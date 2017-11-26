/* The main program of the games */

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
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

/* The constant of the game */
const float MISS_CHANCE = 0.2;
const int STARTING_GOLD = 200;
const int STARTING_INCOME = 100;

struct winsize w;

/* Global Variable for the program */

/* Iterating variable */
int i,k; 
/* For the map */
int width, height, x, y;
Map map;
/* For printing */
int total_space;
/* For controller of the game */
int Enemy, myUnit, otherUnit, ePlayerID;
int nPlayer, totalPlayer, numberOfCastle;
int *castleID;
/* For the unit right now */
int currUnitID;
Unit *currUnit; 
/* For the player right now */
int playerID;
Player *currPlayer, *ePlayer;
/* Controller for the game */
char command[20];
Queue playersTurn;

/* Game commands */

void indent() {
    total_space = (w.ws_col-(4*width+7))/2;
	for (k = 0; k < total_space; k++) {
        putchar(' ');
    }
}

void indentButNoNeedForWidth() {
	total_space = (w.ws_col - 40)/2;
	for (k = 0; k < total_space; k++) {
        putchar(' ');
    }
}

int changeUnit(int ownerID) {
    /* Variable */
    int unitOrder, i;
    /* Access the player */
    Player *player = getPlayer(ownerID);
    /* Store the number of units */
    int numberOfUnits = 0;
    /* Get the first ID in the list */
    lcaddress address = lcFirst(player->units);
    /* Iterate through the list */
    while (1) {
        if (lcNext(address) != lcFirst(player->units)) {

            /* Access the unit */
            Unit *unit = getUnit(lcInfo(address));
            /* Increase the number of units */
            numberOfUnits++;
            /* Print unit */
            indent();
            printf("%d. %c (%d,%d) | HP %d | ATK %d | DEF %d\n", 
                numberOfUnits, 
                unitTypes[unit->type].mapSymbol, 
                absis(unit->location), ordinat(unit->location), 
                unit->health, 
                unitTypes[unit->type].attack, 
                unitTypes[unit->type].defence);

        }
        else {

            /* Access the unit */
            Unit *unit = getUnit(lcInfo(address));
            /* Increase the number of units */
            numberOfUnits++;
            /* Print unit */
            indent();
            printf("%d. %c (%d,%d) | HP %d | ATK %d | DEF %d\n", 
                numberOfUnits, 
                unitTypes[unit->type].mapSymbol, 
                absis(unit->location), ordinat(unit->location), 
                unit->health,               
                unitTypes[unit->type].attack, 
                unitTypes[unit->type].defence);

            break;
        }
        address = lcNext(address);
    }

    indent();
    printf("Enter the order of unit (1-%d) : ", numberOfUnits);
    scanf("%d", &unitOrder);

    address = lcFirst(player->units);

    for (i = 0; i < unitOrder - 1; i++) {
        address = lcNext(address);
    }
    return lcInfo(address);
}

/* Just a logo for the game */
void print_logo() {
    printf("\x1B[2J\x1B[1;1H");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("▀█████████▄     ▄████████     ███         ███      ▄█          ▄████████         ▄████████  ▄██████▄     ▄████████  \n"); 
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("  ███    ███   ███    ███ ▀█████████▄ ▀█████████▄ ███         ███    ███        ███    ███ ███    ███   ███    ███        \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    } 
    printf("  ███    ███   ███    ███    ▀███▀▀██    ▀███▀▀██ ███         ███    █▀         ███    █▀  ███    ███   ███    ███      \n"); 
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf(" ▄███▄▄▄██▀    ███    ███     ███   ▀     ███   ▀ ███        ▄███▄▄▄           ▄███▄▄▄     ███    ███  ▄███▄▄▄▄██▀      \n"); 
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("▀▀███▀▀▀██▄  ▀███████████     ███         ███     ███       ▀▀███▀▀▀          ▀▀███▀▀▀     ███    ███ ▀▀███▀▀▀▀▀       \n"); 
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }    
    printf("  ███    ██▄   ███    ███     ███         ███     ███         ███    █▄         ███        ███    ███ ▀███████████      \n");  
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("  ███    ███   ███    ███     ███         ███     ███▌    ▄   ███    ███        ███        ███    ███   ███    ███        \n");   
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    } 
    printf("▄█████████▀    ███    █▀     ▄████▀      ▄████▀   █████▄▄██   ██████████        ███         ▀██████▀    ███    ███      \n");    
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }   
    printf("                                                  ▀                                                     ███    ███      \n");     
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }                    
    printf(" ▄██████▄   ▄█       ▄██   ▄     ▄▄▄▄███▄▄▄▄      ▄███████▄  ▄█     ▄████████                                       \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("███    ███ ███       ███   ██▄ ▄██▀▀▀███▀▀▀██▄   ███    ███ ███    ███    ███                                       \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("███    ███ ███       ███▄▄▄███ ███   ███   ███   ███    ███ ███▌   ███    ███                                       \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("███    ███ ███       ▀▀▀▀▀▀███ ███   ███   ███   ███    ███ ███▌   ███    ███                                       \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("███    ███ ███       ▄██   ███ ███   ███   ███ ▀█████████▀  ███▌ ▀███████████                                       \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("███    ███ ███       ███   ███ ███   ███   ███   ███        ███    ███    ███                                       \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("███    ███ ███▌    ▄ ███   ███ ███   ███   ███   ███        ███    ███    ███                                       \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf(" ▀██████▀  █████▄▄██  ▀█████▀   ▀█   ███   █▀   ▄████▀      █▀     ███    █▀                                         \n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    printf("           ▀ \n");
}

/* To print the map */
void printMainMap() {
    /* Just a space for printing the map */
    total_space = (w.ws_col-(4*width+7))/2;

    if (total_space < 0) {
        total_space = 0;
    }
    printf("\n");
    printMap(map, currUnitID, total_space);
    printf("\n");
}

/* Make a move for the unit */
void cmdMove() {
    /* Local Variable */
    boolean IsCanMove;
    Point From, To;
    /* To mark the movement of the unit */
    markMoveAbleSquare(&map, currUnitID);
    /* Check if the unit can move */
    if (currUnit->movPoints > 0) {
        printMainMap();
        indent();
        printf("Please​ ​enter​ ​your unit movement (x y):​ ");
        scanf("%d %d",&x,&y);
        From = currUnit->location;
        To = MakePoint(x, y);
        registerMove(currUnitID, &map, From, To);
        IsCanMove = moveUnit(&map, currUnitID, x, y);
        while (!IsCanMove) {
            cancelMoveReg();
            indent();
            printf("You​ ​can’t​ ​move​ ​there\n");
            indent();
            printf("Please​ ​enter​ ​direction ​x​ ​y :​ ");
            scanf("%d %d",&x,&y);
            To = MakePoint(x, y);
            registerMove(currUnitID, &map, From, To);
            IsCanMove = moveUnit(&map, currUnitID, x, y);
        }
        unmarkMoveAbleSquare(&map);
        printMainMap();
    } else {
        printMainMap();
        indent();
        printf("Your unit can't move anymore!\n\n");
    }
}

/* Make an undo move for the unit */
/* Undo only when player use command MOVE */
void cmdUndo(){
    /* Check if it can undo */                    
    if (!undo(&map)) {
        printMainMap();
        indent();
        puts("Cannot undo move!");
        putchar('\n');
    } else {
        printMainMap();
    }
}

/* Change a unit to another unit of same id */
void cmdChangeUnit(){
    initUndo();
    indent();
    printf("=== List of Units ===\n");
    currUnitID = changeUnit(playerID);
    currUnit = getUnit(currUnitID);
    printMainMap();
}

/* Check the next unit of owned unit */
void cmdNextUnit(){
    initUndo();
    currUnitID = nextUnit(playerID, currUnitID);
    currUnit = getUnit(currUnitID);
    printMainMap();
}

/* Recruit new unit and check if player can recruit */
void cmdRecruit(){
    /* Local Variable */
    int j;
    int currCastleID, typeID;
    Point castleLocation;

    initUndo();
    AvailabeCastleLocation(map, playerID, castleID, &numberOfCastle);
    /* Check if there is available castle */
    if (numberOfCastle > 0) {
    	indent();
        printf("=== List of Available Castle Location ===\n");
        /* Iteration through the castle */
        for (j = 0; j < numberOfCastle; j++) {
            castleLocation = getPointByID(map, castleID[j]);
            /* Print the castle */
            indent();
            printf("%d. (%d,%d)\n", (j + 1), absis(castleLocation), ordinat(castleLocation));
        }

        indent();
        printf("Enter the number of castle (1-%d) : ", numberOfCastle);
        scanf("%d", &currCastleID);

        castleLocation = getPointByID(map, castleID[currCastleID - 1]);

        /* Print list of recruitable unit */
        indent();
        printf("============= List of Recruitable Units ============\n");
        indent();
        printf("1. Archer   | HP 100 | ATK 15 | DEF 3 | GOLD 150\n");
        indent();
        printf("2. Swordsman    | HP 150 | ATK 20 | DEF 4 | GOLD 200\n");
        indent();
        printf("3. White Mage   | HP 75  | ATK 10 | DEF 1 | GOLD 200\n");
        indent();
        printf("Enter the type of unit (1-3) : ");
        /* Read the Input */
        scanf("%d", &typeID);
        typeID = typeID - 1 + ARCHER;
        RecruitOutcome recruitOutcome = recruitUnit(&map, playerID, typeID, castleLocation); 
        /* Print the new map */
        printMainMap();
        /* Check if recruit is success */
        if (recruitOutcome == RECRUIT_SUCCESS) {
        	indent();
            printf("Recruit success! \n\n");
        }
        else if (recruitOutcome == NOT_ENOUGH_GOLD) {
        	indent();
            printf("You don't have enough gold to recruit unit!\n\n");
        }
    }
    else {
    	indent();
        printf("No empty castle\n");
    }
}

/* Command unit to attack another nearby (adjacent) unit */
void cmdAttack(){
    /* Local Variable */
    int* listOfTargetID;
    listOfTargetID = (int*) malloc(sizeof(int) * 4);
    int numberOfUnits, j;
    BattleResult battleResult;
    
    initUndo();
    /* Get the list of target */
    getTargetID(&map, currUnitID, listOfTargetID, &numberOfUnits);
    if (numberOfUnits > 0) {
        /* Show the enemies you can attack */
        indent();
        printf("Enemies that ​you​ ​can ​attack :\n");
        for (j = 0; j < numberOfUnits; j++) {
            Unit *unit = getUnit(listOfTargetID[j]);
            printf("%d. %c (%d,%d)\n", (j + 1), unitTypes[unit->type].mapSymbol, absis(unit->location), ordinat(unit->location));
        }
        Enemy = 0;
        /* Input the correct one */
        while ((Enemy > numberOfUnits) || (Enemy <= 0)) {
        	indent();
            printf("Select enemy you want to attack : ");
            scanf("%d", &Enemy);
        }

        /* Get the result of the battle */
        battleResult = procBattle(&map, currUnitID, listOfTargetID[Enemy - 1], &ePlayerID);
        /* Print the new map */
        printMainMap();

        /* All scenes you can get */
        if (battleResult.battleFlag == ATTACK_MISSED) {
        	indent();
            puts("Ow no! Your attack missed.\n");
        }
        else if (battleResult.battleFlag == ATTACK_NOT_PERFORMED) {
        	indent();
            puts("Your unit is tired, it can't attack anymore.\n");
        }
        else {
        	indent();
            printf("Your unit attack the enemy and inflict %d damage.\n", battleResult.atkDamageDone);
            if (battleResult.defHealth < 0) {
            	indent();
                puts("The enemy unit died!");
            }
            else if (battleResult.defDamageDone > 0) {
            	indent();
                printf("The enemy retaliate and inflict %d damage to your unit. \n\n", battleResult.defDamageDone);
                if (battleResult.atkHealth < 0) {
                	indent();
                    puts("After retaliation from the enemy, your unit died!\n\n");
                }
            }
        }
    }
    else {
    	indent();
        puts("There are no enemies in your sight");
        ePlayerID = 1;
        putchar('\n');
    }
    /* Free the memory for efficiency */
    free(listOfTargetID);
}

void printInfoSquare(int w, int h, Map map) {

    /* Local Variables */
    Square square = grid(map, h, w);
    Unit* unit;

    if (square.unitID > 0)  unit = getUnit(square.unitID); 
    else unit = Nil;

    /* print the information from one square */
    /* print Cell Info */
    indent();
    printf("== Cell Info ==\n");
    switch (square.type){
        case TOWER:
        	indent();
            printf("Tower\n");
            indent();
            printf("Owned by Player %d\n", square.ownerID);
            break;
        case VILLAGE:
        	indent();
            printf("Village\n");
            indent();
            printf("Owned by Player %d\n", square.ownerID);
            break;
        case CASTLE:
        	indent();
            printf("Castle\n");
            indent();
            printf("Owned by Player %d\n", square.ownerID);
            break;
        default:
        	indent();
            printf("No Building here... It's just a plain field\n");
    }
    /* Print Unit Info */
    indent();
    printf("== Unit Info ==\n");
    if (unit != Nil) {
    	indent();
        printf("%s\n", unitTypes[unit->type].description);
        indent();
        printf("Owned by Player %d\n", square.ownerID);
        indent();
        printf("Health %d/%d | ", unit->health, unitTypes[unit->type].maxHealth);
        printf("ATK %d | ", unitTypes[unit->type].attack);
        printf("DEF %d\n", unitTypes[unit->type].defence);
    } else {
    	indent();
        printf("There's no unit here..\n");
    } 
}

/* Give the information of the square of the map */
void cmdInfo() {
	indent();
    printf("Enter​ ​the​ ​coordinate​ ​of​ ​the​ ​cell : ");
    scanf("%d %d",&x,&y);
    printMainMap();
    printInfoSquare(x, y, map);
    putchar('\n');
}

/* End the player's turn */
void cmdEndTurn() {
    currPlayer->gold += currPlayer->income - currPlayer->upkeep;
}

/* Check if the game is done and find the winning player */
void checkWin() {
    for (i = 1; i <= totalPlayer; i++) {
        currPlayer = getPlayer(i);
        if (currPlayer->isPlayable) {
            break;
        }
    }
    indent();
    printf("\nCONGRATS!\n After a very long battle.... Player %d has won the game !\n", i);
}

/* Print all the available commands */
void printCommandAvailable() {
	indent();
    printf("AVAILABLE COMMANDS : \n"); 
    indent();
    printf("MOVE | CHANGE_UNIT | NEXT_UNIT | MAP | INFO | SAVE | EXIT | END_TURN | RECRUIT | UNDO\n\n");
}

/* Main Program */
int main(const int argc, const char *argv[]) {
    srand(time(NULL));
    /* Just to make it cool and some stuff */
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    total_space = (w.ws_col - 40)/2;
    print_logo(); putchar('\n');
    for (k = 0; k < total_space; k++) {
        putchar(' ');
    }
    /* Choice to start or load game */
    printf("START NEW GAME (START) | LOAD GAME (LOAD)\n\n");
    for (k = 0; k < total_space / 2; k++) {
        putchar(' ');
    }
    scanf("%s", command);
    /* Program will load if user choose load */
    if (strcmp(command, "LOAD") == 0) {
        if (loadFrom("savefile.boo", &map, &players, &nPlayers)) {
            totalPlayer = nPlayers;
            indent();
            puts("Game restored!");
            width = width(map);
            height = height(map);
            nPlayer = totalPlayer;           
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
        	indent();
            puts("Loading failed!");
            return 1;
        }
    } else {
        /* Start the Game */
        printf("\x1B[2J\x1B[1;1H");
        printf("\x1B[44m");
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        total_space = (w.ws_col - 17)/2;
        for (k = 0; k < total_space; k++) {
            putchar(' ');
        }
        printf("Start a New Game!");
        for (k = total_space + 17; k < w.ws_col; k++) {
            putchar(' ');
        }
        putchar('\n');
        printf("\x1B[0m\n");
        /* Create the map */
		indentButNoNeedForWidth();
        printf("Insert map size :\n");
        indentButNoNeedForWidth();
        printf("Width : ");
        scanf("%d", &width);
        indentButNoNeedForWidth();
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
        indentButNoNeedForWidth();
        printf("How many players do you want : ");
        scanf("%d", &totalPlayer);
        createPlayers(&map, totalPlayer);
        nPlayer = totalPlayer;

        /* Initialize unit pool */
        initUnitPool(&map);
        /* Generate the Map for the Game */
        generateMap(totalPlayer, map.width, map.height, &map);
    }
    /*Initialize playerID to 0 */
    playerID = 0; 

    /* Creater the player's turn */
    playersTurn = createQueue(totalPlayer);

    /* The main loop of the program */
    while (nPlayer > 1) {
        /* Initialize */
        castleID = (int*) malloc(sizeof(int) * 4 * (totalPlayer-1));
        playerID = qInfoHead(playersTurn);
        currPlayer = getPlayer(playerID);

        while (!currPlayer->isPlayable) {
            changeUserTurn(&playersTurn);
            playerID = qInfoHead(playersTurn);
            currPlayer = getPlayer(playerID);
        }

        if (currPlayer->isPlayable) {
            currUnitID = lcInfo(lcFirst(currPlayer->units));
            currUnit = getUnit(currUnitID);
        } 

        initUndo();
        printMainMap();
        healMage(currPlayer, playerID, &map);

        while(1) {
            printf("\x1B[42m");
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
            total_space = (w.ws_col - 19)/2;
            for (k = 0; k < total_space; k++) {
                putchar(' ');
            }
            printf("--Player %d's Turn--", playerID);
            for (k = total_space + 19; k < w.ws_col; k++) {
                putchar(' ');
            }
            printf("\x1B[0m\n");
            puts("");
            indent();
            printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", currPlayer->gold, currPlayer->income, currPlayer->upkeep);

            if (currUnitID != 0) {
            	indent();
                printf("Unit : %c (%d,%d) | HP %d | Movement Point : %d\n", 
                    unitTypes[currUnit->type].mapSymbol, 
                    absis(currUnit->location), 
                    ordinat(currUnit->location), 
                    currUnit->health, 
                    currUnit->movPoints);
               	indent();
                printf("--------------------------------------------\n");
            }
            /* Print the available Command */
            printCommandAvailable();

            /* Input command game */
            indent();
            printf("Insert your command : ");
            scanf("%s", command);

            /* Choose action */
            if (strcmp(command, "MOVE") == 0){
                cmdMove();
            } else if (strcmp(command, "UNDO") == 0){
                cmdUndo();
            } else if (strcmp(command, "CHANGE_UNIT") == 0){
                cmdChangeUnit();
            } else if (strcmp(command, "NEXT_UNIT") == 0) {
                cmdNextUnit();
            } else if (strcmp(command, "RECRUIT") == 0){
                cmdRecruit();
            } else if (strcmp(command, "ATTACK") == 0){
                cmdAttack();
                /* When your king is dead */
                if (!ownKing(playerID)) {
                    sleep(2);
                    currPlayer->isPlayable = false;
                    nPlayer--;
                    deleteOwner(playerID, &map);
                    printMainMap();
                /* When enemy's king is dead */
                } else if (!ownKing(ePlayerID)) {
                    sleep(2);
                    ePlayer = getPlayer(ePlayerID);
                    ePlayer->isPlayable = false;
                    nPlayer--;
                    deleteOwner(ePlayerID, &map);
                    printMainMap();
                }
                if (nPlayer <= 1) goto afterWin;
            } else if (strcmp(command, "MAP") == 0){ //UDAH JADI
                printMainMap();
            } else if (strcmp(command, "INFO") == 0){
                cmdInfo();
            } else if (strcmp(command, "END_TURN") == 0) {
                resetUnit(playerID);
                changeUserTurn(&playersTurn);
                cmdEndTurn();
                break;
            } else if (strcmp(command, "SAVE") == 0) {
                saveAs("savefile.boo", &map, players, nPlayers);
                printMainMap();
                printf("Your file was saved !\n");
                putchar('\n');
            } else if (strcmp(command, "EXIT") == 0) {
                goto exitGame;
            } else {
                printf("You input the wrong command!\n\n");
            }
        }

        free(castleID);
    }
    /* Label last */
    afterWin:
    checkWin();
    exitGame :
    return 0;
}
