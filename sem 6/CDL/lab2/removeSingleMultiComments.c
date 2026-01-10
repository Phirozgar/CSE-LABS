#include <stdio.h>
#include <stdlib.h>

#define FIN "commentInput.c"
#define FOUT "commentOutput.c"
#define SLASH '/'
#define ASTERISK '*'
#define NEWLINE '\n'
#define SPACE ' '

int main() {
    FILE *fptr1, *fptr2;
    fptr1 = fopen(FIN, "r");
    if(fptr1 == NULL) {
        printf("cannot open file %s \n", FIN);
        exit(1);
    }

    fptr2 = fopen(FOUT, "w+");

    int c2, c1 = fgetc(fptr1);
    while (c1 != EOF) { 
        if(c1==SPACE) {
            putc(c1,fptr2);
            while(c1==SPACE)
                c1 = getc(fptr1);
        }
        if (c1==SLASH) {
            c2 = getc(fptr1);
            if (c2 == SLASH) {
                while(c1 != NEWLINE)
                    c1 = getc(fptr1);
            }
            else if (c2 == ASTERISK) {
                do {
                    while(c1 != ASTERISK) 
                        c1 = getc(fptr1);
                    c1 = getc(fptr1);
                } while (c1 != SLASH);
            } 
            else {
                putc(c1,fptr2);
                putc(c2,fptr2);
            }
        }
        else 
            putc(c1,fptr2);
        c1 = getc(fptr1); 
    }
    fclose(fptr1);
    fclose(fptr2); 
    return 0;
}
