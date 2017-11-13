#include "Undo.h"
#include "Stack.h"

typedef union {
    struct {
        short unitID;
        short delta;
    };
    int i;
} UndoStkEntry;

Stack undoStack = Nil;

void initUndo() {
    stkDestroy(&undoStack);
}

void registerMove(int unitID, const Map *map, Point from, Point to) {
    int deltaX = Absis(to) - Absis(from);
    int deltaY = Ordinat(to) - Ordinat(from);
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
    Absis(unit->location) -= deltaX;
    Ordinat(unit->location) -= deltaY;
}
