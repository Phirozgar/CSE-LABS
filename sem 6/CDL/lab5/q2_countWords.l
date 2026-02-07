%{
#include <stdio.h>
int words = 0, chars = 0, blanks = 0, lines = 0;
%}

%%
[ \t]       { blanks++; chars++; }
\n          { lines++; chars++; }
[^ \t\n]+   { words++; chars += yyleng; }
.           { chars++; }
%%

int yywrap() 
{return 1;}

int main() {
    yylex();
    printf("Words = %d\n", words);
    printf("Characters = %d\n", chars);
    printf("Blanks = %d\n", blanks);
    printf("Lines = %d\n", lines);
    return 0;
}
