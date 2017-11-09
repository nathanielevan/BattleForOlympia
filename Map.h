//
// Created by gery on 06/11/17.
//

#ifndef BATTLEFOROLYMPIA_PETAK_H
#define BATTLEFOROLYMPIA_PETAK_H

#include "Point/Point.h"

typedef enum { NORMAL = 0, TOWER, CASTLE, VILLAGE } SquareType;

typedef struct {
    SquareType type;
    int ownerID, unitID;
} Square;

typedef struct {
    int tribute;
    POINT location;
} Village;

typedef struct {
    int height, width;
    Square* squares;
} Map;

#define Square(map, i, j) (*((map).squares[i * ((map).height) + j]))



#endif //BATTLEFOROLYMPIA_PETAK_H
