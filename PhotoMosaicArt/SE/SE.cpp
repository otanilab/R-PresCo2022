// floydSE.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "SymbioticEvolution.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> B, G, R;
vector<int> OB, OG, OR;
int pchrom_sub[PCHROM_LEN], pchrom_num[PCHROM_LEN];
int photo_sub[ArtPhotoNum];

//カンマ区切りで読み込む関数
vector<string> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

void sortn(int lb, int ub)
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

// メインルーチン
int main()
{
	int i, j;
	float comptime;
	clock_t start;
	SymbioticEvolution *se;

	// 時間計測スタート
	start = clock();

	// 乱数のタネの設定
	srand((unsigned int)time(NULL));

	ifstream ifs("../OriginalProcessing/OriginalResult.csv");

    //画素値読込
    string line;
    while (getline(ifs, line)) {

        vector<string> strvec = split(line, ',');
       
        OB.push_back(stoi(strvec.at(0)));
        OG.push_back(stoi(strvec.at(1)));
        OR.push_back(stoi(strvec.at(2)));
    }

    //素材画像の画素値の中央値を記述したファイルをopen
    ifstream ifs2("../MaterialProcessing/MaterialResult.csv");

    //画素値読込
    string line2;
    while (getline(ifs2, line2)) {

        vector<string> strvec = split(line2, ',');
       
        B.push_back(stoi(strvec.at(0)));
        G.push_back(stoi(strvec.at(1)));
        R.push_back(stoi(strvec.at(2)));
    }
	
	FILE *fp;
    fp = fopen("Result.csv", "w");

	// 解探索
	se = new SymbioticEvolution();
	
	se->solve();

	// 処理時間計算
	comptime = (float)(clock() - start) / CLOCKS_PER_SEC;

	// 結果表示
	for(i = 0; i < WCHROM_LEN; i++) {
		//初期化
		for(j = 0; j < PCHROM_LEN; j++) {
			pchrom_sub[j] = i * PCHROM_LEN + j;
		}

		for(j = 0; j < PCHROM_LEN; j++) {
			pchrom_num[j] = se->wpop->pop[0]->chrom[i]->chrom[j];
		}
		sortn(0, PCHROM_LEN-1);
		for(j = 0; j < ArtPhotoNum / WCHROM_LEN; j++) {
			//photo_sub[i * ArtPhotoNum / WCHROM_LEN + j] = pchrom_sub[j]; //右並べ
			photo_sub[i + WCHROM_LEN * j] = pchrom_sub[j];  //交互
		}
	}

	for(i = 0; i < ArtPhotoNum; i++) {
		cout << i << " " << photo_sub[i] << endl;
		fprintf(fp, "%d,", photo_sub[i]);
	}

    fclose(fp);

	printf("\n最良個体の適応度：%f\n", se->bestfit);
	printf("処理時間：%f秒\n", comptime);

	// 後処理
	delete se;

	return 0;
}
