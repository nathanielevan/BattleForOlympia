#include "boolean.h"
#include "Point.h"
#include "Unit.h"
#include "User.h"
#include "Map.h"

/* Move unit with currUnitID with appropriate direction */
/* False if the unit can't be moved as specified by the direction */
/* True if the unit have moved */
boolean moveUnit(Map *map, int currUnitID, int deltaX, int deltaY);

/* Procure battle between two units */
/* False if the fight didn't occur */
/* True if the fight occured */
boolean procBattle(Map *map, int attackerID, int defenderID);

/* Recruit and add unit to the current owner with the owner ID */
/* False if the owner can't recruit the unit */
/* True if the owner recruited the unit succesfully */
boolean recruitUnit(Map *map, int ownerID, TypeID typeID);

/* Return the location of a castle with no unit in it */
/* Return P(-1, -1) if there are no available location */
Point AvailabeCastleLocation(Map map, int ownerID);