#include "PartialIndividual.h"

// �R���X�g���N�^
PartialIndividual::PartialIndividual()
{
	int i, ch;
	
	for(i = 0; i < PCHROM_LEN; i++) {
		chrom[i] = -1;
	}

	for(i = 0; i < PCHROM_LEN; i++) {
		ch = rand() % (PCHROM_LEN - 1);
		do {
			if(chrom[ch] == -1) {
				chrom[ch] = i;
				break;
			} else {
				ch++;	
				if(ch == PCHROM_LEN) {
					ch = 0;
				}
			}
		}while(1);
		
	}
	fitness = DBL_MAX;
}

// �f�X�g���N�^
PartialIndividual::~PartialIndividual()
{

}

// ����??���i??R?????j
void PartialIndividual::newGeneration()
{
	mutate();
	fitness = DBL_MAX;
}

// ����??���i�R�s�[��??R???j
// p: �R�s�[��?????|�C���^
void PartialIndividual::newGeneration(PartialIndividual* p)
{
	int i;
	
	for(i = 0; i < PCHROM_LEN; i++)
		chrom[i] = p->chrom[i];
	mutate();
	fitness = DBL_MAX;
}

// ����??���i�Q�_������??R???j
// p1: �e???��?P
// p2: �e???��?Q
// index1: �����_�i0�`PCHROM_LEN-1�j
// index2: �����_�i0�`PCHROM_LEN-1�j
void PartialIndividual::newGeneration(PartialIndividual* p1, PartialIndividual* p2, int index1, int index2)
{
	int i, j, min, max, tmp;
	int flag = -1;

	if(index1 < index2) {
		min = index1;
		max = index2;
	} else {
		min = index2;
		max = index1;
	}

	for(i = 0; i <= min; i++) {
		for(j = min + 1; j <= max; j++) {
			if(p1->chrom[i] == p2->chrom[j]) {
				flag = j;
				break;
			}
		}
		if(flag != -1) {
			do{
				for(j = min + 1; j <= max; j++) {
					if(p2->chrom[j] == p1->chrom[flag]) {
						flag = j;
						break;
					}
				}
				if(j == max + 1) {
					chrom[i] = p1->chrom[flag];
					break;
				}
			} while(1);
		} else {
			chrom[i] = p1->chrom[i];
		}
		flag = -1;
	}
	for(; i <= max; i++) {
		chrom[i] = p2->chrom[i];
	}
	for(; i < PCHROM_LEN; i++) {
		for(j = min + 1; j <= max; j++) {
			if(p1->chrom[i] == p2->chrom[j]) {
				flag = j;
				break;
			}
		}
		if(flag != -1) {
			do{
				for(j = min + 1; j <= max; j++) {
					if(p2->chrom[j] == p1->chrom[flag]) {
						flag = j;
						break;
					}
				}
				if(j == max + 1) {
					chrom[i] = p1->chrom[flag];
					break;
				}
			} while(1);
		} else {
			chrom[i] = p1->chrom[i];
		}
		flag = -1;
	}
	mutate();
	fitness = DBL_MAX;
}

// ??R???
void PartialIndividual::mutate()
{
	int i, c, r1, r2;

	for(i = 0; i < PCHROM_LEN; i++) {
		if(rand() < MUTATE_PROB)
		{
			r1 = rand() % PCHROM_LEN;
			do {
				r2 = rand() % PCHROM_LEN;
			}while (r1 == r2);
			c = chrom[r1];
			chrom[r1] = chrom[r2];
			chrom[r2] = c;
		}
	}
}
