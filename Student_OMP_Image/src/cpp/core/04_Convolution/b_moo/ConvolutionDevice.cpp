/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "ConvolutionDevice.h"
#include <iostream>
#include <omp.h>
#include "IndiceTools.h"
#include "OmpTools.h"
#include "ConvolutionMath.h"

/*void ConvolutionDevice::ecrasementTexture(uchar* tabSM, int halfThread)
 {
 const int TID_LOCAL = Indice1D::tidLocalBlock();
 const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
 int s = TID_LOCAL;
 while (s < halfThread)
 {
 if (tabSM[s] > tabSM[s + halfThread]) // if tabSM not min
 tabSM[s] = tabSM[s + halfThread];
 if (tabSM[NB_THREAD_BLOCK + s] < tabSM[NB_THREAD_BLOCK + s + halfThread]) // if tabSM not max
 tabSM[NB_THREAD_BLOCK + s] = tabSM[NB_THREAD_BLOCK + s + halfThread];
 s += NB_THREAD_BLOCK;
 }
 }*/

/*void ConvolutionDevice::reductionIntraBTexture(uchar* tabSM)
 {
 const int NB_THREAD = Indice1D::nbThread();
 const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
 int halfThread = NB_THREAD_BLOCK / 2;
 while (halfThread >= 1)
 {
 ecrasementTexture(tabSM, halfThread);
 halfThread /= 2;
 }
 }*/

void ConvolutionDevice::reductionInterBTexture(uchar* tabSM, uchar* ptrDevResult)
    {
#pragma omp parallel
	{
	const int TID_LOCAL = OmpTools::getTid();
	const int NB_THREAD = OmpTools::getNbThread();

	if (TID_LOCAL == 0)
	    {
	    ptrDevResult[0] = 0; //Min
	    ptrDevResult[1] = 255; //Max
	    for (int i = 0; i < NB_THREAD; i++)
		{
		if (tabSM[i] < ptrDevResult[0])
		    {
		    ptrDevResult[0] = tabSM[i];
		    }
		if (tabSM[i + NB_THREAD] > ptrDevResult[1])
		    {
		    ptrDevResult[1] = tabSM[i + NB_THREAD];
		    }

		}

	    }

	}
    }
void ConvolutionDevice::reductionIntraTTexture(uchar* tabSM, uchar4* ptrDevPixels, int n)
    {
#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread();
	const int TID = OmpTools::getTid();

	int s = TID;
	uchar minCrtThread = 255;
	uchar maxCrtThread = 0;
	while (s < n)
	    {
	    uchar crtVal = ptrDevPixels[s].x;
	    if (crtVal > maxCrtThread)
		maxCrtThread = crtVal;
	    if (crtVal < minCrtThread)
		minCrtThread = crtVal;
	    s += NB_THREAD;
	    }
	tabSM[TID] = minCrtThread;
	tabSM[NB_THREAD + TID] = maxCrtThread; // tabSM is 2*n size
	}
    }

void ConvolutionDevice::colorToGreyTexture(uchar4* ptrDevPixels, int w, int h)
    {
#pragma omp parallel
	{
	const int TID = OmpTools::getTid();
	const int NB_THREAD = OmpTools::getNbThread();

	const int WH = w * h;

	int s = TID;
	while (s < WH)
	    {

	    float x = ptrDevPixels[s].x;
	    float y = ptrDevPixels[s].y;
	    float z = ptrDevPixels[s].z;
	    float average = (x / (float) 3.0 + y / (float) 3.0 + z / (float) 3.0);
	    ptrDevPixels[s].x = average;
	    ptrDevPixels[s].y = average;
	    ptrDevPixels[s].z = average;
	    ptrDevPixels[s].w = 255;
	    s += NB_THREAD;
	    }

	}
    }

void ConvolutionDevice::affineTransformTexture(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset)
    {
    const int TID = OmpTools::getTid();
    const int NB_THREAD = OmpTools::getNbThread();

    const int WH = w * h;

    int s = TID;
    while (s < WH)
	{
	uchar newValue = (uchar) ((float) (ptrDevPixels[s].x) * a + b);
	newValue += offset;
	if (newValue > 255)
	    newValue = 255;
	ptrDevPixels[s].x = newValue;
	ptrDevPixels[s].y = newValue;
	ptrDevPixels[s].z = newValue;
	s += NB_THREAD;
	}
    }

void ConvolutionDevice::convolutionTextureKernel(uchar4* ptrDevPixels, float* ptrKernel, int k, int w, int h, float t)
    {

#pragma omp parallel
	{
	ConvolutionMath convMath = ConvolutionMath(w, h);

	const int TID = OmpTools::getTid();
	const int NB_THREAD = OmpTools::getNbThread();

	const int WH = w * h;

	uchar4 color;

	int pixelI;
	int pixelJ;

	int s = TID;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	    const int KERN_SIZE = 9;

	    convMath.colorIJ(&color, ptrDevPixels, ptrKernel, k, pixelJ, pixelI, s); // update color
	    ptrDevPixels[s] = color;
	    s += NB_THREAD;
	    }
	}

    }

/*
 * ptrDevResult should contain min in [0] and max in [1]
 */
void ConvolutionDevice::findMinMaxTexture(uchar4* ptrDevPixels, uchar* ptrDevResult, int w, int h)
    {

    uchar tabSM[OmpTools::getNbThread() * 2];

    int sizePtrDevPixels = w * h;
    reductionIntraTTexture(tabSM, ptrDevPixels, sizePtrDevPixels);
    reductionInterBTexture(tabSM, ptrDevResult);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

