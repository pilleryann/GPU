#include "NewtonProvider.h"
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

Newton* NewtonProvider::create()
    {
    int dw = 16 * 60; // =32*30=960
    int dh = 16 * 60; // =32*30=960

    unsigned int n = 102;

    double x1 = -2.0;
    double y1 = -2.0;
    double x2 = 2.0;
    double y2 = 2.0;

    float dt = 0.1;//animation step

    float eX = 1.0e-3;
    float eF = 1.0e-3;
    float eX_Star = 1.0e-3;

    return new Newton(dw, dh, dt, x1, y1, x2, y2, eX, eF, eX_Star);
    }

ImageFonctionel* NewtonProvider::createGL(void)
    {
    ColorRGB_01* ptrColorTitre=new ColorRGB_01(0,0,0);

    return new ImageFonctionel(create(),ptrColorTitre); // both ptr destroy by destructor of ImageFonctionel
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
