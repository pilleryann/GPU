#include <omp.h>
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

bool
isPiOMPEntrelacerAtomic_Ok (int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double
piOMPEntrelacerAtomic (int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool
isPiOMPEntrelacerAtomic_Ok (int n)
{
  return isAlgoPI_OK (piOMPEntrelacerAtomic, n, "Pi OMP Entrelacer atomic");
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Bonne performance, si!
 */
double
piOMPEntrelacerAtomic (int n)
{
  const int NBTHREAD = OmpTools::setAndGetNaturalGranularity ();
  double sum = 0;

  const double DX = 1.0 / (double) n;

#pragma omp parallel
    {
      double xs = 0;
      double sumLocalThread = 0.0;
      const int ID = OmpTools::getTid ();
      int s = ID;
      while (s < n)
	{
	  xs = s * DX;
	  sumLocalThread += fpi (xs);
	  s += NBTHREAD;
	}
#pragma omp atomic
      sum += sumLocalThread;
    }

  return sum * DX;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

