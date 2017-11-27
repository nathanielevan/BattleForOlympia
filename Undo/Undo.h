#ifndef BATTLEFOROLYMPIA_UNDO_H
#define BATTLEFOROLYMPIA_UNDO_H

#include "Map/Map.h"

void initUndo();
void registerMove(int unitID, const Map *map, Point from, Point to);
void cancelMoveReg();
boolean undo(Map *map);

#endif /* BATTLEFOROLYMPIA_UNDO_H */
