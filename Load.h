#ifndef BATTLEFOROLYMPIA_LOAD_H
#define BATTLEFOROLYMPIA_LOAD_H

#include "Map.h"
#include "User.h"
#include "Time/Time.h"
#include "boolean.h"

boolean loadFrom(const char *fname, Map *map, Player **players, int *nPlayers);
boolean validateFile(const char *fname, Time *saveTime);

#endif /* BATTLEFOROLYMPIA_LOAD_H */
