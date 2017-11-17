#include "Undo.h"
#include "Unit.h"
#include "StackList/Stack.h"

typedef union {
    struct {
        short unitID;
        short delta;
    };
    int i;
} UndoStkEntry;

stkStack undoStack = { NULL };

void initUndo() {
    stkDestroy(&undoStack);
}

void registerMove(int unitID, const Map *map, Point from, Point to) {
    int deltaX = absis(to) - absis(from);
    int deltaY = ordinat(to) - ordinat(from);
    int delta = deltaX + deltaY * width(*map);
    UndoStkEntry u;
    u.delta = delta;
    u.unitID = unitID;
    stkPush(&undoStack, u.i);
}

void undo(const Map *map) {
    UndoStkEntry u;
    Unit *unit;
    int deltaX, deltaY, delta;
    stkPop(&undoStack, &u.i);
    unit = getUnit(u.unitID);
    deltaY = u.delta / width(*map);
    deltaX = u.delta % width(*map);
    delta = abs(deltaX) + abs(deltaY);
    unit->movPoints += delta;
    absis(unit->location) -= deltaX;
    ordinat(unit->location) -= deltaY;
}
