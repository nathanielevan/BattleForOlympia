#include "User.h"
#include "Unit.h"
#include "listsirkuler.h"

Player *players;
int nPlayers;

int addUnit(int playerID, int unitID){
    Player* player = getPlayer(playerID);
    Unit *unit = getUnit(unitID);
    unit->ownerID = playerID;
    lcInsVFirst(&player->units, unitID);
}

void removeUnit(int playerID, int unitID){
    Player *player = getPlayer(playerID);
    Unit *unit = getPlayer(unitID);
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
        player = players[i];
        player->gold = STARTING_GOLD;
        player->income = STARTING_INCOME;
        player->upkeep = 0;
        player->color = i;
        player->units = Nil;
    }
}
