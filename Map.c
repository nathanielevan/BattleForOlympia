/*
	Body of Map
*/
#include "Map.h"
#include "pcolor.h"
#include "Unit.h"
#include <stdio.h>
#include <stdlib.h>

/* Fungsi untuk membuat peta berdasarkan input tinggi dan lebar dari pengguna 
	I.S.	: map belum terdefinisi
	F.S.	: map terbentuk	*/
void createMap(int h, int w, Map* map) {
	/* Var lokal */
	int i, j;
	SquareType initType = NORMAL;
	map->squares = (Square*) calloc (h*w, sizeof(Square));
	height(*map) = h;
	width(*map) = w;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
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
	height(*map) = 0;
	width(*map) = 0;
}

/* memberikan input mengenai informasi pada suatu koordinat x y */
void printInfoSquare(int h, int w, Map map) {

	/* Local Variables */
	Square square = Grid(Map, h, w);
	Unit* unit_type;

	if (square.unitID > 0)  unit_type = getUnit(square.unitID);	
	else unit_type = Nil;

	/* print the information from one square */
	/* print Cell Info */
	printf("== Cell Info ==\n");
	switch (square.type){
		case TOWER:
			printf("Tower\n");
			printf("Owned by Player %d\n", square.ownerID);
			break;
		case VILLAGE:
			printf("Village\n");
			printf("Owned by Player %d\n", square.ownerID);
			break;
		case CASTLE:
			printf("Castle\n");
			printf("Owned by Player %d\n", square.ownerID);
			break;
		default:
			printf("No Building here... It's just a plain field\n");
	}
	/* Print Unit Info */
	printf("== Unit Info ==\n");
	if (unit_type != Nil) {
		switch (unit_type->type){
			case KING:
				printf("King\n");
				break;
			case ARCHER:
				printf("Archer\n");
				break;
			case SWORDSMAN:
				printf("Swordsman\n");
				break;
			case WHITE_IMAGE:
				printf("White Mage\n");
		}
		printf("Owned by Player %d\n", square.ownerID);
		printf("Health %d/%d | ", unit_type->health, unitTypes[unit_type->type].maxHealth);
		printf("ATK %d | ", unitTypes[unit_type->type].attack);
		printf("DEF %d\n", unitTypes[unit_type->type].defence);
	} else {
		printf("There's no unit here..\n");
	}
}

/* Fungsi untuk menampilkan map pada terminal */
void printMap(Map map) {
	/* Var lokal */
	int w = width(map), h = height(map);
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