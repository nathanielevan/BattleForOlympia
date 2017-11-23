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
    int totalVillage = (w * h) / 8;
    int randomX, randomY, randomN;

    /* make a fixed map for player */
    for (i = 1; i <= numPlayer; i++) {
        if (i == 1) initializeGrid(map, i, 1, 1);
        else if (i == 2) initializeGrid(map, i, h - 2, w - 2);
        else if (i == 3) initializeGrid(map, i, h - 2, 1);
        else initializeGrid(map, i, 1, w - 2);
    }

    /* Time to do random */
    i = totalVillage;
    while (i > 0) {
        randomN = (rand() / (float) RAND_MAX) * w * h;
        randomX = (rand() / (float) RAND_MAX) * w;
        randomY = (rand() / (float) RAND_MAX) * h;
        printf("%d %d\n", randomX, randomY);
        if (grid(*map, randomY, randomX).ownerID == 0) {
            grid(*map, randomY, randomX).type = VILLAGE;
            i--;
        } 
    }
}

void initializeGrid(Map* map, int ownerID, int h, int w) {
    grid(*map, h - 1, w).type = CASTLE;
    grid(*map, h + 1, w).type = CASTLE;
    grid(*map, h, w - 1).type = CASTLE;
    grid(*map, h, w + 1).type = CASTLE;
    grid(*map, h, w).type = TOWER;
    grid(*map, h, w).unitID = addUnit(ownerID, KING);
    /* Get the unit location */
    Unit *unit = getUnit(grid(*map, h, w).unitID);
    unit->ownerID = ownerID;
    unit->location = MakePoint(h, w);
    /* Get the ownerID of the grid */
    grid(*map, h, w).ownerID = ownerID;
    grid(*map, h - 1, w).ownerID = ownerID;
    grid(*map, h + 1, w).ownerID = ownerID;
    grid(*map, h, w - 1).ownerID = ownerID;
    grid(*map, h, w + 1).ownerID = ownerID;
    addSquare(ownerID, grid(*map, h, w).squareID);
    addSquare(ownerID, grid(*map, h - 1, w).squareID);
    addSquare(ownerID, grid(*map, h, w - 1).squareID);
    addSquare(ownerID, grid(*map, h, w + 1).squareID);    
    addSquare(ownerID, grid(*map, h + 1, w).squareID);
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
    system("clear");
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
        /* print the top of the grid */
        for (j = 0; j < w; j++) {
            /* Print char with the associative color */
            printColor(grid(map, i, j).type, grid(map, i, j).ownerID);
        }
        putchar('*'); putchar('\n');

        /* print the center of the grid*/
        Unit* unit;
        int ownerId;
        printf("%3d", i);
        for (j = 0; j < w; j++) {
            unit = getUnit(grid(map, i, j).unitID);
            if (unit != Nil) {
                ownerId = unit->ownerID;
            } else {
                ownerId = 0;
            }
            /* Print unit symbol with the associative color */
            printColor(getUnitChar(map, i, j), ownerId);
        }
        putchar('*'); putchar('\n'); printf("   ");

        /* print the bottom of the grid */
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
    int x = (ID - 1) % width(map);
    /* Dapatkan nilai dari y */
    int y = (ID - 1) / width(map);
    /* Return nilai square yang sesuai */
    return &grid(map, x, y);
}

Point getPointByID(Map map, int ID) {
    Point P;
    /* Dapatkan nilai dari sumbu x */
    int x = (ID - 1) % width(map);
    /* Dapatkan nilai dari y */
    int y = (ID - 1) / width(map);
    P = MakePoint(x, y);
    return P;
}