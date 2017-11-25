/* the main program of the games */

/* All things included */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
#include "GameController.h"
#include "Undo.h"
#include "User.h"
#include "Unit.h"
#include "Save.h"
#include "Load.h"
#include "boolean.h"
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

/* The constant of the game */
const int MISS_CHANCE = 30;
const int STARTING_GOLD = 200;
const int STARTING_INCOME = 100;

struct winsize w;

/* Var Global */
int i,k; //Iterating variable
int width, height, x, y;
int total_space;
int Enemy, myUnit, otherUnit;
int number_of_player, playerID, currUnitID, numberOfCastle;
int *castleID;
Map map;
char command[20];
Unit *currUnit;
Player *currPlayer;
boolean IsOneKing, validCommand;

/* Game commands */
void print_logo() {
	printf("\x1B[2J\x1B[1;1H");
	printf("▀█████████▄     ▄████████     ███         ███      ▄█          ▄████████         ▄████████  ▄██████▄     ▄████████  \n"); 
  	printf("  ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███         ███    ███        ███    ███ ███    ███   ███    ███        \n"); 
  	printf("  ███    ███   ███    ███    ▀███▀▀██    ▀███▀▀██ ███         ███    █▀         ███    █▀  ███    ███   ███    ███      \n"); 
 	printf(" ▄███▄▄▄██▀    ███    ███     ███   ▀     ███   ▀ ███        ▄███▄▄▄           ▄███▄▄▄     ███    ███  ▄███▄▄▄▄██▀      \n"); 
	printf("▀▀███▀▀▀██▄  ▀███████████     ███         ███     ███       ▀▀███▀▀▀          ▀▀███▀▀▀     ███    ███ ▀▀███▀▀▀▀▀       \n");     
 	printf("  ███    ██▄   ███    ███     ███         ███     ███         ███    █▄         ███        ███    ███ ▀███████████      \n");  
  	printf("  ███    ███   ███    ███     ███         ███     ███▌    ▄   ███    ███        ███        ███    ███   ███    ███        \n");    
	printf("▄█████████▀    ███    █▀     ▄████▀      ▄████▀   █████▄▄██   ██████████        ███         ▀██████▀    ███    ███      \n");       
    printf("                                                  ▀                                                     ███    ███      \n");                         
    printf(" ▄██████▄   ▄█       ▄██   ▄     ▄▄▄▄███▄▄▄▄      ▄███████▄  ▄█     ▄████████                                       \n");
    printf("███    ███ ███       ███   ██▄ ▄██▀▀▀███▀▀▀██▄   ███    ███ ███    ███    ███                                       \n");
    printf("███    ███ ███       ███▄▄▄███ ███   ███   ███   ███    ███ ███▌   ███    ███                                       \n");
    printf("███    ███ ███       ▀▀▀▀▀▀███ ███   ███   ███   ███    ███ ███▌   ███    ███                                       \n");
    printf("███    ███ ███       ▄██   ███ ███   ███   ███ ▀█████████▀  ███▌ ▀███████████                                       \n");
    printf("███    ███ ███       ███   ███ ███   ███   ███   ███        ███    ███    ███                                       \n");
    printf("███    ███ ███▌    ▄ ███   ███ ███   ███   ███   ███        ███    ███    ███                                       \n");
    printf(" ▀██████▀  █████▄▄██  ▀█████▀   ▀█   ███   █▀   ▄████▀      █▀     ███    █▀                                         \n");
    printf("           ▀ \n");
}

void printMainMap() {
	total_space = (w.ws_col-(4*width+7))/2;

	if (total_space < 0) {
		total_space = 0;
	}
	printf("\n");
	printMap(map, currUnitID, total_space);
	printf("\n");
}

void healNearbyUnit(lcaddress addrUnit, Map* map, int playerID) {
	/* Local Variabele */
	Unit *unit;
	int numberOfUnits, j;
	unit = getUnit(lcInfo(addrUnit));
	if (unit->type == WHITE_MAGE) {
		int* listOfTargetID = (int*) malloc(sizeof(int) * 4);
		getTargetID(map, lcInfo(addrUnit), listOfTargetID, &numberOfUnits);
		for (j = 0; j < numberOfUnits; j++) {
			if (unit->ownerID == playerID) {
				Unit *targetUnit = getUnit(listOfTargetID[j]);
				procHeal(map, lcInfo(addrUnit), listOfTargetID[j]);
				printf("Your %s unit just healed your %s! \n\n", unitTypes[unit->type].description, unitTypes[targetUnit->type].description);
			}
		}
		free(listOfTargetID);
	}
}

void healMage(Player *currPlayer, int playerID, Map* map) {
	/* Local Variabele */
	lcList units = currPlayer->units;
	lcaddress addrUnit = lcFirst(units);
	
	if (!lcIsEmpty(units)) {
		while (lcNext(addrUnit) != lcFirst(units)) {
			healNearbyUnit(addrUnit, map, playerID);
			addrUnit = lcNext(addrUnit);
		}
		healNearbyUnit(addrUnit, map, playerID);
	}
}

void cmdMove() {
	boolean IsCanMove;
	Point From, To;
	markMoveAbleSquare(&map, currUnitID);
	validCommand = true;
	if (currUnit->movPoints > 0) {
		printMainMap();
		printf("Please​ ​enter​ ​your unit movement (x y):​ ");
		scanf("%d %d",&x,&y);
		From = currUnit->location;
		To = PlusDelta(From, x, y);
		registerMove(currUnitID, &map, From, To);
		IsCanMove = moveUnit(&map, currUnitID, x, y);
		while(!IsCanMove){
			cancelMoveReg();
			printf("You​ ​can’t​ ​move​ ​there\n");
			printf("Please​ ​enter​ ​direction ​x​ ​y :​ ");
			scanf("%d %d",&x,&y);
			To = PlusDelta(From, x, y);
			registerMove(currUnitID, &map, From, To);
			IsCanMove = moveUnit(&map, currUnitID, x, y);
		}
		unmarkMoveAbleSquare(&map);
		printMainMap();
	} else {
		printMainMap();
		printf("Your unit can't move anymore!\n\n");
	}

	
}

void cmdUndo(){
	validCommand = true;
						
	if (!undo(&map)) {
		printMainMap();
		puts("Cannot undo move!");
		putchar('\n');
	}
}

void cmdChangeUnit(){
	validCommand = true;
	initUndo();

	printf("=== List of Units ===\n");
	currUnitID = changeUnit(playerID);
	currUnit = getUnit(currUnitID);
	printMainMap();
}

void cmdNextUnit(){
	validCommand = true;
	initUndo();
	currUnitID = nextUnit(playerID, currUnitID);
	currUnit = getUnit(currUnitID);
	printMainMap();
}

void cmdRecruit(){
	int j;

	validCommand = true;
	initUndo();
	AvailabeCastleLocation(map, playerID, castleID, &numberOfCastle);

	if (numberOfCastle > 0) {

		int currCastleID, typeID;
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
		typeID = typeID - 1 + ARCHER;

		RecruitOutcome recruitOutcome = recruitUnit(&map, playerID, typeID, castleLocation); 

		printMainMap();

		if (recruitOutcome == RECRUIT_SUCCESS) {
			printf("Recruit success! \n\n");
		}
		else if (recruitOutcome == NOT_ENOUGH_GOLD) {
			printf("You don't have enough gold to recruit unit!\n\n");
		}
	}

	else {
		printf("No empty castle\n");
	}
}

void cmdAttack(){
	validCommand = true;
	initUndo();

	int* listOfTargetID;
	listOfTargetID = (int*) malloc(sizeof(int) * 4);
	int numberOfUnits, j;
	BattleResult battleResult;
    
	getTargetID(&map, currUnitID, listOfTargetID, &numberOfUnits);
	if (numberOfUnits > 0) {
		printf("Enemies that ​you​ ​can ​attack :\n");
		for (j = 0; j < numberOfUnits; j++) {
			Unit *unit = getUnit(listOfTargetID[j]);
			printf("%d. %c (%d,%d)\n", (j + 1), unitTypes[unit->type].mapSymbol, absis(unit->location), ordinat(unit->location));
		}
		printf("Select enemy you want to attack : ");
		scanf("%d", &Enemy);

		battleResult = procBattle(&map, currUnitID, listOfTargetID[Enemy - 1]);

		printMainMap();

		if (battleResult.battleFlag == ATTACK_MISSED) 
			puts("Ow no! Your attack missed.\n");
		else if (battleResult.battleFlag == ATTACK_NOT_PERFORMED) 
			puts("Your unit is tired, it can't attack anymore.\n");
		else {
			printf("Your unit attack the enemy and inflict %d damage.\n", battleResult.atkDamageDone);
			if (battleResult.defHealth < 0) 
				puts("The enemy unit died!");
			else if (battleResult.defDamageDone > 0) {
				printf("The enemy retaliate and inflict %d damage to your unit. \n", battleResult.defDamageDone);
				if (battleResult.atkHealth < 0)
					puts("After retaliation from the enemy, your unit died!");
			}
		}
	}
	else {
		puts("There are no enemies in your sight");
	}
	free(listOfTargetID);
}

void cmdMap() {
	validCommand = true;
	printMainMap();
}

void cmdInfo() {
	validCommand = true;
	printf("Enter​ ​the​ ​coordinate​ ​of​ ​the​ ​cell : ");
	scanf("%d %d",&x,&y);
	printInfoSquare(x, y, map);
}

void cmdEndTurn() {
	validCommand = true;
	currPlayer->gold += currPlayer->income - currPlayer->upkeep;
}

/* Main Program */
int main(const int argc, const char *argv[]) {
	srand(time(NULL));
	if (argc > 1) {
		if (loadFrom("savefile.boo", &map, &players, &nPlayers)) {
			number_of_player = nPlayers;
			puts("Game restored!");
			width = width(map);
			height = height(map);

			/*Give WARNING */
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			if (4*width+4 > w.ws_col) {
				total_space = (w.ws_col-62)/2;
				for (i = 0; i < total_space; i++) {
					putchar(' ');
				}
				printf("******* WARNING: YOUR MAP IS WIDER THAN YOUR TERMINAL *******\n\n");
			}
		} else {
			puts("Loading failed!");
			return 1;
		}
	} else {
		/* Just to make it cool and some stuff */
		print_logo();
		putchar('\n');
		printf("\x1B[44m");
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		total_space = (w.ws_col - 17)/2;
		for(k = 0; k < total_space; k++) {
			putchar(' ');
		}
		printf("Start a New Game!");
		for(k = total_space + 17; k < w.ws_col; k++) {
			putchar(' ');
		}
		putchar('\n');
		printf("\x1B[0m\n");
		/* Create map */
		printf("Insert map size :\n");
		printf("Width : ");
		scanf("%d", &width);
		printf("Height : ");
		scanf("%d", &height);

		/*Give WARNING */
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		if (4*width+4 > w.ws_col) {
			total_space = (w.ws_col-62)/2;
			for (i = 0; i < total_space; i++) {
				putchar(' ');
			}
			printf("******* WARNING: YOUR MAP IS WIDER THAN YOUR TERMINAL *******\n\n");
		}
		createMap(height, width, &map);

		/* Create players */
		printf("How many players do you want : ");
		scanf("%d", &number_of_player);
		createPlayers(&map, number_of_player);

		/* Initialize unit pool */
		initUnitPool(&map);
		/* Generate the Map for the Game */
		generateMap(number_of_player, map.width, map.height, &map);
	}

	/* Initialize */
	IsOneKing = false;

	for(i = 1;; i++){
		/* Initialize */
		castleID = (int*) malloc(sizeof(int) * 4);
		playerID = i % number_of_player + !(i % number_of_player) * number_of_player;
		currPlayer = getPlayer(playerID);
		if (currPlayer->isPlayable) {
			if (!lcIsEmpty(currPlayer->units)) {
				currUnitID = lcInfo(lcFirst(currPlayer->units));
				currUnit = getUnit(currUnitID);
			} else {
				continue;
			}
			
			initUndo();
			printMainMap();
			healMage(currPlayer, playerID, &map);

			while(1) {
				printf("\x1B[42m");
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
				total_space = (w.ws_col - 19)/2;
				for(k = 0; k < total_space; k++) {
					putchar(' ');
				}
				printf("--Player %d's Turn--", playerID);
				for(k = total_space + 19; k < w.ws_col; k++) {
					putchar(' ');
				}
				printf("\x1B[0m\n");
				printf("\nCash : %dG | Income : %dG | Upkeep : %dG\n", currPlayer->gold, currPlayer->income, currPlayer->upkeep);

				if (currUnitID != 0) {
					printf("Unit : %c (%d,%d) | HP %d | Movement Point : %d\n", 
						unitTypes[currUnit->type].mapSymbol, 
						absis(currUnit->location), 
						ordinat(currUnit->location), 
						currUnit->health, 
						currUnit->movPoints);
					printf("--------------------------------------------\n\n");
				}

				/* Input command game */
				printf("Insert your command : ");
				scanf("%s", command);
				validCommand = false;

				/* Choose action */
				if (strcmp(command, "MOVE") == 0){
					cmdMove();
				}else if (strcmp(command, "UNDO") == 0){
					cmdUndo();
				}else if (strcmp(command, "CHANGE_UNIT") == 0){
					cmdChangeUnit();
				}else if (strcmp(command, "NEXT_UNIT") == 0) {
					cmdNextUnit();
				}else if (strcmp(command, "RECRUIT") == 0){
					cmdRecruit();
				}else if (strcmp(command, "ATTACK") == 0){
					cmdAttack();
				}else if (strcmp(command, "MAP") == 0){ //UDAH JADI
					validCommand = true;
					printMainMap();
					cmdAttack();
				}else if (strcmp(command, "MAP") == 0){
					cmdMap();
				}else if (strcmp(command, "INFO") == 0){
					cmdInfo();
				}else if (strcmp(command, "END_TURN") == 0) {
					if (!ownKing(playerID)) {
						currPlayer->isPlayable = false;
						/* Player is dead output something */
						/* TODO: REMOVE ALL THEIR VILLAGE */
					}
					else {
						resetUnitAttack(playerID);
						cmdEndTurn();
					}
					break;
				}else if (strcmp(command, "SAVE") == 0) {
					validCommand = true;
					saveAs("savefile.boo", &map, players, nPlayers);
					putchar('\n');
				}else if (strcmp(command, "EXIT") == 0) {
					validCommand = true;
					goto exitGame;
				}else {
					printf("Wrong command!\n");
					validCommand = true;
				}
			}
		}
	}
	exitGame :
    return 0;
}
