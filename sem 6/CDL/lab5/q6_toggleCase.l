%{
#include <stdio.h>
%}

%%
"//".*                  { printf("%s", yytext); }
"/*"([^*]|\*+[^*/])*\*+"/"  { printf("%s", yytext); }
[A-Z]                   { printf("%c", tolower(yytext[0])); }
.|\n                    { printf("%s", yytext); }
%%

int yywrap() 
{return 1;}

int main() {
    yylex();
    return 0;
}
