#pragma once

#include "PartialPopulation.h"

class WholeIndividual
{
public:
	static PartialPopulation** ppop;

	WholeIndividual();
	~WholeIndividual();
	void newGeneration();
	void newGeneration(WholeIndividual* p);
	void newGeneration(WholeIndividual* p1, WholeIndividual* p2, int index1, int index2);
	void evaluation();
	int pchrom_sub[PCHROM_LEN], pchrom_num[PCHROM_LEN];
	int photo_sub[ArtPhotoNum];
	void sortn(int lb, int ub);

	PartialIndividual* chrom[WCHROM_LEN];	// ���F��
	double fitness;							// �K���x

private:
	void mutate();
};
