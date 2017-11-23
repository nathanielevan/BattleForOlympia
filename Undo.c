#include "Undo.h"
#include "Unit.h"
#include "GameController.h"
#include "StackList/Stack.h"

/* UndoStkEntry defined in Stack.h */

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

boolean undo(Map *map) {
    UndoStkEntry u;
    Unit *unit;
    int deltaX, deltaY, delta;
    if (stkIsEmpty(undoStack))
        return false;
    stkPop(&undoStack, &u);
    unit = getUnit(u.unitID);
    getSquare(*map, unit->location)->ownerID = u.prevDestOwnerID;
    deltaY = u.delta / width(*map);
    deltaX = u.delta % width(*map);
    delta = abs(deltaX) + abs(deltaY);
    unit->movPoints += delta;
    moveUnit(map, u.unitID, -deltaX, -deltaY);
    unit->movPoints += delta;
    return true;
}
