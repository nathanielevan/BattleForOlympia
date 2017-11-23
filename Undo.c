#include "Undo.h"
#include "Unit.h"

typedef struct {
    int unitID;
    int delta;
    int prevDestOwnerID;
} UndoStkEntry;

#define stkInfoType UndoStkEntry
#include "StackList/Stack.h"

stkStack undoStack = { NULL };

void initUndo() {
    stkDestroy(&undoStack);
}

void registerMove(int unitID, const Map *map, Point from, Point to,
                  int prevDestOwnerID) {
    int deltaX = absis(to) - absis(from);
    int deltaY = ordinat(to) - ordinat(from);
    int delta = deltaX + deltaY * width(*map);
    UndoStkEntry u;
    u.delta = delta;
    u.unitID = unitID;
    u.prevDestOwnerID = prevDestOwnerID;
    stkPush(&undoStack, u);
}

void undo(const Map *map) {
    UndoStkEntry u;
    Unit *unit;
    int deltaX, deltaY, delta;
    stkPop(&undoStack, &u);
    unit = getUnit(u.unitID);
    getSquare(*map, unit->location)->ownerID = u.prevDestOwnerID;
    deltaY = u.delta / width(*map);
    deltaX = u.delta % width(*map);
    delta = abs(deltaX) + abs(deltaY);
    unit->movPoints += delta;
    absis(unit->location) -= deltaX;
    ordinat(unit->location) -= deltaY;
}
