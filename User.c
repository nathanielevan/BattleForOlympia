#include "User.h"
#include "GameController.h"
#include <string.h>
#include <stdio.h>

Player *players;
int nPlayers;

int addUnit(int playerID, TypeID unitType){
    Player* player = getPlayer(playerID);
    Unit *unit;
    int unitID = createUnit(unitType);
    unit = getUnit(unitID);
    unit->ownerID = playerID;
    lcInsVLast(&player->units, unitID);
    return unitID;
}

void addSquare(int playerID, int squareID) {
    /* Get the player with the current ID */
    Player* player = getPlayer(playerID);

    /* Insert square ID into the list of square */
    llInsVFirst(&player->squares, squareID);
}

void removeUnit(int playerID, int unitID){
    Player *player = getPlayer(playerID);
    Unit *unit = getUnit(unitID);
    lcDelP(&player->units, unitID);
    unit->ownerID = 0;
}

Player* getPlayer(int id){
    if (id > nPlayers) {
        return Nil;
    } else {
        return &players[id-1];
    }
}

void createPlayers(const Map* map, int N){
    int i;
    Player *player;
    nPlayers = N;
    players = (Player *) calloc(N, sizeof(Player));
    for (i = 0; i < N; i++) {
        player = &players[i];
        player->gold = STARTING_GOLD;
        player->income = STARTING_INCOME;
        player->upkeep = 0;
        player->color = i;
        player->isPlayable = true;
        lcCreateEmpty(&player->units);
        llCreateEmpty(&player->squares);
    }
}

Queue createQueue(int nPlayers) {
    Queue queue;
    int i;
    qCreateEmpty(&queue);
    for (i = 1; i <= nPlayers; i++) {
        qAdd(&queue, i);
    }

    return queue;
}

void delUserQueue(Queue *queue, int* i) {
    qDel(queue, i);
}

void changeUserTurn(Queue *queue) {
    int i;
    qDel(queue, &i);
    qAdd(queue, i);
}