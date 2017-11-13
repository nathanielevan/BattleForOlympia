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
    int unitID;
} Square;
/*
*/

typedef struct {
    int tribute;
    POINT location;
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

#define Height(M) (M).height
#define Width(M) (M).width
#define Grid(M, i, j) (M).squares[i*((M).width)+j]

/* Konstruktor */

/* Fungsi untuk membuat peta berdasarkan input tinggi dan lebar dari pengguna 
	I.S.	: map belum terdefinisi
	F.S.	: map terbentuk	*/
void createMap(int height, int width, Map* map);

/* Destruktor */

/* Fungsi untuk menghapus map */
void deleteMap(Map* map);

/* memberikan warna sesuai dengan ID owner */
void printColor(char symbol, int ownerID); 

/* Fungsi untuk menampilkan map pada terminal */
void printMap(Map map);

#endif 