#ifndef FRACTAL_H_
#define HELLO_FONCTIONEL_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"
#include "VariateurF.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fractal: public AnimableFonctionel_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Fractal(int w, int h, float dt, int n);
	virtual ~Fractal(void);

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

	void runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath); // Override

	/**
	 * Para animation
	 */
	float getT(void); // Override
	int getW(void); // Override
	int getH(void); // Override
	DomaineMath* getDomaineMathInit(void); // Override
	string getTitle(void); // Override



	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
	int n;

	// Tools
	dim3 dg;
	dim3 db;
	float t; // para animation
	VariateurF variateurAnimation; // varier t
	DomaineMath* ptrDomaineMathInit;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
