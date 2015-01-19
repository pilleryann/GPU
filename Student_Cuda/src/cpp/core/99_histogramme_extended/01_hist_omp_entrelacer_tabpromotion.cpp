#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "OmpTools.h"

void hist_omp_entrelacer_tabpromotion(int* data, int* hist, const uint DATA_SIZE, const int MIN_VALUE, const int MAX_VALUE)
{

	assert(MIN_VALUE < MAX_VALUE);
	assert(DATA_SIZE > 0);

	const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
	const int NB_VALUES = MAX_VALUE - MIN_VALUE + 1;

	// Init
	int promotionHistSize = NB_VALUES * NB_THREADS;
	int* promotionHist = new int[promotionHistSize];
	for (int i = 0; i < promotionHistSize; i++)
	{
		promotionHist[i] = 0;
	}

	// Compute histogramme
#pragma omp parallel
	{
		const int TID = OmpTools::getTid();
		const int OFFSET = TID * (MAX_VALUE - MIN_VALUE + 1);
		int s = TID;
		while (s < DATA_SIZE)
		{
			int val = data[s];
			uint index = val - MIN_VALUE;
			promotionHist[OFFSET + index]++;

			s += NB_THREADS;
		}
	}

	// Reduction
	for (int i = 0; i < promotionHistSize; i++)
	{
		hist[i % NB_VALUES] += promotionHist[i];
	}

	delete[] promotionHist;
}
