%{
#include <stdio.h>
int sc = 0, pr = 0;
%}

%%
scanf   { sc++; printf("READ"); }
printf  { pr++; printf("WRITE"); }
.|\n    { printf("%s", yytext); }
%%

int yywrap() 
{return 1;}

int main() {
    yylex();
    printf("\nNumber of scanf = %d\n", sc);
    printf("Number of printf = %d\n", pr);
    return 0;
}
