#include <omp.h>
#include <string.h>
#include "00_pi_tools.h"
#include "OmpTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab,  n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    double* sum = new double[NB_THREAD];
    memset(sum, 0, NB_THREAD*sizeof(*sum));
    double finalSum = 0.0;
    const double DX = 1.0/(double)n;
#pragma omp parallel
    {
	double xs = 0.0;
	const int TID = OmpTools::getTid();
	int s = TID;
	while(s<n)
	    {
	    xs = s*DX;
	    sum[TID] += fpi(xs);
	    s+=NB_THREAD;
	    }
    }
    // reduction sequentielle
    for(int i = 0;i<NB_THREAD;i++)
	{
	finalSum += sum[i];
	}
    delete[] sum;
    return DX*finalSum;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

