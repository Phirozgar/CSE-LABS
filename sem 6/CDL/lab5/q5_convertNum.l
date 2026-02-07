%{
#include <stdio.h>
%}

%%
[0-9]+  {
            int n = atoi(yytext);
            printf("0x%X", n);
        }
\n      { printf("\n"); }
.       { printf("%s", yytext); }
%%

int yywrap() 
{return 1;}

int main() {
    yylex();
    return 0;
}
