#include "boolean.h"
#include "GameController.h"
#include "Point.h"
#include "Unit.h"
#include "User.h"
#include "Map.h"
#include <stdlib.h>

boolean canMove(int currUnitID, int deltaX, int deltaY) {
	if (abs(deltaX) + abs(deltaY) >= unit->movPoints) &&
		PlusDelta(unit->location, deltaX, deltaY) 
		/* Hasilkan nilai true karena unit mampu bergerak */
		return true;
	/* Unit tidak mampu bergerak, hasilkan false */
	return false;
}

boolean moveUnit(Map *map, int currUnitID, int deltaX, int deltaY) {

	/* Access the address of the unit with the current unit ID */
	Unit *unit = getUnit(currUnitID);

	/* Check if the unit able to do the move */
	if (canMove(currUnitID, deltaX, deltaY)) {

		/* Remove the current unit from the map */
		getSquare(*map, unit->location)->currUnitID = 0;

		/* Translate the location of the unit with the corresponding X and Y */
		unit->location = PlusDelta(unit->location, deltaX, deltaY);

		/* Add the current unit to the new square on the map */
		getSquare(*map, unit->location)->unitID = currUnitID; 

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
			battleResult.battleFlag = MISSED;

			/* Return the battle result */
			return battleResult;
		}

		/* Remove the defender health according to the attacker attack point */
		defender->health -= attacker->attack - defender->defence;

		/* Update the battle result */
		battleResult.defHealth = defender->health;
		battleResult.atkDamageDone = attacker->attack - defender->defence;

		/* Defender is death */
		if (defender->health <= 0) {

			/* Remove the unit from the list of unit */
			destroyUnit(defenderID);

			/* Remove the unit from the map */
			getSquare(*map, unit->location)->unitID = 0;
		}

		/* Defender is still alive and can attack */
		else if (defender->type == KING || defender->type == attacker->type) {

			/* Attacker lose health according to the defender attack point */
			attacker->health -= defender->attack - attacker->defence;

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

void getTargetID(Map *map, int attackerID, int* targetID, int* numberOfUnits) {

	/* Get the attacker address */
	Unit* attacker = getUnit(attackerID);

	Point targetLocation;

	/* Counter for the number of units */
	numberOfUnits* = -1;

	/* Check for the south square */
	if (ordinat(attacker->location) + 1 < map->height) {

		/* Increase the counter for unit */
		(numberOfUnits*)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location), ordinat(attacker->location) + 1);

		/* Add the unitID to array of targetID */
		targetID[(numberOfUnits*)] = getSquare(*map, targetLocation)->unitID;
	}

	/* Check for the north square */
	if (ordinat(attacker->location) - 1 >= 0) {

		/* Increase the counter for unit */
		(numberOfUnits*)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location), ordinat(attacker->location) - 1);

		/* Add the unitID to array of targetID */
		targetID[(numberOfUnits*)] = getSquare(*map, targetLocation)->unitID;
	}

	/* Check for the east square */
	if (absis(attacker->location) + 1 < map->width) {

		/* Increase the counter for unit */
		(numberOfUnits*)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location) + 1, ordinat(attacker->location));

		/* Add the unitID to array of targetID */
		targetID[(numberOfUnits*)] = getSquare(*map, targetLocation)->unitID;
	}

	/* Check for the west square */
	if (absis(attacker->location) - 1 >= 0) {

		/* Increase the counter for unit */
		(numberOfUnits*)++;

		/* Get the target location */
		targetLocation = MakePoint(absis(attacker->location) - 1, ordinat(attacker->location));

		/* Add the unitID to array of targetID */
		targetID[(numberOfUnits*)] = getSquare(*map, targetLocation)->unitID;
	}
}

RecruitOutcome recruitUnit(Map *map, int ownerID, TypeID typeID) {

	/* Access the address of the owner with the current owner ID */
	User *user = getUser(ownerID);

	/* Find the available castle location for the player */
	Point castleLocation = AvailabeCastleLocation(*map, ownerID);

	/* Check if the user have enough money */
	if (user->gold >= unitTypes[typeID].cost) 

		/* User doesn't have enough gold */
		return NOT_ENOUGH_GOLD;
	

	/* Check if the user have empty castle */
	if (absis(castleLocation) != -1 && ordinat(castleLocation) != -1)

		/* User doesn't have empty castle */
		return NO_AVAILABE_CASTLE;


	/* Recruit the unit */
	int currUnitID = addUnit(ownerID, typeID);

	/* Add the unit into an available castle in the map */
	getSquare(*map, castleLocation)->unitID = currUnitID;

	/* Unit successfully recruited */
	return RECRUIT_SUCCESS;

}

Point AvailabeCastleLocation(Map map, int ownerID) {

	/* Access the address of the owner with the ID */
	User *user = getUser(ownerID);

	/* Get the first ID in the list */
	lladdress address = llFirst(user->squares)

	/* Iterate through the list until empty castle is found */
	while (!llIsEmpty(address)) {

		/* Get the square */
		Square *square = getSquareByID(map, llInfo(address));

		/* Check if the square is a castle and empty */
		if (square->type == CASTLE && square->unitID == 0) {

			/* Return the location of the square */
			return square->location;
		}

		/* Iterate through the next address */
		address = llNext(address);
	}

	/* Return empty point */
	Point castleLocation = MakePoint(0, 0);

	return castleLocation;
}
