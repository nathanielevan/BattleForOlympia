#ifndef BATTLEFOROLYMPIA_USER_H
#define BATTLEFOROLYMPIA_USER_H

#include "Unit.h"
#include "CircularList/CircularList.h"
#include "LinearList/LinearList.h"

typedef struct {
    int id, gold, income, upkeep, color;
    lcList units;
    llList squares;
} Player;

int addUnit(int playerID, TypeID unitType);

void removeUnit(int playerID, int unitID);

Player* getPlayer(int id);

void createPlayers(const Map* map, int N);

void addSquare(int playerID, int squareID);

#endif /* BATTLEFOROLYMPIA_USER_H */
