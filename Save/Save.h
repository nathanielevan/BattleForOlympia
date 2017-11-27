#ifndef BATTLEFOROLYMPIA_SAVE_H
#define BATTLEFOROLYMPIA_SAVE_H

#include "Map/Map.h"
#include "Unit/Unit.h"
#include "User/User.h"
#include "boolean.h"
#include <stdio.h>

/* Functions return true on success */

/* Public entry point */
boolean saveAs(const char *fname, const Map *map, const Player *players,
               const int nPlayers);

/* Internal save procedures */
boolean savePlayers(FILE *file, const Player *players, const int nPlayers);
boolean saveSquares(FILE *file, const Map *map);
boolean saveUnit(FILE *file, const int unitID);

#endif /* BATTLEFOROLYMPIA_SAVE_H */
