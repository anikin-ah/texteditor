#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clipboard.h"
#include "text_buffer.h"
#include "undo_redo.h"

#define CLIP_SIZE 1000
char clipboard[CLIP_SIZE];

// Copy entire text buffer
void copyText() {
    char *snapshot = getTextSnapshot();
    strncpy(clipboard, snapshot, CLIP_SIZE);
    free(snapshot);
    printf("Copied text to clipboard.\n");
}

// Paste clipboard contents at end
void pasteText() {
    if (strlen(clipboard) == 0) {
        printf("Clipboard is empty.\n");
        return;
    }

    saveState();
    for (int i = 0; clipboard[i] != '\0'; i++)
        insertChar(clipboard[i]);
    printf("Pasted clipboard contents.\n");
}
