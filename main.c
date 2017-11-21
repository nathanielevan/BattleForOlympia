#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "GameController.h"
#include "Undo.h"
#include "User.h"
#include "Unit.h"
#include "boolean.h"


const int MISS_CHANCE = 30;
const int STARTING_GOLD = 100;
const int STARTING_INCOME = 100;

/* Var Global */
int i; //Iterating variable
int width, height, x, y;
int Enemy, myUnit;
int number_of_player, playerID, currUnitID;
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
		for(i = 1; i <= number_of_player; i++){
			/* Initialize */
			playerID = i;
			currUnitID = 0;
			currUnit = getUnit(currUnitID);
			currPlayer = getPlayer(playerID);

			printf("Player %d's Turn\n", playerID);

			printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", currPlayer->gold, currPlayer->income, currPlayer->upkeep);

			if (currUnitID != 0) {
				printf("Unit : | Movement Point : %d\n", currUnit->movPoints);
				printf("--------------------------------------------\n");
			}

			/* Input command game */
			printf("Insert your command : ");
			scanf("%s", command);
			validCommand = false;
			/* Choose action */
			while(!validCommand){
				if (command == "MOVE"){
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
						printf("Please​ ​enter​ ​cell’s​ ​coordinate​ ​x​ ​y :​ ");
						scanf("%d %d",&x,&y);
					}
					registerMove(currUnitID, &map, From, currUnit->location);
					printf("You​ ​have​ ​successfully​ ​moved​ ​to​ (%d, %d)\n", x, y);
				}else if (command == "UNDO"){
					validCommand = true;
					
					undo(&map);
					printMap(map);
				}else if (command == "CHANGE_UNIT"){
					validCommand = true;
					
					printf("=== List of Units ===\n");
				/*
				}else if (command == "RECRUIT"){
					validCommand = true;
					
					printf("Enter coordinate of empty castle : ");
					scanf("%d %d",&x,&y);
					while(Castle_Occupied){
						printf("That​ ​castle​ ​is​ ​occupied!\n");
						printf("Enter coordinate of empty castle : ");
						scanf("%d %d",&x,&y);
					}
					printf("\n");
					printf("=== List of Recruits ===\n");
					*/
				}else if (command == "ATTACK"){
					validCommand = true;
					
					initUndo();
					printf("Enemies that ​you​ ​can ​attack :\n");
					//print list
					printf("Select enemy you want to attack : ");
					scanf("%d", &Enemy);
					procBattle(&map, myUnit, Enemy);
				}else if (command == "MAP"){ //UDAH JADI
					validCommand = true;
					
					printf("\n");
					printMap(map);
					printf("\n");
				}else if (command == "INFO"){ //UDAH JADI
					validCommand = true;
					
					printf("Enter​ ​the​ ​coordinate​ ​of​ ​the​ ​cell : ");
					scanf("%d %d",&x,&y);
					printInfoSquare(x, y, map);
				}else if (command == "END_TURN"){ //UDAH JADI
					validCommand = true;

					printf("Your turn has ended.\n");
					break;
				}else if (command == "SAVE"){
					validCommand = true;
					

				}else if (command == "EXIT"){
					validCommand = true;
					

				}else printf("Wrong command!\n");
			}
		}
	}
    return 0;
}
