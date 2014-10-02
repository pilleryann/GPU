#include <iostream>

#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "RipplingMath.h"
#include "IndiceTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t)
    {
	RipplingMath ripplingMath(w,h);
	const int WH = w * h;
	const int NB_THREAD = Indice2D::nbThread();// dans region parallel
	const int TID = Indice2D::tid();
	int s = TID; // in [0,...

	int i;
	int j;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[
	    ripplingMath.color(i,j,t,ptrDevPixels[s]);

	    s += NB_THREAD;
	    }
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

