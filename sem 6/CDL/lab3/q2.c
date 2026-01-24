#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define FIN "../lab2/commentInput.c"

typedef enum
{
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SPECIAL_SYMBOL,
    END_OF_FILE
} TokenType;

typedef struct
{
    int row;
    int col;
    TokenType type;
    char lexeme[50];
} Token;

const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "for", "while",
    "do", "break", "continue", "return", "void", "switch", "case"
};

int isKeyword(char *word)
{
    for (int i = 0; i < 15; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

Token getNextToken(FILE *fptr1)
{
    static int row = 1, col = 0;
    Token token;
    int c, next;
    int i;

    while ((c = fgetc(fptr1)) != EOF)
    {
        col++;

        if (c == '\n')
        {
            row++;
            col = 0;
            continue;
        }

        if (isspace(c))
            continue;

        if (c == '#')
        {
            while ((c = fgetc(fptr1)) != '\n' && c != EOF);
            row++;
            col = 0;
            continue;
        }

        if (c == '/')
        {
            next = fgetc(fptr1);

            if (next == '/')
            {
                while ((c = fgetc(fptr1)) != '\n' && c != EOF);
                row++;
                col = 0;
                continue;
            }
            else if (next == '*')
            {
                while ((c = fgetc(fptr1)) != EOF)
                {
                    if (c == '\n')
                    {
                        row++;
                        col = 0;
                    }
                    if (c == '*' && fgetc(fptr1) == '/')
                        break;
                }
                continue;
            }
            else
            {
                ungetc(next, fptr1);
            }
        }

        if (c == '"')
        {
            while ((c = fgetc(fptr1)) != '"' && c != EOF)
            {
                if (c == '\n')
                {
                    row++;
                    col = 0;
                }
            }
            continue;
        }

        token.row = row;
        token.col = col;
        i = 0;

        if (isalpha(c) || c == '_')
        {
            token.lexeme[i++] = c;

            while (isalnum(c = fgetc(fptr1)) || c == '_')
                token.lexeme[i++] = c;

            token.lexeme[i] = '\0';
            ungetc(c, fptr1);

            token.type = isKeyword(token.lexeme) ? KEYWORD : IDENTIFIER;
            return token;
        }

        if (isdigit(c))
        {
            token.lexeme[i++] = c;

            while (isdigit(c = fgetc(fptr1)))
                token.lexeme[i++] = c;

            token.lexeme[i] = '\0';
            ungetc(c, fptr1);

            token.type = NUMBER;
            return token;
        }

        if (strchr("+-*/=%<>!", c))
        {
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            token.type = OPERATOR;
            return token;
        }

        if (strchr("(){}[];,", c))
        {
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            token.type = SPECIAL_SYMBOL;
            return token;
        }
    }

    token.type = END_OF_FILE;
    strcpy(token.lexeme, "EOF");
    token.row = row;
    token.col = col;
    return token;
}

int main()
{
    FILE *fptr1 = fopen(FIN, "r");
    Token t;

    if (fptr1 == NULL)
        return 1;

    while ((t = getNextToken(fptr1)).type != END_OF_FILE)
    {
        printf("Row:%d Col:%d Type:%d Lexeme:%s\n",
               t.row, t.col, t.type, t.lexeme);
    }

    fclose(fptr1);
    return 0;
}
