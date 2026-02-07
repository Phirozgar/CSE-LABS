%{
#include <stdio.h>
int pos_int=0, neg_int=0, pos_float=0, neg_float=0;
%}

%%
[-]?[0-9]+"."[0-9]+   {
                        if(yytext[0]=='-') neg_float++;
                        else pos_float++;
                      }
[-]?[0-9]+            {
                        if(yytext[0]=='-') neg_int++;
                        else pos_int++;
                      }
\n                    ;
.                     ;
%%

int yywrap() 
{return 1;}

int main() {
    yylex();
    printf("Positive Integers = %d\n", pos_int);
    printf("Negative Integers = %d\n", neg_int);
    printf("Positive Floats = %d\n", pos_float);
    printf("Negative Floats = %d\n", neg_float);
    return 0;
}
