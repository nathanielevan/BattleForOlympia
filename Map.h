/*
    Header for Map
*/
#ifndef BATTLEFOROLYMPIA_PETAK_H
#define BATTLEFOROLYMPIA_PETAK_H

#include "Point/Point.h"

typedef enum { NORMAL = ' ', TOWER = 'T', CASTLE = 'C', VILLAGE = 'V'} SquareType;

typedef struct {
    int ownerID;
    SquareType type;
    int squareID;
    int unitID;
} Square;
/*
*/

typedef struct {
    int tribute;
    Point location;
} Village;
/*
*/

typedef struct {
    int height;
    int width;
    Square* squares;
} Map;
/*
*/

#define height(M) (M).height
#define width(M) (M).width
#define grid(M, i, j) (M).squares[i*((M).width)+j]
#define getSquare(M, p) (&grid((M), absis(p), ordinat(p)))

/* Konstruktor */

/* Fungsi untuk membuat peta berdasarkan input tinggi dan lebar dari pengguna 
    I.S.    : map belum terdefinisi
    F.S.    : map terbentuk */
void createMap(int height, int width, Map* map);

/* Destruktor */

/* Fungsi untuk menghapus map */
void deleteMap(Map* map);

/* Create Random empty Map first */
void generateMap(int numPlayer, int w, int h, Map* map);

void initializeGrid(Map* map, int ownerID, int x, int y);
/* Aksesor */

/* memberikan input mengenai informasi pada suatu koordinat x y */
void printInfoSquare(int h, int w, Map map);

/* Fungsi untuk menampilkan map pada terminal */
void printMap(Map map);

/* Fungsi untuk mendapatkan simbol character Unit*/
char getUnitChar(Map map, int i, int j);

/* memberikan warna sesuai dengan ID owner */
void printColor(char symbol, int ownerID); 

Square* getSquareByID(Map map, int ID);

#endif 
