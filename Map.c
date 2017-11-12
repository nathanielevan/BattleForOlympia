/*
	Body of Map
*/

#include "Map.h"
#include <stdio.h>
#include <stdlib.h>

/* Fungsi untuk membuat peta berdasarkan input tinggi dan lebar dari pengguna 
	I.S.	: map belum terdefinisi
	F.S.	: map terbentuk	*/
void createMap(int height, int width, Map* map) {
	/* Var lokal */
	int i, j;
	SquareType initType = NORMAL;
	map->squares = (Square*) calloc (height*width, sizeof(Square));
	Height(*map) = height;
	Width(*map) = width;
	for (i = 0; i < height; i++)
		for (j = 0; j < width; j++)
			Grid(*map, i, j).type = initType; 
}

/* Destruktor */

/* Fungsi untuk menghapus map */
void deleteMap(Map* map) {
	free(map->squares);
	Height(*map) = 0;
	Width(*map) = 0;
}

/* Fungsi untuk menampilkan map pada terminal */
void printMap(Map map) {
	/* Var lokal */
	int w = Width(map), h = Height(map);
	int i, j;
	/* Algoritma */
	printf("   ");
	for (i = 0; i < w; i++) {
		printf(" %2d ", i);
	}
	putchar('\n'); printf("   ");
	for (i = 0; i < h; i++) {
		for (j = 0; j < 4*w+1; j++) {
			putchar('*');
		}
		putchar('\n'); printf("   ");
		for (j = 0; j < w; j++) {
			printf("* %c ", Grid(map, i, j).type);
		}
		putchar('*'); putchar('\n');
		printf("%3d", i);
		for (j = 0; j < w; j++) {
			printf("*   ");
		}
		putchar('*'); putchar('\n'); printf("   ");
		for (j = 0; j < w; j++) {
			printf("*   ");
		}
		putchar('*'); putchar('\n'); printf("   ");
	}
	for (j = 0; j < 4*w+1; j++) {
		putchar('*');
	}
	putchar('\n');

}