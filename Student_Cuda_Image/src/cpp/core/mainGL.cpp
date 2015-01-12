#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"

#include "Device.h"
#include "cudaTools.h"

#include "Rippling0Provider.h"
#include "RipplingProvider.h"
#include "MandelbrotJuliaProvider.h"
#include "MandelbrotJuliaProviderMultiGPU.h"
#include "HeatTransfertProvider.h"
#include "RayTracingProvider.h"
#include "NewtonProvider.h"
#include "ConvolutionProvider.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainGL(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainGL(void)
    {
    Rippling0Image* ptrRippling0 = Rippling0Provider::createGL();
    Image* ptrRippling = RipplingProvider::createGL();
    Image* ptrRayTracing = RayTracingProvider::createGL();
    Image* ptrConvolution = ConvolutionProvider::createGL();
    // TODO : Insert  autres Images ...
    //ImageFonctionel* ptrMandelbrotJulia = MandelbrotJuliaProvider::createGL();

  //  ImageFonctionel* ptrMandelbrotJuliaMultiGPU =  MandelbrotJuliaProviderMultiGPU::createGL();

    Image* ptrHeatTransfert =  HeatTransfertProvider::createGL();
    ImageFonctionel* ptrNewton = NewtonProvider::createGL();


    bool isAnimation = true;
    bool isSelection = false;

   // GLUTImageViewers rippling0Viewer(ptrRippling0, isAnimation, isSelection, 0, 0);
  //  GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelection, 10, 10);
    // TODO : Insert here autres ImageViewers ...
    //GLUTImageViewers mandelbrotJuliaViewer(ptrMandelbrotJulia, isAnimation, isSelection, 0, 0);

    //-----------------------------JULIA MANDELBROT MULTI GPU
   // GLUTImageViewers mandelbrotJuliaViewerMultiGPU(ptrMandelbrotJuliaMultiGPU, isAnimation, isSelection, 0, 0);
  //  GLUTImageViewers heatTransfertViewer(ptrHeatTransfert, isAnimation, isSelection, 0, 0);
  //  GLUTImageViewers  rayTracingViewer(ptrRayTracing, isAnimation, isSelection, 0, 0);
   // GLUTImageViewers  newtonViewer(ptrNewton, isAnimation, isSelection, 0, 0);
    GLUTImageViewers  newtonViewer(ptrConvolution, isAnimation, isSelection, 0, 0);
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	delete ptrRippling0;
	delete ptrRippling;
	delete ptrRayTracing;
	//delete ptrMandelbrotJuliaMultiGPU;
	//delete ptrMandelbrotJulia;
	delete ptrHeatTransfert;
	delete ptrNewton;
	delete ptrConvolution;

	ptrRippling0 = NULL;
	ptrRayTracing=NULL;
	ptrRippling = NULL;
	ptrHeatTransfert=NULL;
	ptrNewton=NULL;
	ptrConvolution=NULL;
	//ptrMandelbrotJuliaMultiGPU=NULL;
	//ptrMandelbrotJulia = NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

