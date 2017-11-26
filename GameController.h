#ifndef BATTLEFOROLYMPIA_GAMECONTROLLER_H
#define BATTLEFOROLYMPIA_GAMECONTROLLER_H

#include "boolean.h"
#include "Point/Point.h"
#include "Unit.h"
#include "User.h"
#include "Map.h"

extern const float MISS_CHANCE;
extern const int STARTING_GOLD;
extern const int STARTING_INCOME;

typedef enum { ATTACK_MISSED, ATTACK_NOT_PERFORMED, ATTACK_SUCCEED} BattleFlag;
typedef enum { NO_AVAILABE_CASTLE = 0, NOT_ENOUGH_GOLD, RECRUIT_SUCCESS } RecruitOutcome;

typedef struct {
	int defDamageDone, atkDamageDone, defHealth, atkHealth;
	BattleFlag battleFlag;
} BattleResult;

boolean canMove(Unit *unit, int deltaX, int deltaY, Map *map);

void markMoveAbleSquare(Map *map, int currUnitID);

void unmarkMoveAbleSquare(Map *map);

/* Move unit with currUnitID with appropriate direction */
/* False if the unit can't be moved as specified by the direction */
/* True if the unit have moved */
boolean moveUnit(Map *map, int currUnitID, int deltaX, int deltaY);

/* Check if the point X Y in Map */
boolean isInMap (Point point, Map *map);

/* Check if user own the king */
boolean ownKing(int playerID);

/* Reset all the attack of the unit */
void resetUnit(int ownerID);

/* Procure battle between two units */
/* False if the fight didn't occur */
/* True if the fight occured */
BattleResult procBattle(Map *map, int attackerID, int defenderID, int* ePlayerId);

/* To heal the nearby unit owned by user*/
void healNearbyUnit(lcaddress addrUnit, Map* map, int playerID); 

/* Heal nearby unit if player has mage */
void healMage(Player *currPlayer, int playerID, Map* map);

void procHeal(Map *map, int unitID, int targetID); 

void getTargetID(Map *map, int attackerID, int* targetID, int* numberOfUnits);

/* Recruit and add unit to the current owner with the owner ID */
/* False if the owner can't recruit the unit */
/* True if the owner recruited the unit succesfully */
RecruitOutcome recruitUnit(Map *map, int ownerID, TypeID typeID, Point castleLocation);

/* Return the location of a castle with no unit in it */
/* Return P(-1, -1) if there are no available location */
void AvailabeCastleLocation(Map map, int ownerID, int *castleID, int* numberOfCastle);

/* Return the unitId of the nextUnit from the list */
int nextUnit(int ownerID, int currUnitID);

/* Return the unitId of the choices of unit */
int changeUnit(int ownerID);

#endif