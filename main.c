#include <stdio.h>
#include "Map.h"

/* Var Global */
int width, height;
Map map;

void initializeMap(Map* map) {
	scanf("%d %d", &height, &width);
	createMap(height, width, map);
	printMap(*map);
}

int main() {
    printf("Hello, World!\n");
    initializeMap(&map);
    return 0;
}