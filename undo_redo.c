#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "undo_redo.h"
#include "text_buffer.h"

#define MAX_STACK 1000

char *undoStack[MAX_STACK];
char *redoStack[MAX_STACK];
int undoTop = -1, redoTop = -1;

void push(char **stack, int *top, const char *state)
{
    if (*top >= MAX_STACK - 1)
        return;
    stack[++(*top)] = strdup(state);
}

char *pop(char **stack, int *top)
{
    if (*top < 0)
        return NULL;
    return stack[(*top)--];
}

// Save current state to undo stack
void saveState()
{
    char *snapshot = getTextSnapshot();
    push(undoStack, &undoTop, snapshot);
    // clear redo stack
    while (redoTop >= 0)
        free(redoStack[redoTop--]);
    free(snapshot);
}

// Undo last action
void undo()
{
    if (undoTop < 0)
    {
        printf("Nothing to undo.\n");
        return;
    }
    char *current = getTextSnapshot();
    push(redoStack, &redoTop, current);

    char *prevState = pop(undoStack, &undoTop);
    setTextFromSnapshot(prevState);

    free(prevState);
    free(current);
    printf("Undo successful.\n");
}

// Redo previously undone action
void redo()
{
    if (redoTop < 0)
    {
        printf("Nothing to redo.\n");
        return;
    }
    char *current = getTextSnapshot();
    push(undoStack, &undoTop, current);

    char *redoState = pop(redoStack, &redoTop);
    setTextFromSnapshot(redoState);

    free(redoState);
    free(current);
    printf("Redo successful.\n");
}
