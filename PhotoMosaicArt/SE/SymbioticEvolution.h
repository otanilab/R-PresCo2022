#pragma once

#include "WholePopulation.h"

class SymbioticEvolution
{
public:
	SymbioticEvolution();
	~SymbioticEvolution();
	void solve();

	int best[MAX_NUM];
	double bestfit;

	WholePopulation* wpop;
	PartialPopulation* ppop[WCHROM_LEN];
};
