#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_buffer.h"
#include "undo_redo.h"
#include "clipboard.h"
#include "file_ops.h"

void showMenu()
{
    printf("\n====== TEXT EDITOR ======\n");
    printf("|[1].Insert Text        |");
    printf("|[2].Delete Last Char   |");
    printf("|[3].Delete Last Word   |");
    printf("|[4].Display Text       |\n");
    printf("|[5].Move Cursor Left   |");
    printf("|[6].Move Cursor Right  |");
    printf("|[7].Move to start      |");
    printf("|[8].Move to end        |\n");
    printf("|[9].Undo               |");
    printf("|[10].Redo              |");
    printf("|[11].Copy All Text     |");
    printf("|[12].Paste Text        |\n");
    printf("|[13].Search & Replace  |");
    printf("|[14].Save to File      |");
    printf("|[15].Load from File    |");
    printf("|[16].Exit              |\n");
    printf("=========================\n");
    printf("Choose: ");
}

int main()
{
    int choice;
    char input[200], search[100], replace[100], filename[100];

    while (1)
    {
        showMenu();
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice)
        {
        case 1:
            printf("Enter text to insert: ");
            fgets(input, sizeof(input), stdin);
            saveState();
            for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++)
                insertChar(input[i]);
            break;

        case 2:
            saveState();
            deleteChar();
            break;
        case 3:
            saveState();
            deleteLastWord();
            break;

        case 4:
            displayTextWithCursor();
            break;
        case 5:
            moveCursorLeft();
            break;
        case 6:
            moveCursorRight();
            break;
        case 7:
            moveCursorToStart();
            printf("Cursor moved to start.\n");
            break;

        case 8:
            moveCursorToEnd();
            printf("Cursor moved to end.\n");
            break;

        case 9:
            undo();
            break;

        case 10:
            redo();
            break;

        case 11:
            copyText();
            break;

        case 12:
            pasteText();
            break;

        case 13:
            printf("Enter word to search: ");
            fgets(search, sizeof(search), stdin);
            search[strcspn(search, "\n")] = 0; // remove newline
            printf("Enter word to replace with: ");
            fgets(replace, sizeof(replace), stdin);
            replace[strcspn(replace, "\n")] = 0;

            saveState();
            searchAndReplace(search, replace);
            break;

        case 14:
            printf("Enter filename to save: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            saveToFile(filename);
            break;

        case 15:
            printf("Enter filename to load: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = 0;
            loadFromFile(filename);
            break;

        case 16:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
