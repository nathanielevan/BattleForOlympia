#include "boolean.h"
#include "GameController.h"
#include "Point/Point.h"
#include "Unit.h"
#include "User.h"
#include "Map.h"
#include <stdlib.h>
#include <stdio.h>

boolean canMove(Unit *unit, int deltaX, int deltaY, Map *map) {

	if ((abs(deltaX) + abs(deltaY) <= unit->movPoints) &&
			isInMap(PlusDelta(unit->location, deltaX, deltaY), map))
		/* Hasilkan nilai true karena unit mampu bergerak */
		return true;
	/* Unit tidak mampu bergerak, hasilkan false */
	return false;
}

boolean isInMap (Point point, Map *map) {

	/* Check if it is in map */
	return absis(point) < width(*map) && absis(point) >= 0 && ordinat(point) < height(*map) && ordinat(point) >= 0;
}

boolean moveUnit(Map *map, int currUnitID, int deltaX, int deltaY) {

	/* Access the address of the unit with the current unit ID */
	Unit *unit = getUnit(currUnitID);

	/* Check if the unit able to do the move */
	if (canMove(unit, deltaX, deltaY, map)) {

		/* Remove the current unit from the map */
		getSquare(*map, unit->location)->unitID = 0;

		/* Translate the location of the unit with the corresponding X and Y */
		unit->location = PlusDelta(unit->location, deltaX, deltaY);

		/* Add the current unit to the new square on the map */
		getSquare(*map, unit->location)->unitID = currUnitID; 

		if (getSquare(*map, unit->location)->type == VILLAGE) {
			getSquare(*map, unit->location)->ownerID = unit->ownerID;

			Player *player = getPlayer(unit->ownerID);

			player->income += getSquare(*map, unit->location)->tribute;
		}

		/* Decrease the movement point of unit */
		unit->movPoints -= abs(deltaX) + abs(deltaY);

		/* The movement is done succesfully */
		return true;
	}

	/* The unit can't do the move */
	return false;
}

BattleResult procBattle(Map *map, int attackerID, int defenderID) {

	/* Access the address of the unit with the current unit ID */
	Unit *attacker = getUnit(attackerID);
	Unit *defender = getUnit(defenderID);

	/* Create a container for battle result */
	BattleResult battleResult;

	/* Check if the two units can battle */
	if (attacker->canAttack) {

		/* Make the attacker unable to attack */
		attacker->canAttack = false;

		/* Check if the attack missed the target */
		if ((float) rand()/RAND_MAX >= MISS_CHANCE) {
			/* The attack missed */
			battleResult.battleFlag = ATTACK_MISSED;

			/* Return the battle result */
			return battleResult;
		}

		/* Remove the defender health according to the attacker attack point */
		defender->health -= unitTypes[attacker->type].attack - unitTypes[defender->type].defence;

		/* Update the battle result */
		battleResult.defHealth = defender->health;
		battleResult.atkDamageDone = unitTypes[attacker->type].attack - unitTypes[defender->type].defence;

		/* Defender is dead */
		if (defender->health <= 0) {

			/* Remove the unit from the list of unit */
			destroyUnit(defenderID);

			/* Remove the unit from the map */
			getSquare(*map, defender->location)->unitID = 0;
		}

		/* Defender is still alive and can attack */
		else if (defender->type == KING || defender->type == attacker->type) {

			/* Attacker lose health according to the defender attack point */
			attacker->health -= unitTypes[defender->type].attack - unitTypes[attacker->type].defence;

			/* Update the battle result */
			battleResult.atkHealth = attacker->health;
			battleResult.defDamageDone = defender->health;
		}

		/* The battle occured, update battle result */
		battleResult.battleFlag = ATTACK_SUCCEED;
		return battleResult;
	}

	/* The two units can't battle */
	battleResult.battleFlag = ATTACK_NOT_PERFORMED;
	return battleResult;
}

void procHeal(Map *map, int unitID, int targetID) {
	Unit *unit = getUnit(unitID);
	Unit *target = getUnit(targetID);

	if (unit->canAttack) {
		unit->canAttack = false;
		target->health += unitTypes[unit->type].attack*3;

		if (target->health > unitTypes[target->type].maxHealth) {
			target->health = unitTypes[target->type].maxHealth;
		}
	} else {
		printf("You can't heal right now!\n");
	}
}

void getTargetID(Map *map, int attackerID, int* targetID, int* numberOfUnits) {

	/* Get the attacker address */
	Unit* attacker = getUnit(attackerID);

	Point targetLocation;

	/* Counter for the number of units */
	*numberOfUnits = 0;

	/* Check for the south square */
	if (ordinat(attacker->location) + 1 < map->height && getSquare(*map, PlusDelta(attacker->location, 0, 1))->unitID != 0) {

		/* Increase the counter for unit */
		(*numberOfUnits)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location), ordinat(attacker->location) + 1);

		/* Add the unitID to array of targetID */
		targetID[(*numberOfUnits) - 1] = getSquare(*map, targetLocation)->unitID;
	}

	/* Check for the north square */
	if (ordinat(attacker->location) - 1 >= 0 && getSquare(*map, PlusDelta(attacker->location, 0, -1))->unitID != 0) {

		/* Increase the counter for unit */
		(*numberOfUnits)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location), ordinat(attacker->location) - 1);

		/* Add the unitID to array of targetID */
		targetID[(*numberOfUnits) - 1] = getSquare(*map, targetLocation)->unitID;
	}

	/* Check for the east square */
	if (absis(attacker->location) + 1 < map->width && getSquare(*map, PlusDelta(attacker->location, 1, 0))->unitID != 0) {

		/* Increase the counter for unit */
		(*numberOfUnits)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location) + 1, ordinat(attacker->location));

		/* Add the unitID to array of targetID */
		targetID[(*numberOfUnits) - 1] = getSquare(*map, targetLocation)->unitID;
	}

	/* Check for the west square */
	if (absis(attacker->location) - 1 >= 0 && getSquare(*map, PlusDelta(attacker->location, -1, 0))->unitID != 0) {

		/* Increase the counter for unit */
		(*numberOfUnits)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location) - 1, ordinat(attacker->location));

		/* Add the unitID to array of targetID */
		targetID[(*numberOfUnits) - 1] = getSquare(*map, targetLocation)->unitID;
	}
}

RecruitOutcome recruitUnit(Map *map, int ownerID, TypeID typeID, Point castleLocation) {

	int currUnitID;

	/* Access the address of the owner with the current owner ID */
	Player *player = getPlayer(ownerID);

	/* Check if the player have enough money */
	if (player->gold < unitTypes[typeID].cost) 

		/* Player doesn't have enough gold */
		return NOT_ENOUGH_GOLD;

	/* Recruit the unit */
	currUnitID = addUnit(ownerID, typeID);

	Unit *unit = getUnit(currUnitID);

	player->gold -= unitTypes[unit->type].cost;

	player->upkeep += unitTypes[unit->type].upkeep;

	unit->location = castleLocation;

	/* Add the unit into an available castle in the map */
	getSquare(*map, castleLocation)->unitID = currUnitID;

	/* Unit successfully recruited */
	return RECRUIT_SUCCESS;

}

void AvailabeCastleLocation(Map map, int ownerID, int *castleID, int *numberOfCastle) {

	/* Access the address of the owner with the ID */
	Player *player = getPlayer(ownerID);

	/* Get the first ID in the list */
	lladdress address = llFirst(player->squares);
	/* Set the number of castle to be zero */
	*numberOfCastle = 0;

	/* Iterate through the list until empty castle is found */
	while (address != Nil) {

		/* Get the square */
		Square *square = getSquareByID(map, llInfo(address));

		/* Check if the square is a castle and empty */
		if (square->type == CASTLE && square->unitID == 0) {
			/* Increase the number of castle */
			(*numberOfCastle)++;
			/* Add the ID to the list of castle ID */
			castleID[*numberOfCastle - 1] = llInfo(address);
		}

		/* Iterate through the next address */
		address = llNext(address);
	}
}

int changeUnit(int ownerID) {
	/* Variable */
	int unitOrder, i, unitID;
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

	printf("Enter the order of unit (1-%d) : ", numberOfUnits);
	scanf("%d", &unitOrder);

	address = lcFirst(player->units);

	for (i = 0; i < unitOrder - 1; i++) {
		address = lcNext(address);
	}

	return lcInfo(address);

}
