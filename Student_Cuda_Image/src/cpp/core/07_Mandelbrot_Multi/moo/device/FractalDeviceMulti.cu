#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "FractalMathMulti.h"
#include "FractalMandelbrotMulti.h"



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void fractalMulti(uchar4* ptrDevPixels,int w, int h,bool julia,DomaineMath domaineMath, int n,float t,double cx, double cy);
__device__ void workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,FractalMathMulti* ptrFractalMath,float t);

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

__global__ void fractalMulti(uchar4* ptrDevPixels, int w, int h,bool julia, DomaineMath domaineMath, int n,float t,double cx, double cy)
    {
    FractalMathMulti* fractalMath;
    fractalMath = new FractalMandelbrotMulti(n);// ici pour preparer cuda
    const int NB_THREAD = Indice2D::nbThread(); // dans region parallel

    const int TID = Indice2D::tid();
    int s = TID; // in [0,...

    int i;
    int j;
    int WH = w*h;
    while (s < WH)
	{
	IndiceTools::toIJ(s,w,&i,&j); // s[0,W*H[ --> i[0,H[ j[0,W[

	workPixel(&ptrDevPixels[s],i, j,s, domaineMath,fractalMath,t);

	s += NB_THREAD;
	}

    delete fractalMath;

    }


__device__ void workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,FractalMathMulti* ptrFractalMath, float t)
    {

    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2
   // std::cout<<"print"<<std::endl;
    double x;
    double y;

    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    ptrFractalMath->colorXY(ptrColorIJ,x, y, domaineMath, t); // in [01]
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

