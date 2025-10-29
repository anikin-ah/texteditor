#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_buffer.h"

void saveToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    Node *temp = head;
    while (temp) {
        fputc(temp->ch, fp);
        temp = temp->next;
    }

    fclose(fp);
    printf("File saved successfully as '%s'.\n", filename);
}

void loadFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file for reading.\n");
        return;
    }

    // clear old text
    setTextFromSnapshot("");

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        insertChar(ch);
    }

    fclose(fp);
    printf("File '%s' loaded successfully.\n", filename);
}
