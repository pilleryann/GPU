#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
	RipplingMath(int w, int h)
	    {
	    this->dim2 = w / 2;
	    }

	__device__
	RipplingMath(const RipplingMath& source)
	    {
	    //nothing
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * x=pixelI
	 * y=pixelJ
	 */
	__device__
	void color(int i, int j, float t, uchar4& color)
	    {
	    // Debug (a mettre en commentaire)
		/*{
		unsigned char levelGris = 128; //in [0.255]  (debug image)
		color.x = levelGris;
		color.y = levelGris;
		color.z = levelGris;
		}*/

	    // Vrai problem
		{
		  float dxy_val = 0.0;
		  dxy(i,j,&dxy_val);

		  double numerator = cos(dxy_val/10-t/7);
		  double denominator = dxy_val/10+1;
		  double result = 128+127*numerator/denominator;
		  color.x = result;
		  color.y = result;
		  color.z = result;
		  color.w = 255;
		}

	    //color.w = 255; // opaque
	    }

    private:
	__device__ void dxy(int i, int j, float* ptrResult) // par exmple
	    {
	      double fx = i-this->dim2;
	      double fy = j-this->dim2;

	      *ptrResult = sqrt(fx*fx+fy*fy);

	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	double dim2; //=dim/2

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
