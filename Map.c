/*
	Body of Map
*/

#include "Map.h"
#include "pcolor.h"
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
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			/* Initialize square value */
			Grid(*map, i, j).type = initType;
			Grid(*map, i, j).ownerID = 0;
			Grid(*map, i, j).unitID = 0; 
		}
	}
}

/* Destruktor */

/* Fungsi untuk menghapus map */
void deleteMap(Map* map) {
	/* Set the square value to default */
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
			/* Print char with the associative color */
			printColor(Grid(map, i, j).type, Grid(map, i, j).ownerID);
		}
		putchar('*'); putchar('\n');
		printf("%3d", i);
		for (j = 0; j < w; j++) {
			/* Print unit symbol with the associative color */
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

void printColor(char symbol, int ownerID) {
	switch (ownerID) {
		case 0 :
			print_red(symbol);
			break;
		case 1 :
			print_green(symbol);
			break;
		case 2 :
			print_yellow(symbol);
			break;
		case 3 :
			print_blue(symbol);
			break;
		case 4 :
			print_magenta(symbol);
			break;
		case 5 :
			print_cyan(symbol);
			break;
		default :
			printf("* %c ", symbol);
	}
}