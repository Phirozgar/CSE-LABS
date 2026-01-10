#include <stdio.h>
#include <stdlib.h>

#define FIN "directiveReplace.c"
#define FOUT "directiveOutput.c"
#define PREPOC '#'
#define NEWLINE '\n'

int main() {
    FILE *fptr1 = fopen(FIN, "r");
    FILE *fptr2 = fopen(FOUT, "w");

    if (fptr1 == NULL || fptr2 == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }

    int c;
    int prev = 0;  // previous character written

    while ((c = fgetc(fptr1)) != EOF) {
        if(c == PREPOC) {
            while ((c = fgetc(fptr1)) != NEWLINE);
        }
        fputc(c, fptr2);
    }
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}
