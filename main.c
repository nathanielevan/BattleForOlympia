#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Map.h"

/* Var Global */
int width, height;
Map map;

void initializeMap(Map* map) {
    scanf("%d %d", &height, &width);
    createMap(height, width, map);
    generateMap(4, width, height, map);
    printMap(*map);
}

int main() {
	srand(time(NULL));
    printf("Hello, World!\n");
    initializeMap(&map);
    return 0;
}