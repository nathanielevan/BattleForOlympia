#ifndef BATTLEFOROLYMPIA_UNIT_H
#define BATTLEFOROLYMPIA_UNIT_H

#include "boolean.h"
#include "Point/Point.h"
#include "Map.h"

typedef enum { INVALID_TYPE = 0, KING, ARCHER, SWORDSMAN, WHITE_MAGE } TypeID;

typedef struct {
    int health, movPoints, ownerID;
    TypeID type;
    boolean canAttack;
    Point location;
} Unit;

typedef enum {MELEE, RANGED} AtkType;

typedef struct {
    char mapSymbol;
    const char *description;
    int maxHealth, attack, defence, maxMovPoints, cost, upkeep;
    AtkType atkType;
} UnitType;

extern const UnitType unitTypes[];

void initUnitPool(const Map *map);

/* returns pointer to unit with the specified id */
Unit *getUnit(int id);

/* returns id of newly created unit */
int createUnit(TypeID type);

/* destroy the unit */
void destroyUnit();

/* lookup a type ID by its map symbol; returns -1 if not found */
TypeID lookupTypeID(char mapSymbol);

#endif /* BATTLEFOROLYMPIA_UNIT_H */
