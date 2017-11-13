#include "boolean.h"
#include "Point.h"
#include "Unit.h"
#include "User.h"
#include "Map.h"

boolean moveUnit(Map *map, int currUnitID, int deltaX, int deltaY) {

	/* Access the address of the unit with the current unit ID */
	Unit *unit = getUnit(currUnitID);

	/* Check if the unit able to do the move */
	if (abs(deltaX) + abs(deltaY) >= unit->movPoints) {

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

boolean procBattle(Map *map, int attackerID, int defenderID) {

	/* Access the address of the unit with the current unit ID */
	Unit *attacker = getUnit(attackerID);
	Unit *defender = getUnit(defenderID);

	/* Check if the two units can battle */
	if (IsNeighbor(attacker->location, defender->location) && attacker->canAttack) {

		/* Remove the defender health according to the attacker attack point */
		defender->health -= attacker->attack - defender->defence;

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
		}

		/* The battle occured */
		return true;
	}

	/* The two units can't battle */
	return false;
}

boolean recruitUnit(Map *map, int ownerID, TypeID typeID) {

	/* Access the address of the owner with the current owner ID */
	User *user = getUser(ownerID);

	/* Find the available castle location for the player */
	Point castleLocation = AvailabeCastleLocation(*map, ownerID);

	/* Check if the user have the money to buy the unit and have available castle */
	if (user->gold >= unitTypes[typeID].cost && absis(castleLocation) != -1 && 
		ordinat(castleLocation) != -1) {

		/* Recruit the unit */
		int currUnitID = addUnit(ownerID, typeID);

		/* Add the unit into an available castle in the map */
		getSquare(*map, castleLocation)->unitID = currUnitID;

		/* Unit successfully recruited */
		return true;
	}

	/* Unit can't be recruited */
	return false;
}

Point AvailabeCastleLocation(Map map, int ownerID) {

}
