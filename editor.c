/**
 * editor.c
 *
 * You must implement the functions in editor.h in this file.
 * Consult the assignment handout for the detailed specifications of each of the functions.
 *
 * Student ID:300434984
 * Name: Connor R. Morgan
 */
#include "stdio.h"
#include "editor.h"
#include "string.h"
#include "stdbool.h"


int editor_replace_str(char *editing_buffer, const char *str, const char *replacement, int offset) {
    char offsetedArray[EDITING_BUFLEN - offset];
    for (int i = 0; i + offset < EDITING_BUFLEN; i++) {
        offsetedArray[i] = editing_buffer[i + offset];
    }
    printf("\n%s",offsetedArray);
    // Locates the index of the first instance of str after the offset
    if (strstr(editing_buffer, str) != NULL) {
        char *point = strstr(offsetedArray, str);
        int location = (int) ((point) - offsetedArray)+offset;
        printf("\n%d",location);
        if (strlen(str) == strlen(replacement)) {
            for (int i = 0; i < strlen(replacement); i++) {
                editing_buffer[location + i] = replacement[i];
            }
        }
        else if (strlen(replacement) > strlen(str)) {
            int strLengthDifference = strlen(replacement) - strlen(str);
            int numberOfCharsToMove = EDITING_BUFLEN - location - strLengthDifference;
            if (location + strlen(replacement) > EDITING_BUFLEN) {
                return -1;
            }
            char charsToMove[numberOfCharsToMove];
            for (int i = 0; i + location + strlen(str) < EDITING_BUFLEN; i++) {
                charsToMove[i] = editing_buffer[i + location + strlen(str)];
            }
            for (int i = 0; i < strlen(replacement); i++) {
                editing_buffer[i + location] = replacement[i];
            }
            for (int i = 0; i < numberOfCharsToMove; i++) {
                if (i + location + strlen(replacement) < EDITING_BUFLEN - 1) {
                    editing_buffer[i + location + strlen(replacement)] = charsToMove[i];
                }
            }
            if (numberOfCharsToMove + location + strlen(replacement) > EDITING_BUFLEN - 1) {
                editing_buffer[20] = '\0';
            } else {
                for (int i = numberOfCharsToMove + location + strlen(replacement); i < EDITING_BUFLEN; i++) {
                    editing_buffer[i] = '\0';
                }
            }
        }
    }


}

int editor_insert_char(char *editing_buffer, char to_insert, int pos) {
    char toMove[EDITING_BUFLEN - (pos + 1)];
    for (int i = 0; i < EDITING_BUFLEN - pos - 1; i++) {
        toMove[i] = editing_buffer[i + pos];
    }
    editing_buffer[pos] = to_insert;
    for (int i = 0; i < EDITING_BUFLEN - pos - 1; i++) {
        editing_buffer[i + pos + 1] = toMove[i];
    }
    printf("%s\n", editing_buffer);
    return 1;
}

int editor_delete_char(char *editing_buffer, char to_delete, int offset) {
    int deletedChar;
    for (int i = 0; i < EDITING_BUFLEN; i++) {
        if (editing_buffer[i] == to_delete) {
            deletedChar = i;
            break;
        }
    }
    if (editing_buffer[deletedChar] == to_delete) {
        for (int i = deletedChar; i < EDITING_BUFLEN - 1; i++) {
            editing_buffer[i] = editing_buffer[i + 1];
        }
        editing_buffer[EDITING_BUFLEN] = '\0';
        return 1;
    }
}


int main() {



    // int r = editor_insert_char(editing_buffer,'s', 9);
    char editing_buffer[EDITING_BUFLEN] = "The quick brown fox";
    char str[] = "brown";
    char rep[] = "browns";
    int r = editor_replace_str(editing_buffer, str, rep, 3);
    printf("\n%s",editing_buffer);
    return 0;

}