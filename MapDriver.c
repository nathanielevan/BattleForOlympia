/* Testing driver of the map */

#include "Unit.h"
#include "User.h"
#include "Map.h"
#include <stdio.h>

/* The constant of the game */
const float MISS_CHANCE = 0.3;
const int STARTING_GOLD = 200;
const int STARTING_INCOME = 100;

/* Global Variables */
Map map;
int currUnitID = 0, total_space = 0, numPlayer = 2;
int width, height;

/* To print the map */
void printMainMap() {
    printf("\n");
    printMap(map, currUnitID, total_space);
    printf("\n");
}

int main () {
	/* Input */
	printf("Insert map size :\n");
    printf("Width : ");
    scanf("%d", &width);
    printf("Height : ");
    scanf("%d", &height);
    /* Create the Map */
    createMap(height, width, &map);
    createPlayers(&map, numPlayer);
    initUnitPool(&map);
    /* Generate the map */
    generateMap(numPlayer, map.width, map.height, &map);
    /* Print the map */
    printMainMap();
}