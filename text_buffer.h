#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

typedef struct Node {
    char ch;
    struct Node *next;
} Node;

extern Node *head;

void insertChar(char c);
void deleteChar();
//void displayText();
char *getTextSnapshot();  // returns current text as string
void setTextFromSnapshot(const char *text);
void searchAndReplace(const char *search, const char *replace);
void deleteLastWord();
void moveCursorLeft();
void moveCursorRight();
void displayTextWithCursor();
void moveCursorToStart();
void moveCursorToEnd();


#endif
