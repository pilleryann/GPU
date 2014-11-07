#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"
#include "VariateurF.h"
#include "Sphere.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracing: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	RayTracing(int w, int h, float dt, double x1, double y1, double x2, double y2, Sphere* spheres, int n);
	virtual ~RayTracing(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*----------------*\
	|*  Override	  *|
	\*---------------*/


	/**
	 * Override
	 * Call periodicly by the API
	 */
	virtual void animationStep(void);

	void runGPU(uchar4* ptrDevPixels); // Override

	/**
	 * Para animation
	 */
	float getT(void); // Override
	int getW(void); // Override
	int getH(void); // Override
	string getTitle(void); // Override



	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
	
	Sphere* spheres;
	int n;

	// Tools
	dim3 dg;
	dim3 db;
	float t;
	VariateurF variateurAnimation;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
