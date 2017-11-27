/*
	Driver dari Linear List untuk testing program yang hanya digunakan pada permainan
	Testing berupa Ins First Last etc...
*/

#include "CircularList.h"
#include <stdio.h>

int main() {
	lcList L1;
	int i, n;

	lcCreateEmpty(&L1);
	printf("Masukkan isi dari list!\n");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		lcInsVLast(&L1, i);
	}
	lcPrintInfo(L1); printf("\n");
	lcDelP(&L1, 8);
	lcPrintInfo(L1); printf("\n");
	while(!lcIsEmpty(L1)) {
		lcDelVLast(&L1, &n);
	}
	if(lcIsEmpty(L1)) {
		printf("L1 is empty!\n");
	}

	return 0;
}