#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FIN "q1b.c"
#define KEYWORD_COUNT 32
#define DOUBLE_QUOTE '"'

const char splSymbols[] = {',', ';', '*', '=', '#', '.', '&', ':'};
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

int isKeyword(const char *word)
{
    for (int i = 0; i < KEYWORD_COUNT; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void checkForSpecialSymbols(char c)
{
    for (int i = 0; i < sizeof(splSymbols); i++)
    {
        if (c == splSymbols[i])
            printf("\nSpecial Symbol : %c", c);
    }
}

void checkForKeywordsOrIdentifiers(char c, FILE *fptr1)
{
    char word[32];
    int i = 0;
    char next;

    if (isalpha(c) || c == '_')
    {
        word[i++] = c;

        while ((next = fgetc(fptr1)) != EOF && (isalnum(next) || next == '_'))
        {
            word[i++] = next;
        }

        word[i] = '\0';

        if (next != EOF)
            fseek(fptr1, -1, SEEK_CUR);

        if (isKeyword(word))
            printf("\nKeyword : %s", word);
        else
            printf("\nIdentifier : %s", word);
    }
}

void checkForNumConsts(char c, FILE *fptr1)
{
    char num[16];
    int i = 0;
    char next;

    if (isdigit(c))
    {
        num[i++] = c;

        while ((next = fgetc(fptr1)) != EOF && isdigit(next))
        {
            num[i++] = next;
        }

        num[i] = '\0';

        if (next != EOF)
            fseek(fptr1, -1, SEEK_CUR);

        printf("\nNumeric Constant : %s", num);
    }
}

void checkForStringLiterals(char c, FILE *fptr1)
{
    char str[64];
    int i = 0;
    char next;

    if (c == '"')
    {
        while ((next = fgetc(fptr1)) != EOF && next != '"')
        {
            if (i < sizeof(str) - 1)
                str[i++] = next;
        }

        str[i] = '\0';
        printf("\nString Literal : \"%s\"", str);
    }
}


int main()
{
    FILE *fptr1 = fopen(FIN, "r");

    if (fptr1 == NULL)
    {
        printf("Can't open file");
        exit(1);
    }

    char c;
    while ((c = fgetc(fptr1)) != EOF)
    {
        checkForSpecialSymbols(c);
        checkForKeywordsOrIdentifiers(c, fptr1);
        checkForNumConsts(c, fptr1);
        checkForStringLiterals(c, fptr1);
    }

    fclose(fptr1);
    return 0;
}
