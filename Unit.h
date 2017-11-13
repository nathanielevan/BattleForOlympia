#include "boolean.h"
#include "Point/Point.h"

#ifndef BATTLEFOROLYMPIA_UNIT_H
#define BATTLEFOROLYMPIA_UNIT_H

typedef enum { KING = 0, ARCHER, SWORDSMAN } TypeID;

typedef struct {
    int health, movPoints, ownerID;
    TypeID type;
    char* atkType;
    boolean canAttack;
    POINT location;
} Unit;

typedef enum {MELEE, RANGED} AtkType;

typedef struct {
    char mapSymbol;
    int maxHealth, attack, maxMovPoints, cost;
    AtkType atkType;
} UnitType;

extern const UnitType unitTypes[];

/* returns pointer to unit with the specified id */
Unit *getUnit(int id);

/* returns id of newly created unit */
int createUnit();

/* destroy te unit */
void destroyUnit();

#endif //BATTLEFOROLYMPIA_UNIT_H
