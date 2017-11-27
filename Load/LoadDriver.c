#include "Map/Map.h"
#include "User/User.h"
#include "Load/Load.h"
#include <stdio.h>

Map map;
char Filename[60];
Time time;

const int STARTING_GOLD = 50;
const int STARTING_INCOME = 5;
const int MIN_TRIBUTE = 2;
const int MAX_TRIBUTE = 5;

int main()
{
    printf("Input file name here:\n");
    scanf("%59s", Filename);
    if (validateFile(Filename, &time)) {
        printf("saved on %04d-%02d-%02d %02d:%02d:%02d\n",
        Year(time), Month(time), Day(time),
        Hour(time), Minute(time), Second(time));
        if (loadFrom(Filename, &map, &players, &nPlayers)) {
            printMap(map, 0, 0);
        }
        else printf("Loading failed.\n");
    }
    else printf("Validation failed.\n");

    return 0;
}