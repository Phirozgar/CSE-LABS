#include <stdio.h>
#include <stdlib.h>

#define FIN "sample.c"
#define EQ '='
#define LT '<'
#define GT '>'
#define NOT '!'
#define SPACE ' '

int main() {
    FILE* fptr1 = fopen(FIN, "r");

    if(fptr1 == NULL) {
        printf("Can't open file");
        exit(1);
    }

    char c, prev;
    while ((c = fgetc(fptr1)) != EOF) {
        if(c == EQ) {
            prev = EQ;
            c = fgetc(fptr1);
            if(c == EQ)
                printf("\nRelational Operator : %c%c", prev, c);
            else if (c == SPACE)
                printf("\nAssignment Operator : %c%c", prev, c);

        } else if (c == LT || c == GT || c == NOT) {
            prev = c;
            c = fgetc(fptr1);
            if(c == EQ)
                printf("\nRelational Operator : %c%c", prev, c);
            else 
                printf("\nRelational Operator : %c", c);
        }

    }
    fclose(fptr1);
    return 0;
}