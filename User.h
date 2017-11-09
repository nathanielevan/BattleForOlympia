//
// Created by gery on 09/11/17.
//

#ifndef BATTLEFOROLYMPIA_USER_H
#define BATTLEFOROLYMPIA_USER_H

#include "Unit.h"

typedef struct {
    int id, gold, income, upkeep, color;
    Unit* units;
} Player;

#endif //BATTLEFOROLYMPIA_USER_H
