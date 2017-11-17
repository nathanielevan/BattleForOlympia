/*
    Body of Map
*/
#include "Map.h"
#include "pcolor.h"
#include "Unit.h"
#include "User.h"
#include <stdio.h>
#include <stdlib.h>

/* Fungsi untuk membuat peta berdasarkan input tinggi dan lebar dari pengguna 
    I.S.    : map belum terdefinisi
    F.S.    : map terbentuk */
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
            grid(*map, i, j).type = initType;
            grid(*map, i, j).ownerID = 0;
            grid(*map, i, j).unitID = 0; 
            grid(*map, i, j).squareID = i * width(*map) + j + 1;
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

/* Create Random empty Map first */
void generateMap(int numPlayer, int w, int h, Map* map) {
    int i;
    int totalVillage = (w * h) / 10;
    int randomX, randomY;

    /* make a fixed map for player */
    for (i = 1; i <= numPlayer; i++) {
        switch (i) {
            case 1:
                initializeGrid(map, i, 1, 1);
                break;
            case 2:
                initializeGrid(map, i, w - 1, h - 1);
                break;
            case 3:
                initializeGrid(map, i, w - 1, 1);
                break;
            case 4:
                initializeGrid(map, i, 1, h - 1);
                break;
        }
    }
    /* Time to do random */
    i = totalVillage;
    while (i > 0) {
        randomX = rand() % w;
        randomY = rand() % h;
        if (grid(*map, randomX, randomY).ownerID == 0) {
            grid(*map, randomX, randomY).type = VILLAGE;
            i--;
        } 
    }
}

void initializeGrid(Map* map, int ownerID, int x, int y) {
    grid(*map, x - 1, y).type = CASTLE;
    grid(*map, x, y - 1).type = CASTLE;
    grid(*map, x, y + 1).type = CASTLE;
    grid(*map, x + 1, y).type = CASTLE;
    grid(*map, x, y).type = TOWER;
    grid(*map, x, y).unitID = addUnit(ownerID, KING);
    grid(*map, x, y).ownerID = ownerID;
    grid(*map, x - 1, y).ownerID = ownerID;
    addSquare(ownerID, grid(*map, x - 1, y).squareID);
    grid(*map, x, y - 1).ownerID = ownerID;
    addSquare(ownerID, grid(*map, x, y - 1).squareID);
    grid(*map, x, y + 1).ownerID = ownerID;
    addSquare(ownerID, grid(*map, x, y + 1).squareID);
    grid(*map, x + 1, y).ownerID = ownerID;
    addSquare(ownerID, grid(*map, x + 1, y).squareID);
}

/* memberikan input mengenai informasi pada suatu koordinat x y */
void printInfoSquare(int h, int w, Map map) {

    /* Local Variables */
    Square square = grid(map, h, w);
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
            case WHITE_MAGE:
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
            printColor(grid(map, i, j).type, grid(map, i, j).ownerID);
        }
        putchar('*'); putchar('\n');
        printf("%3d", i);
        for (j = 0; j < w; j++) {
            /* Print unit symbol with the associative color */
            printColor(getUnitChar(map, i, j), grid(map, i, j).ownerID);
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

char getUnitChar(Map map, int i, int j) {
    if (grid(map, i, j).unitID != 0) 
        return unitTypes[getUnit(grid(map, i, j).unitID)->type].mapSymbol;
    else 
        return ' ';
}

void printColor(char symbol, int ownerID) {
    int color = getPlayer(ownerID)->color;
    switch (color) {
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

/* Fungsi untuk mendapatkan nilai square dari id square */
Square* getSquareByID(Map map, int ID) {
    /* Dapatkan nilai dari sumbu x */
    int x = ID / width(map);
    /* Dapatkan nilai dari y */
    int y = ID - x * width(map);
    /* Return nilai square yang sesuai */
    return &grid(map, x, y);
}