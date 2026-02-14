#include <stdio.h>
#include <stdlib.h>
#define FIN "q1.c"

int main() {
    FILE *fp;
    char ch;
    int blankLines = 0;
    int semicolonLines = 0;
    int blankSpaces = 0;
    int isBlankLine = 1;   // Assume line is blank initially
    int lastChar = 0;      // To check last character before newline

    // Open the source file in read mode
    fp = fopen(FIN, "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        // Count blank spaces
        if (ch == ' ')
            blankSpaces++;

        // If character is not space or tab or newline, line is not blank
        if (ch != ' ' && ch != '\t' && ch != '\n')
            isBlankLine = 0;

        // If newline encountered
        if (ch == '\n') {

            // Check if it was a blank line
            if (isBlankLine)
                blankLines++;

            // Check if line ended with semicolon
            if (lastChar == ';')
                semicolonLines++;

            // Reset for next line
            isBlankLine = 1;
        }

        // Store last non-newline character
        if (ch != '\n')
            lastChar = ch;
    }

    fclose(fp);

    printf("Total Blank Lines: %d\n", blankLines);
    printf("Total Lines Ending with Semicolon: %d\n", semicolonLines);
    printf("Total Blank Spaces: %d\n", blankSpaces);

    return 0;
}
