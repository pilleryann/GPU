#include <iostream>
#include <assert.h>

#include "Rippling.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t);

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

Rippling::Rippling(int w, int h, float dt)
    {
    assert(w == h);

    // Inputs
    this->w = w;
    this->h = h;
    this->dt = dt;

    // Tools
    this->dg = dim3(8, 8, 1);
    this->db = dim3(16, 16, 1);
    this->t = 0;

    // Outputs
    this->title = "Rippling Cuda";

    //print(dg, db);
    Device::assertDim(dg, db);
    }

Rippling::~Rippling()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void Rippling::animationStep()
    {
    t+=dt;
    }

/**
 * Override
 */
void Rippling::runGPU(uchar4* ptrDevPixels)
    {
    rippling<<<dg,db>>>(ptrDevPixels,w,h,t);
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float Rippling::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int Rippling::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int Rippling::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string Rippling::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

