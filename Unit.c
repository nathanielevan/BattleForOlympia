/*
    Body of Unit
*/
#include "Unit.h"
#include "ListLinear/listlinier.h"

const UnitType unitTypes[] = {
        {
                .mapSymbol = 'K',
                .maxHealth = 100,
                .attack = 10,
                .defence = 7,
                .maxMovPoints = 1,
                .atkType = MELEE,
                .cost = 0},
        {
                .mapSymbol = 'A',
                .maxHealth = 100,
                .attack = 15,
                .defence = 3,
                .maxMovPoints = 1,
                .atkType = RANGED,
                .cost = 150},
        {
                .mapSymbol = 'S',
                .maxHealth = 150,
                .attack = 20,
                .defence = 4,
                .maxMovPoints = 2,
                .atkType = MELEE,
                .cost = 200},
        {
                .mapSymbol = 'W',
                .maxHealth = 75,
                .attack = 10,
                .defence = 1,
                .maxMovPoints = 1,
                .atkType = MELEE,
                .cost = 200},
};

Unit *unitPool;
int capacity;
llList freeList;

Unit *getUnit(int id) {
    if (id < 1 || id > capacity) {
        return Nil;
    } else {
        return unitPool[id - 1];
    }
}

int createUnit(const Map *map) {
    int i;
    if (capacity == 0) {
        /* initialize the unitpool */
        capacity = width(*map) * height(*map);
        unitPool = malloc(capacity * sizeof(Unit));
        for (i = capacity; i-- > 0;)
            llInsVFirst(&freeList, i);
    } else {
        if (llIsEmpty(freeList)) {
            return -1;
        } else {
            llDelVFirst(&freeList, &i);
            memset(&unitPool[i], 0, sizeof(Unit));
            return i + 1;
        }
    }
}

void destroyUnit(int id) {
    llInsVFirst(&freeList, id - 1);
}