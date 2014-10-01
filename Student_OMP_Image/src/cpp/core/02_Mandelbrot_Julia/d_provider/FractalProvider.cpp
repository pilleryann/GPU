#include "FractalProvider.h"
#include "MathTools.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-----------------*\
 |*	static	   *|
 \*----------------*/

FractalImage* FractalProvider::create(void)
    {
    int dw = 16 * 80; // =32*30=960
    int dh = 16 * 60; // =32*30=960
    bool julia = false;


    // animation para

    //Document : [-2.1,0.8]x[-1.3,1.3]
    //Image API : -2.1,-1.3,0.8,1.3
    //mandelbrot ex 1
    /*int n = 12;
    double xMin = -2.1;
    double yMin = -1.3;
    double xMax = 0.8;
    double yMax = 1.3;*/

    //mandelbrot ex 2
    /*int n = 102;
    double xMin = -1.3968;
    double yMin = -0.03362;
    double xMax = -1.3578;
    double yMax = 0.0013973;*/

    //julia ex 2
    /*julia = true;
    int n = 52;
    double cx = -0.12;
    double cy = 0.85;
    double xMin = -1.3;
    double yMin = -1.4;
    double xMax = 1.3;
    double yMax = 1.4;*/
    julia = true;
    int n = 300;
    double cx = -0.745;
    double cy = 0.1;
    double xMin = -1.7;
    double yMin = -1;
    double xMax = 1.7;
    double yMax = 1;

    return new FractalImage(dw, dh, julia, n,xMin,yMin,xMax,yMax,cx,cy);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
