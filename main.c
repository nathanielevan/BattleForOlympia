#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "GameController.h"
#include "Undo.h"
#include "User.h"
#include "Unit.h"
#include "boolean.h"
#include <string.h>


const int MISS_CHANCE = 30;
const int STARTING_GOLD = 100;
const int STARTING_INCOME = 100;

/* Var Global */
int i; //Iterating variable
int width, height, x, y;
int Enemy, myUnit;
int number_of_player, playerID, currUnitID, numberOfCastle;
int *castleID;
Map map;
char command[20];
Unit *currUnit;
Player *currPlayer;
boolean IsOneKing, validCommand;


int main() {
    srand(time(NULL));
    printf("Start a New Game!\n");

	/* Create map */
	printf("Insert map size :\n");
	printf("Width : ");
	scanf("%d", &width);
	printf("Height : ");
	scanf("%d", &height);
	createMap(height, width, &map);

	/* Create players */
	printf("How many players do you want : ");
	scanf("%d", &number_of_player);
	createPlayers(&map, number_of_player);

	/* Initialize unit pool */
	initUnitPool(&map);

	generateMap(number_of_player, map.width, map.height, &map);

	printMap(map);

	/* Initialize */
	IsOneKing = false;

	while(!IsOneKing){
		for(i = 1;; i++){
			/* Initialize */
			playerID = i % number_of_player;
			currUnitID = 0;
			currUnit = getUnit(currUnitID);
			currPlayer = getPlayer(playerID);
			castleID = (int*) malloc(sizeof(int) * 4);

			printf("Player %d's Turn\n", playerID);

			while(1) {
				printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", currPlayer->gold, currPlayer->income, currPlayer->upkeep);

				if (currUnitID != 0) {
					printf("Unit : %c | Movement Point : %d\n", unitTypes[currUnit->type].mapSymbol, currUnit->movPoints);
					printf("--------------------------------------------\n");
				}
				/* Input command game */
				printf("Insert your command : ");
				scanf("%s", command);
				validCommand = false;
				/* Choose action */
				while(!validCommand){
					if (strcmp(command, "MOVE") == 0){
						boolean IsCanMove;
						Point From, To;
						validCommand = true;

						printf("\n");
						printMap(map);
						printf("\n");
						printf("Please​ ​enter​ ​cell’s​ ​coordinate​ ​x​ ​y :​ ");
						scanf("%d %d",&x,&y);
						From = currUnit->location;
						IsCanMove = moveUnit(&map, currUnitID, x, y);
						while(!IsCanMove){
							printf("You​ ​can’t​ ​move​ ​there\n");
							printf("Please​ ​enter​ ​direction ​x​ ​y :​ ");
							scanf("%d %d",&x,&y);
							IsCanMove = moveUnit(&map, currUnitID, x, y);
						}
						registerMove(currUnitID, &map, From, currUnit->location);
						printf("You​ ​have​ ​successfully​ ​moved​ ​to​ (%d, %d)\n", x, y);
					}else if (strcmp(command, "UNDO") == 0){
						validCommand = true;
						
						undo(&map);
						printMap(map);
					}else if (strcmp(command, "CHANGE_UNIT") == 0){
						validCommand = true;
						
						printf("=== List of Units ===\n");
						currUnitID = changeUnit(playerID);

						currUnit = getUnit(currUnitID);

					}else if (strcmp(command, "RECRUIT") == 0){
						validCommand = true;
						
						AvailabeCastleLocation(map, playerID, castleID, &numberOfCastle);

						int j;

						if (numberOfCastle > 0) {

							int currCastleID, typeID;
							Square *square;
							Point castleLocation;

							printf("=== List of Availabe Castle Location ===\n");

							for (j = 0; j < numberOfCastle; j++) {
								castleLocation = getPointByID(map, castleID[j]);
								/* Print the castle */
								printf("%d. (%d,%d)\n", (j + 1), absis(castleLocation), ordinat(castleLocation));
							}

							printf("Enter the number of castle (1-%d) : ", numberOfCastle);
							scanf("%d", &currCastleID);

							castleLocation = getPointByID(map, castleID[currCastleID - 1]);

							/* Print list of recruitable unit */
							printf("============= List of Recruitable Units ============\n");
							printf("1. Archer 	| HP 100 | ATK 15 | DEF 3 | GOLD 150\n");
							printf("2. Swordsman	| HP 150 | ATK 20 | DEF 4 | GOLD 200\n");
							printf("3. White Mage 	| HP 75  | ATK 10 | DEF 1 | GOLD 200\n");
							printf("Enter the type of unit (1-3) : ");
							scanf("%d", &typeID);

							RecruitOutcome recruitOutcome = recruitUnit(&map, playerID, typeID, castleLocation); 

							if (recruitOutcome == RECRUIT_SUCCESS) {
								printf("Recruit success\n");
							}
							else if (recruitOutcome == NOT_ENOUGH_GOLD) {
								printf("Not enough gold to recruit unit\n");
							}
						}

						else {
							printf("No empty castle\n");
						}

					}else if (strcmp(command, "ATTACK") == 0){
						validCommand = true;
						int* listOfTargetID;
						listOfTargetID = (int*) malloc(sizeof(int) * 4);
						int numberOfUnits, j;
						initUndo();
						printf("Enemies that ​you​ ​can ​attack :\n");
						getTargetID(&map, currUnitID, listOfTargetID, &numberOfUnits);
						for (int j = 0; j < numberOfUnits; j++) {
							Unit *unit = getUnit(listOfTargetID[j]);
							printf("%d. %c (%d,%d)\n", (j + 1), unitTypes[unit->type].mapSymbol, absis(unit->location), ordinat(unit->location));
						}
						printf("Select enemy you want to attack : ");
						scanf("%d", &Enemy);
						procBattle(&map, listOfTargetID[Enemy - 1], currUnitID);
					}else if (strcmp(command, "MAP") == 0){ //UDAH JADI
						validCommand = true;
						
						printf("\n");
						printMap(map);
						printf("\n");
					}else if (strcmp(command, "INFO") == 0){ //UDAH JADI
						validCommand = true;
						
						printf("Enter​ ​the​ ​coordinate​ ​of​ ​the​ ​cell : ");
						scanf("%d %d",&x,&y);
						printInfoSquare(x, y, map);
					}else if (strcmp(command, "END_TURN") == 0) { //UDAH JADI
						validCommand = true;

						printf("Your turn has ended.\n");
						break;
					}else if (strcmp(command, "SAVE") == 0) {
						validCommand = true;
						

					}else if (strcmp(command, "EXIT") == 0) {
						validCommand = true;
						

					}else printf("Wrong command!\n");
				}
			}
		}
	}
    return 0;
}
