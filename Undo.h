#ifndef BATTLEFOROLYMPIA_UNDO_H
#define BATTLEFOROLYMPIA_UNDO_H

#include "Map.h"

void initUndo();
void registerMove(int unitID, const Map *map, Point from, Point to,
                  int prevDestOwnerID);
void undo(const Map *map);

#endif /* BATTLEFOROLYMPIA_UNDO_H */
