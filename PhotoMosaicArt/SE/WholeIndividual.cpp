#include "WholeIndividual.h"
#include <vector>
#include <iostream>
using namespace std;
PartialPopulation** WholeIndividual::ppop = NULL;

extern vector<int> B, G, R;
extern vector<int> OB, OG, OR;

// コンストラクタ
WholeIndividual::WholeIndividual()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++)
		chrom[i] = ppop[i]->pop[rand() % PPOP_SIZE];
	fitness = DBL_MAX;
}

// デストラクタ
WholeIndividual::~WholeIndividual()
{

}

// 次世代生成（ランダム）
void WholeIndividual::newGeneration()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++)
		chrom[i] = ppop[i]->pop[rand() % PPOP_SIZE];
	fitness = DBL_MAX;
}

// 次世代生成（コピー＆突然変異）
// p: コピー元個体へのポインタ
void WholeIndividual::newGeneration(WholeIndividual* p)
{
	int i;
	
	for(i = 0; i < WCHROM_LEN; i++)
		chrom[i] = p->chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// 次世代生成（２点交叉＆突然変異）
// p1: 親個体その１
// p2: 親個体その２
// index1: 交叉点（0～WCHROM_LEN-1）
// index2: 交叉点（0～WCHROM_LEN-1）
void WholeIndividual::newGeneration(WholeIndividual* p1, WholeIndividual* p2, int index1, int index2)
{
	int i, min, max;

	if(index1 < index2) {
		min = index1;
		max = index2;
	} else {
		min = index2;
		max = index1;
	}
	for(i = 0; i < min; i++)
		chrom[i] = p1->chrom[i];
	for( ; i < max; i++)
		chrom[i] = p2->chrom[i];
	for( ; i < PCHROM_LEN; i++)
		chrom[i] = p1->chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// 突然変異
void WholeIndividual::mutate()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++) {
		if(rand() < MUTATE_PROBI)
			chrom[i] = ppop[i]->pop[rand() % PPOP_SIZE];
	}
}
void WholeIndividual::sortn(int lb, int ub)
{
	int i, j, k;
	double pivot;
	int tmp;

	if(lb < ub) {
		k = (lb + ub) / 2;
		pivot = pchrom_num[k];
		i = lb;
		j = ub;
		do {
			while(pchrom_num[i] < pivot) {
				i++;
			}
			while(pchrom_num[j] > pivot) {
				j--;
			}
			if(i <= j) {
				tmp = pchrom_num[i];
				pchrom_num[i] = pchrom_num[j];
				pchrom_num[j] = tmp;
				tmp = pchrom_sub[i];
				pchrom_sub[i] = pchrom_sub[j];
               	pchrom_sub[j] = tmp;
				i++;
				j--;
			}
		} while(i <= j);
		sortn(lb, j);
		sortn(i, ub);
	}
}

// 評価
void WholeIndividual::evaluation()
{
	int i, j, k;

	fitness = 0.0;
	for(i = 0; i < WCHROM_LEN; i++) {
		//初期化
		for(j = 0; j < PCHROM_LEN; j++) {
			pchrom_sub[j] = i * PCHROM_LEN + j;
		}

		for(j = 0; j < PCHROM_LEN; j++) {
			pchrom_num[j] = chrom[i]->chrom[j];
		}
		sortn(0, PCHROM_LEN-1);
		for(j = 0; j < ArtPhotoNum / WCHROM_LEN; j++) {
			photo_sub[i * ArtPhotoNum / WCHROM_LEN + j] = pchrom_sub[j]; //交互i + WCHROM_LEN * j
		}
	}
	for(i = 0; i < ArtPhotoNum; i++) {
		double dis = (B[photo_sub[i]] - OB[i]) * (B[photo_sub[i]] - OB[i]) + (G[photo_sub[i]] - OG[i]) * (G[photo_sub[i]] - OG[i]) + (R[photo_sub[i]] - OR[i]) * (R[photo_sub[i]] - OR[i]);
		dis = sqrt(dis);
		fitness += dis;
	}
	fitness = fabs(fitness);
}
