#include <stdio.h>
#include <stdlib.h>

#define FIN "tabReplace.c"
#define FOUT "tabReplaceOutput.c"
#define SPACE ' '
#define TAB '\t'

int main() {
 FILE *fptr1 = fopen(FIN, "r");
 FILE *fptr2 = fopen(FOUT, "w");

 if (fptr1 == NULL || fptr2 == NULL) {
 printf("Cannot open file\n");
 exit(1);
 }

 int c;
 int prev = 0; // previous character written

 while ((c = fgetc(fptr1)) != EOF) {

 // Treat tabs as spaces
 if (c == TAB)
 c = SPACE;

 // Skip if this is a space and previous was also space
 if (c == SPACE && prev == SPACE)
 continue;

 fputc(c, fptr2);
 prev = c;
 }
 fclose(fptr1);
 fclose(fptr2);
 return 0;
}
