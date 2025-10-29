#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_buffer.h"

//static Node *head = NULL;
static Node *cursor = NULL; // New: tracks cursor position
static int cursorAfterEnd = 0; // 0 = normal, 1 = after end

Node *head = NULL;

// Insert at the end (append mode)
void insertChar(char c) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->ch = c;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        cursor = newNode;
        return;
    }

    if (cursor == NULL) {
        newNode->next = head;
        head = newNode;
        cursor = newNode;
        return;
    }

    newNode->next = cursor->next;
    cursor->next = newNode;
    cursor = newNode;
}

// Delete last character
void deleteChar() {
    if (head == NULL || cursor == NULL) return;

    if (cursor == head) {
        Node *temp = head;
        head = head->next;
        free(temp);
        cursor = head;
        return;
    }

    Node *temp = head;
    while (temp->next != cursor)
        temp = temp->next;

    temp->next = cursor->next;
    free(cursor);
    cursor = temp;
}

void moveCursorLeft() {
    if (head == NULL) return;

    // If cursor is after end, just move to last node
    if (cursorAfterEnd) {
        Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        cursor = temp;
        cursorAfterEnd = 0;
        return;
    }

    // If cursor is before first char, can't move further
    if (cursor == NULL) return;

    // Move left normally
    if (cursor == head) {
        cursor = NULL;
        return;
    }

    Node *temp = head;
    while (temp->next != cursor)
        temp = temp->next;
    cursor = temp;
}

void moveCursorRight() {
    if (head == NULL) return;

    // If cursor is before first char
    if (cursor == NULL) {
        cursor = head;
        return;
    }

    // If already after end, can’t go further
    if (cursorAfterEnd) return;

    // If at last node, move after end
    if (cursor->next == NULL) {
        cursorAfterEnd = 1;
        return;
    }

    // Otherwise move normally
    cursor = cursor->next;
}

// display function
void displayTextWithCursor() {
    Node *temp = head;
    printf("\n--- Text Buffer ---\n");

    if (head == NULL) {
        printf("|");
    }

    // Cursor before first char
    if (cursor == NULL && !cursorAfterEnd)
        printf("|");

    while (temp != NULL) {
        printf("%c", temp->ch);
        if (temp == cursor && !cursorAfterEnd)
            printf("|");
        temp = temp->next;
    }

    // Cursor after last char
    if (cursorAfterEnd)
        printf("|");

    printf("\n-------------------\n");
}

void moveCursorToStart() {
    if (head == NULL) return;
    cursor = NULL;          // before first character
    cursorAfterEnd = 0;
}

void moveCursorToEnd() {
    if (head == NULL) return;

    Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    cursor = temp;          // at last character
    cursorAfterEnd = 1;     // logically after the end
}



// Snapshot the text buffer into a string
char *getTextSnapshot() {
    int len = 0;
    Node *temp = head;
    while (temp) {
        len++;
        temp = temp->next;
    }

    char *text = (char *)malloc(len + 1);
    temp = head;
    int i = 0;
    while (temp) {
        text[i++] = temp->ch;
        temp = temp->next;
    }
    text[i] = '\0';
    return text;
}

// Restore linked list from a saved text snapshot
void setTextFromSnapshot(const char *text) {
    // clear current list
    Node *temp = head;
    while (temp) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    head = NULL;

    for (int i = 0; text[i] != '\0'; i++)
        insertChar(text[i]);
}
//next
// Search and Replace function
void searchAndReplace(const char *search, const char *replace) {
    char *text = getTextSnapshot();

    char *pos = strstr(text, search);
    if (!pos) {
        printf("'%s' not found.\n", search);
        free(text);
        return;
    }

    // Allocate new buffer
    char newText[5000];
    newText[0] = '\0';

    while (pos) {
        strncat(newText, text, pos - text); // part before match
        strcat(newText, replace);           // insert replacement
        text = pos + strlen(search);        // move after match
        pos = strstr(text, search);         // find next
    }
    strcat(newText, text); // append remaining text

    setTextFromSnapshot(newText);
    printf("All occurrences of '%s' replaced with '%s'.\n", search, replace);
}
//next
// Delete the last word (characters until previous space)
void deleteLastWord() {
    if (head == NULL) return;

    // Convert to string for easier logic
    char *text = getTextSnapshot();
    int len = strlen(text);

    if (len == 0) {
        free(text);
        return;
    }

    // Find last non-space character
    int i = len - 1;
    while (i >= 0 && text[i] == ' ')
        i--;

    // Now skip backward until space or start
    while (i >= 0 && text[i] != ' ')
        i--;

    text[i + 1] = '\0'; // truncate at that point
    setTextFromSnapshot(text);

    free(text);
    printf("Last word deleted.\n");
}
