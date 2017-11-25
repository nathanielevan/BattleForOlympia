#ifndef BATTLEFOROLYMPIA_LOAD_H
#define BATTLEFOROLYMPIA_LOAD_H

#include "Map.h"
#include "Unit.h"
#include "User.h"
#include "boolean.h"

boolean loadFrom(const char *fname, Map *map, Player **players, int *nPlayers);

#endif /* BATTLEFOROLYMPIA_LOAD_H */
