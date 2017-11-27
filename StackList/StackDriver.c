#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

UndoStkEntry undoStack;
stkElement StackElmt;
stkStack Stack;

int main()
{
    undoStack.unitID = 123;
    undoStack.oldLoc.X = 100;
    undoStack.oldLoc.Y = 200;
    undoStack.oldMovPoints = 2;
    undoStack.prevDestOwnerID = 120;

    printf("Welcome to Stack! We'll create an empty stack first...\n");
    stkCreateEmpty(&Stack);
    if (stkIsEmpty(Stack)) {
        printf("An empty stack has been created.\n");
    }
    printf("We will use an already defined undoStack to test Stack.c.\n");
    printf("We'll push it in the stack.\n");
    stkPush(&Stack, undoStack);
    if (!stkIsEmpty(Stack)) {
        printf("undoStack has been pushed to the stack. Now see if we can pop it...\n");
    }
    stkPop(&Stack, &undoStack);
    if (stkIsEmpty(Stack)) {
        printf("undoStack has been popped off the stack. The stack is now empty.\n");
    }

    return 0;
}
