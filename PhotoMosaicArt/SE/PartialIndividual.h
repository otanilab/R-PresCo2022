#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

// 定数の定義
#define GENERATION_MAX	2000					// 世代交代数
#define WPOP_SIZE		1000						// 全体解集団内の個体の数
#define PPOP_SIZE		950						// 部分解集団内の個体の数
#define MUTATE_PROB		0.0001 * RAND_MAX		  	// 突然変異確率
#define MUTATE_PROBI	0.1 * RAND_MAX			// 突然変異確率×乱数の最大値
#define MAX_NUM			WCHROM_LEN*PCHROM_LEN	// フロイド問題におけるN
#define WCHROM_LEN		25						// 全体解の染色体の長さ
#define PCHROM_LEN		480						// 部分解の染色体の長さ
#define CHILDPOP		6
#define ArtPhotoNum     2025                    //モザイクアートの構成写真枚数

class PartialIndividual
{
public:
	PartialIndividual();
	~PartialIndividual();
	void newGeneration();
	void newGeneration(PartialIndividual* p);
	void newGeneration(PartialIndividual* p1, PartialIndividual* p2, int index1, int index2);

	int chrom[PCHROM_LEN];	// 染色体
	double fitness;			// 適応度

private:
	void mutate();
};
