//
// Created by gery on 06/11/17.
//
#include "boolean.h"
#include "Point/Point.h"

#ifndef BATTLEFOROLYMPIA_UNIT_H
#define BATTLEFOROLYMPIA_UNIT_H

typedef enum { KING = 0, ARCHER, SWORDSMAN } TypeID;

typedef struct {
    int health, movPoints, id;
    TypeID type;
    char* atkType;
    boolean canAttack;
    POINT location;
} Unit;

typedef enum {MELEE, RANGED} AtkType;

typedef struct {
    char symbol;
    int maxHealth, attack, maxMovPoints, cost;
    AtkType atkType;
} UnitType;

const UnitType unitTypes[] = {
        {
                .symbol = 'K',
                .maxHealth = 100,
                .attack = 10,
                .maxMovPoints = 1,
                .atkType = MELEE,
                .cost = 0},
        {
                .symbol = 'A',
                .maxHealth = 100,
                .attack = 15,
                .maxMovPoints = 1,
                .atkType = RANGED,
                .cost = 150},
        {
                .symbol = 'S',
                .maxHealth = 150,
                .attack = 20,
                .maxMovPoints = 2,
                .atkType = MELEE,
                .cost = 200},
        {
                .symbol = 'W',
                .maxHealth = 75,
                .attack = 10,
                .maxMovPoints = 1,
                .atkType = MELEE,
                .cost = 200},
};

#endif //BATTLEFOROLYMPIA_UNIT_H
