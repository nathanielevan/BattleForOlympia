/*
	Driver dari Linear List untuk testing program yang hanya digunakan pada permainan
	Testing berupa Ins First Last etc...
*/

#include "LinearList.h"
#include <stdio.h>

int main() {
	llList L1;
	int i, n;

	llCreateEmpty(&L1);
	printf("Masukkan isi dari list!\n");
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		llInsVLast(&L1, i);
	}
	llPrintInfo(L1); printf("\n");
	llDelP(&L1, 8);
	llPrintInfo(L1); printf("\n");
	while(!llIsEmpty(L1)) {
		llDelVLast(&L1, &n);
	}
	if(llIsEmpty(L1)) {
		printf("L1 is empty!\n");
	}

	return 0;
}