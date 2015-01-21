#ifndef CONVOLUTION_MOO_H_
#define CONVOLUTION_MOO_H_


#include <iostream>
#include "MathTools.h"
#include "CaptureVideo.h"
#include "ConvolutionDevice.h"



using std::cout;
using std::endl;
using std::string;
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionMOO
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	ConvolutionMOO(unsigned int w, unsigned int h, float dt);
	virtual ~ConvolutionMOO(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void process(uchar4* ptrTabPixels, int w, int h);
	void animationStep();
	float getT();

    private:

	/*void entrelacementOMP(uchar4* ptrTabPixels,int w,int h); 	// Code entrainement Cuda
	void forAutoOMP(uchar4* ptrTabPixels,int w, int h); 		// Code naturel et direct OMP, plus performsnt
    */
	void fillDetourage(float* ptrNoyau);
	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double dt;

	// Tools
	double t;
	bool isEntrelacement;

	int w;
	int h;

	int k;

	// Tools


	//Outputs
	string title;

	// noyau convolution
	float* ptrHostNoyau;


	// capture video
	string videoPath;
	string videoTitle;
	CaptureVideo* captureur;
	uchar4* ptrHostMemory;


	size_t sizeSM;
	uchar* ptrHostResult;
	size_t sizeResult;

	ConvolutionDevice* convolutionDevice;



    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
