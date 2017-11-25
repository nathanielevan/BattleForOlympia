/*
  Body of Unit
*/
#include "Unit.h"
#include "LinearList/LinearList.h"
#include <stdlib.h>
#include <string.h>

const UnitType unitTypes[] = {
    { '?', "MISSINGNO", 0, 0, 0, 0, MELEE, 0, 0 },
    {
        .mapSymbol = 'K',
        .description = "King",
        .maxHealth = 100,
        .attack = 10,
        .defence = 7,
        .maxMovPoints = 100,
        .atkType = MELEE,
        .cost = 0,
        .upkeep = 0},
    {
        .mapSymbol = 'A',
        .description = "Archer",
        .maxHealth = 100,
        .attack = 15,
        .defence = 3,
        .maxMovPoints = 1,
        .atkType = RANGED,
        .cost = 150,
        .upkeep = 1}, /* Spec 4e: Upkeep = number of units - king */
    {
        .mapSymbol = 'S',
        .description = "Swordsman",
        .maxHealth = 150,
        .attack = 20,
        .defence = 4,
        .maxMovPoints = 2,
        .atkType = MELEE,
        .cost = 200,
        .upkeep = 1},
    {
        .mapSymbol = 'W',
        .description = "White Mage",
        .maxHealth = 75,
        .attack = 10,
        .defence = 1,
        .maxMovPoints = 1,
        .atkType = MELEE,
        .cost = 200,
        .upkeep = 1},
};

Unit *unitPool;
int capacity;
llList freeList;

void initUnitPool(const Map *map) {
    int i;
    if (capacity == 0) {
        /* initialize the unitpool */
        capacity = width(*map) * height(*map);
        unitPool = malloc(capacity * sizeof(Unit));
        for (i = capacity; i-- > 0;) {
            llInsVFirst(&freeList, i);
        }
    }
}

Unit *getUnit(int id) {
    if (id < 1 || id > capacity) {
        return NULL;
    } else {
        return &unitPool[id - 1];
    }
}

int createUnit(TypeID typeID) {
    Unit *unit;
    const UnitType *type;
    int i;
    if (llIsEmpty(freeList)) {
        return -1;
    } else {
        llDelVFirst(&freeList, &i);
        type = &unitTypes[typeID];
        unit = &unitPool[i];
        memset(unit, 0, sizeof(Unit));
        unit->type = typeID;
        unit->health = type->maxHealth;
        unit->movPoints = type->maxMovPoints;
        unit->ownerID = 0;
        unit->canAttack = true;
        absis(unit->location) = 0;
        ordinat(unit->location) = 0;
        return i + 1;
    }
}

void destroyUnit(int id) {
    llInsVFirst(&freeList, id - 1);
}

TypeID lookupTypeID(char mapSymbol) {
    int i;
    const int nTypes = sizeof(unitTypes) / sizeof(unitTypes[0]);
    for (i = 0; i < nTypes; i++)
        if (unitTypes[i].mapSymbol == mapSymbol)
            return i;
    return -1;
}
