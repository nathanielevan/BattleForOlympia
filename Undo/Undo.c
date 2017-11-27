#include "Undo/Undo.h"
#include "Unit/Unit.h"
#include "GameController/GameController.h"
#include "StackList/Stack.h"
#include <assert.h>

/* UndoStkEntry defined in Stack.h */

stkStack undoStack = { NULL };

void initUndo() {
    stkDestroy(&undoStack);
}

void registerMove(int unitID, const Map *map, Point from, Point to) {
    Unit *unit = getUnit(unitID);
    UndoStkEntry u;
    u.unitID = unitID;
    u.oldLoc = unit->location;
    u.oldMovPoints = unit->movPoints;
    u.prevDestOwnerID = getSquare(*map, to)->ownerID;
    stkPush(&undoStack, u);
}

void cancelMoveReg() {
    UndoStkEntry u;
    assert(!stkIsEmpty(undoStack));
    stkPop(&undoStack, &u);
}

boolean undo(Map *map) {
    UndoStkEntry u;
    Unit *unit;
    int x, y, delta;
    if (stkIsEmpty(undoStack))
        return false;
    stkPop(&undoStack, &u);
    unit = getUnit(u.unitID);
    getSquare(*map, unit->location)->ownerID = u.prevDestOwnerID;
    x = absis(u.oldLoc);
    y = ordinat(u.oldLoc);
    delta = abs(absis(unit->location) - x) + abs(ordinat(unit->location) - y);
    unit->movPoints = delta; /* give movpoints to reverse the motion */
    moveUnit(map, u.unitID, x, y);
    unit->movPoints = u.oldMovPoints; /* restore movpoints */
    return true;
}
