#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>

// 定数の定義
#define GENERATION_MAX	4000					// 世代交代数
#define WPOP_SIZE		5000					// 全体解集団内の個体の数
#define PPOP_SIZE		5000					// 部分解集団内の個体の数
#define MUTATE_PROB		0.0001 * RAND_MAX		// 突然変異確率×乱数の最大値1
#define MUTATE_PROBI	0.001 * RAND_MAX		// 突然変異確率×乱数の最大値2
#define MAX_NUM			WCHROM_LEN*PCHROM_LEN	// フロイド問題におけるN
#define MATERIAL_PHOTO_NUM 40000				//構成画像の枚数
#define PEOPLE_NUM		1000					//人数 500 or 1000
#define WCHROM_LEN		60						// 全体解の染色体の長さ
#define PCHROM_LEN		60						// 部分解の染色体の長さ
#define CHILDPOP		6
#define ArtPhotoNum     3600                    //モザイクアートの構成写真枚数
#define SCALE			10000					//分散の重み付

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
