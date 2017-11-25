#include "Undo.h"
#include "Unit.h"
#include "GameController.h"
#include "StackList/Stack.h"
#include <assert.h>

/* UndoStkEntry defined in Stack.h */

stkStack undoStack = { NULL };

void initUndo() {
    stkDestroy(&undoStack);
}

void registerMove(int unitID, const Map *map, Point from, Point to) {
    int deltaX = absis(to) - absis(from);
    int deltaY = ordinat(to) - ordinat(from);
    int delta = deltaX + deltaY * width(*map);
    UndoStkEntry u;
    u.unitID = unitID;
    u.delta = delta;
    u.oldMovPoints = getUnit(unitID)->movPoints;
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
    int deltaX, deltaY, delta;
    if (stkIsEmpty(undoStack))
        return false;
    stkPop(&undoStack, &u);
    unit = getUnit(u.unitID);
    getSquare(*map, unit->location)->ownerID = u.prevDestOwnerID;
    deltaY = u.delta / width(*map);
    deltaX = u.delta % width(*map);
    delta = abs(deltaX) + abs(deltaY);
    unit->movPoints = delta; /* give movpoints to reverse the motion */
    moveUnit(map, u.unitID, -deltaX, -deltaY);
    unit->movPoints = u.oldMovPoints; /* restore movpoints */
    return true;
}
