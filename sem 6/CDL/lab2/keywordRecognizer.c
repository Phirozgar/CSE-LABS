#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define FIN "keywordRecognizer.c"
#define FOUT "keywordOutput.txt"
#define MAX_WORD 64
#define KEYWORD_COUNT 32


const char *keywords[] = {
    "auto","break","case","char","const","continue",
    "default","do","double","else","enum","extern",
    "float","for","goto","if","int","long","register",
    "return","short","signed","sizeof","static","struct",
    "switch","typedef","union","unsigned","void","volatile","while"
};

int isKeyword(const char *word) {
    for (int i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main(void) {
    FILE *fptr1 = fopen(FIN, "r");
    FILE *fptr2 = fopen(FOUT, "w");

    if (fptr1 == NULL || fptr2 == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }

    int c;
    char word[MAX_WORD];
    int i;

    while ((c = fgetc(fptr1)) != EOF) {

        if (isalpha(c) || c == '_') {
            i = 0;
            word[i++] = c;

            while ((c = fgetc(fptr1)) != EOF &&
                   (isalnum(c) || c == '_')) {
                if (i < MAX_WORD - 1)
                    word[i++] = c;
            }

            word[i] = '\0';

            if (isKeyword(word)) {
                /* write keyword using fputc */
                for (int j = 0; word[j] != '\0'; j++) {
                    fputc(word[j], fptr2);
                }
                fputc('\n', fptr2);
            }
        }
    }

    fclose(fptr1);
    fclose(fptr2);
    return 0;
}
