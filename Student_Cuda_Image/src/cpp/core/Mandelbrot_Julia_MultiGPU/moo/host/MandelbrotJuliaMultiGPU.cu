#include <assert.h>

#include "MandelbrotJuliaMultiGPU.h"
#include "Device.h"
#include "MathTools.h"
#include <omp.h>


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void mandelbrotJuliaCuMltiGPU(uchar4* ptrDevPixels,int w, int h,DomaineMath domaineMath, int n,float t,bool isJulia,float cX,float cY,float offset);

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

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

MandelbrotJuliaMultiGPU::MandelbrotJuliaMultiGPU(int w, int h, float dt, int n,float xMin,float xMax,float yMin,float yMax,bool isJulia,float cX=0,float cY=0) :
	variateurAnimation(IntervalF(20, 200),dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->n = n;
	this->cX=cX;
    this->cY=cY;
    this->isJulia=isJulia;
    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = 0;
    ptrDomaineMathInit=new DomaineMath(xMin,yMin,xMax,yMax);

    //Outputs
    this->title = "[API Image Fonctionelle] : MandelbrotJuliaMultiGPU zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);

    const size_t SIZE_BAND=h/6*w*sizeof(uchar4);
    std::cout<<"--- Inits GPUS ----";
    cudaSetDevice(1);
    std::cout<<"Init1 ";
    HANDLE_ERROR(cudaMalloc(&ptrDevPixels1,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(ptrDevPixels1,0,SIZE_BAND));
    cudaSetDevice(2);
    std::cout<<"Init2 ";
    HANDLE_ERROR(cudaMalloc(&ptrDevPixels2,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(ptrDevPixels2,0,SIZE_BAND));
    cudaSetDevice(3);
    std::cout<<"Init2 ";
    HANDLE_ERROR(cudaMalloc(&ptrDevPixels3,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(ptrDevPixels3,0,SIZE_BAND));
    cudaSetDevice(4);
    std::cout<<"Init3 ";
    HANDLE_ERROR(cudaMalloc(&ptrDevPixels4,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(ptrDevPixels4,0,SIZE_BAND));
    cudaSetDevice(5);
    std::cout<<"Init4 ";
    HANDLE_ERROR(cudaMalloc(&ptrDevPixels5,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(ptrDevPixels5,0,SIZE_BAND));

    cudaSetDevice(0);


    assert(w == h);
    }

MandelbrotJuliaMultiGPU::~MandelbrotJuliaMultiGPU()
    {
    cudaSetDevice(1);
    HANDLE_ERROR(cudaFree(ptrDevPixels1));
    cudaSetDevice(2);
    HANDLE_ERROR(cudaFree(ptrDevPixels2));
    cudaSetDevice(3);
    HANDLE_ERROR(cudaFree(ptrDevPixels3));
    cudaSetDevice(4);
    HANDLE_ERROR(cudaFree(ptrDevPixels4));
    cudaSetDevice(5);
    HANDLE_ERROR(cudaFree(ptrDevPixels5));
    cudaSetDevice(0);

   delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void MandelbrotJuliaMultiGPU::animationStep()
    {


    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }


int MandelbrotJuliaMultiGPU::setAndGetNaturalGranularity()
    {
    // ko sur ARM, 1 core detecte only
//    {
//    int nbThread = omp_get_num_procs();
//    omp_set_num_threads(nbThread);
//    return nbThread;
//    }

#ifndef __arm__

    int nbThread = omp_get_num_procs();

#else

    //omp_get_num_procs ne donne pas la bonne valeurs sur kayla

    int nbThread=4;//4 car kayla � 4 coeurs.

#endif

    omp_set_num_threads(nbThread);
    return nbThread;
    }

/**
 * Override
 */
void MandelbrotJuliaMultiGPU::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {

    const size_t SIZE_RESULT = h/6*w*(size_t)sizeof(uchar4);

    const int NBTHREAD = setAndGetNaturalGranularity();




        #pragma omp parallel
        {
	  const int TID = omp_get_thread_num();
	  switch(TID){
	      case 0 :
		  cudaSetDevice(0);
		  		     mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels,w,h/6,domaineMath,n,t, isJulia, cX, cY,0);
		  break;
	      case 1 :
		  cudaSetDevice(1);
		 		    mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels1,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6);
		 		    HANDLE_ERROR(cudaMemcpy(ptrDevPixels+(h/6*w),ptrDevPixels1,SIZE_RESULT,cudaMemcpyDeviceToDevice));//barriere implicite de sync
		  break;
	      case 2 :  cudaSetDevice(2);
	      mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels2,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*2);
	      HANDLE_ERROR(cudaMemcpy(ptrDevPixels+(h/6*w*2),ptrDevPixels2,SIZE_RESULT,cudaMemcpyDeviceToDevice));//barriere implicite de sync
      	      	      break;
	      case 3 :
		  cudaSetDevice(3);
		  		     mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels3,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*3);
		  		     HANDLE_ERROR(cudaMemcpy(ptrDevPixels+(h/6*w*3),ptrDevPixels3,SIZE_RESULT,cudaMemcpyDeviceToDevice));//barriere implicite de sync
		      break;
	      case 4 :
		  cudaSetDevice(4);
		      mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels4,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*4);
		      HANDLE_ERROR(cudaMemcpy(ptrDevPixels+(h/6*w*4),ptrDevPixels4,SIZE_RESULT,cudaMemcpyDeviceToDevice));//barriere implicite de sync
	      	      break;
	      case 5 :
		  cudaSetDevice(5);
		         mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels5,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*5);
		         HANDLE_ERROR(cudaMemcpy(ptrDevPixels+(h/6*w*5),ptrDevPixels5,SIZE_RESULT,cudaMemcpyDeviceToDevice));//barriere implicite de sync
	      	      break;
	      default :
		  break;
	  }
        }

    cudaSetDevice(0);

    }

/*--------------*\
 |*	get	 *|,
 \*--------------*/

/**
 * Override
 */
DomaineMath* MandelbrotJuliaMultiGPU::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float MandelbrotJuliaMultiGPU::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int MandelbrotJuliaMultiGPU::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int MandelbrotJuliaMultiGPU::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string MandelbrotJuliaMultiGPU::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

