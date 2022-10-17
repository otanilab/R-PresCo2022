#include "SymbioticEvolution.h"

// コンストラクタ
SymbioticEvolution::SymbioticEvolution()
{
	int i, j;
	// 初期集団生成
	for(i = 0; i < WCHROM_LEN; i++)
		ppop[i] = new PartialPopulation();
	WholeIndividual::ppop = ppop;
	wpop = new WholePopulation();
	wpop->evaluation();
	for(i = 0; i < WCHROM_LEN; i++)
		ppop[i]->evaluation();
	// 最適解初期化
	bestfit = wpop->pop[0]->fitness;
	for(i = 0; i < WCHROM_LEN; i++) {
		for(j = 0; j < PCHROM_LEN; j++)
			best[i*PCHROM_LEN+j] = wpop->pop[0]->chrom[i]->chrom[j];
	}
	printf("初期世代\t最良個体の適応度は%f\n", bestfit);
}

// デストラクタ
SymbioticEvolution::~SymbioticEvolution()
{
	int i;

	for(i = 0; i < WCHROM_LEN; i++)
		delete ppop[i];
	delete wpop;
}

// 進化
void SymbioticEvolution::solve(void)
{
	int gen, i, j;

	for(gen = 1; gen <= GENERATION_MAX; gen++) {
		// 次世代生成
		
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->newGeneration();
		wpop->newGeneration();
		// 評価
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->evalinit();
		wpop->evaluation();
		for(i = 0; i < WCHROM_LEN; i++)
			ppop[i]->evaluation();
		// 最適解更新
		if(wpop->pop[0]->fitness < bestfit) {
			bestfit = wpop->pop[0]->fitness;
			//初期化
			for(i = 0; i < PEOPLE_NUM; i++) {
				used_photo_cnt[i] = 0;
			}
	
			for(i = 0; i < WCHROM_LEN; i++) {
				for(j = 0; j < PCHROM_LEN; j++) {
					best[i*PCHROM_LEN+j] = wpop->pop[0]->chrom[i]->chrom[j];
					used_photo_cnt[best[i * PCHROM_LEN + j] / (MATERIAL_PHOTO_NUM / PEOPLE_NUM)]++;
				}
			}

			for(i = 0; i < PEOPLE_NUM; i++) {
				printf("%d人目　%f枚\n",i, used_photo_cnt[i]);
			}

			printf("第%d世代\t最良個体の適応度は%f\n", gen, bestfit);
		}
	}
}
