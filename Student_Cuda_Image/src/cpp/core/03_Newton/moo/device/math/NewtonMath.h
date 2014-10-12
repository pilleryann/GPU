#ifndef NEWTONMATH_H_
#define NEWTONMATH_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class NewtonMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ NewtonMath(int n)
	/*:calibreur(IntervalF(0, n), IntervalF(0, 1))*/
	    {
	this->n = n;
	xa.x1 = 1.0;
	xa.x2 = 0.0;
	xb.x1 = -0.5;
	xb.x2 = sqrt(1.5);
	xc.x1 = -0.5;
	xc.x2 = -sqrt(1.5);
	    }

	__device__ virtual ~NewtonMath(void)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	int indiceArret(float x1, float x2, float epsilonx, float epsilonf,
		float epsilonxstar,float* jacobiMatrix)
	    {

	float crtX1 = x1;
	float crtX2 = x2;

	float nextX1,nextX2;
	float solX1, solX2;
	int nbIters = 0;
	int itersNotConverge = 500;
	while(nbIters < itersNotConverge)
	    {
	    jacobi(crtX1,crtX2,jacobiMatrix);
	    inverse(jacobiMatrix);
	    matrixVectorMult(jacobiMatrix,f1(crtX1,crtX2),f2(crtX1,crtX2),&solX1,&solX2);
	    nextX1 = crtX1 - solX1;
	    nextX2 = crtX2 - solX2;
	    // current X is near solution a, b or c
	    if(normSquare(crtX1-xa.x1,crtX2-xa.x2)/normSquare(xa.x1,xa.x2) < epsilonxstar)
		{
		return NOIR;
		}
	    else if(normSquare(crtX1-xb.x1,crtX2-xb.x2)/normSquare(xb.x1,xb.x2) < epsilonxstar)
		{
		return GRIS;
		}
	    else if(normSquare(crtX1-xc.x1,crtX2-xc.x1)/normSquare(xc.x1,xc.x2) < epsilonxstar)
		{
		return BLANC;
		}
	    // iteration doesn't move enough OR solution is good enough
	    if(normSquare(crtX1-nextX1,crtX2-nextX2)/normSquare(nextX1,nextX2) < epsilonx ||
		    normSquare(f1(crtX1, crtX2)-f1(nextX1,nextX2),f2(crtX1, crtX2)-f2(nextX1,nextX2))/
		    normSquare(f1(nextX1,nextX2),f2(nextX1,nextX2)) < epsilonf)
		{
		float diffA = normSquare(nextX1-xa.x1,nextX2-xa.x2)/normSquare(xa.x1,xa.x2);
		float diffB = normSquare(nextX1-xb.x1,nextX2-xb.x2)/normSquare(xb.x1,xb.x2);
		float diffC = normSquare(nextX1-xc.x1,nextX2-xc.x2)/normSquare(xc.x1,xc.x2);

		if(diffA < diffB)
		    {
		    if(diffA < diffC)
			return NOIR; // near xa
		    else
			return BLANC; // near xc
		    }
		else
		    {
		    if(diffB < diffC)
			return GRIS; // near xb
		    else
			return BLANC; // near xc
		    }
		}
	    crtX1 = nextX1;
	    crtX2 = nextX2;
	    nbIters++;
	    }
	return NOT_CONVERGE_ERROR;
	    }

	__device__
	float normSquare(float x1, float x2)
	    {
	    return x1*x1+x2*x2;
	    }

	__device__
	float f1(float x1, float x2)
	    {
	    return (x1*x1*x1)-(3*x1*(x2*x2))-1;
	    }

	__device__
	float f2(float x1, float x2)
	    {
	    return (x2*x2*x2)-(3*x2*(x1*x1));
	    }

	__device__
	float d1f1(float x1, float x2)
	    {
	    return (3*x1*x1)-(3*x2*x2);
	    }

	__device__
	float d2f1(float x1, float x2)
	    {
	    return -6*x1*x2;
	    }

	__device__
	float d1f2(float x1, float x2)
	    {
	    return -6*x2*x1;
	    }

	__device__
	float d2f2(float x1, float x2)
	    {
	    return 3*x2*x2-3*x1*x1;
	    }

	__device__
	void jacobi(float x1, float x2, float* matrixDevicePtr)
	    {
	    matrixDevicePtr[0] = d1f1(x1,x2);
	    matrixDevicePtr[1] = d2f1(x1,x2);
	    matrixDevicePtr[2] = d1f2(x1,x2);
	    matrixDevicePtr[3] = d2f2(x1,x2);
	    }

	__device__
	float det(float* matrixDevicePtr)
	    {
	    return (matrixDevicePtr[0]*matrixDevicePtr[3])-(matrixDevicePtr[1]*matrixDevicePtr[2]);
	    }

	__device__
	void inverse(float* matrixDevicePtr)
	    {
	    float determ = det(matrixDevicePtr);
	    float aCopy = matrixDevicePtr[0];
	    float bCopy = matrixDevicePtr[1];
	    float cCopy = matrixDevicePtr[2];
	    float dCopy = matrixDevicePtr[3];
	    matrixDevicePtr[0] = dCopy / determ;
	    matrixDevicePtr[1] = -bCopy / determ;
	    matrixDevicePtr[2] = -cCopy / determ;
	    matrixDevicePtr[3] = aCopy / determ;
	    }

	__device__
	void matrixVectorMult(float* matrixDevicePtr, float x1, float x2,float* solX1, float* solX2)
	    {
	    *solX1 = matrixDevicePtr[0]*x1+matrixDevicePtr[1]*x2;
	    *solX2 = matrixDevicePtr[2]*x1+matrixDevicePtr[3]*x2;
	    }

	/**
	 * x=pixelI
	 * y=pixelJ
	 */
	__device__
	void colorXY(uchar4* ptrColor,float x, float y,float t,float epsilonx,float epsilonf,
		float epsilonxstar,float* jacobiMatrix)
	    {
	    int couleur = indiceArret(x,y,epsilonx,epsilonf,epsilonxstar,jacobiMatrix);
	    //printf("%f\n",k);
	    if(couleur == NOIR)
		{
		ptrColor->x = 0; // noir
		ptrColor->y = 0; // noir
		ptrColor->z = 0; // noir
		}
	    else if(couleur == GRIS)
		{
		ptrColor->x = 211; // gris
		ptrColor->y = 211; // gris
		ptrColor->z = 211; // gris
		}
	    else if(couleur == BLANC)
		{
		ptrColor->x = 255; // blanc
		ptrColor->y = 255; // blanc
		ptrColor->z = 255; // blanc
		}
	    else if(couleur == NOT_CONVERGE_ERROR)
		{
		ptrColor->x = 255; // orange
		ptrColor->y = 165; // orange
		ptrColor->z = 0; // orange
		}

	    ptrColor->w = 255; // opaque
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Input
	int n;

	struct solutions
	    {
		float x1;
		float x2;
	    };

	struct solutions xa;
	struct solutions xb;
	struct solutions xc;

	const static int NOIR = 0;
	const static int GRIS = 1;
	const static int BLANC = 2;
	const static int NOT_CONVERGE_ERROR = 3;

	// Tools
	//CalibreurF calibreur;

    };



#endif 



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
