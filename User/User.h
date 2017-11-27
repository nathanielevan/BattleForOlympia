#ifndef BATTLEFOROLYMPIA_USER_H
#define BATTLEFOROLYMPIA_USER_H

#include "Unit/Unit.h"
#include "CircularList/CircularList.h"
#include "LinearList/LinearList.h"
#include "Queue/Queue.h"
#include "boolean.h"

typedef struct {
    int gold, income, upkeep, color;
    boolean isPlayable;
    lcList units;
    llList squares;
} Player;

extern Player *players;
extern int nPlayers;

int addUnit(int playerID, TypeID unitType);

void removeUnit(int playerID, int unitID);

Player* getPlayer(int id);

void createPlayers(const Map* map, int N);

void addSquare(int playerID, int squareID);

Queue createQueue(int nPlayers);

void delUserQueue(Queue *queue, int* i);

void changeUserTurn(Queue *queue);
#endif /* BATTLEFOROLYMPIA_USER_H */
