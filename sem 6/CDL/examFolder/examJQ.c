#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define FIN "input.js"

/* ---------------- TOKEN TYPES ---------------- */

typedef enum {
    KEYWORD,
    FUNC,
    IDENTIFIER,
    NUMBER,
    STRING_LITERAL,
    OPERATOR,
    SPECIAL_SYMBOL,
    END_OF_FILE
} TokenType;

typedef struct {
    char lexeme[100];
    int row;
    int col;
    TokenType type;
} Token;

/* ---------------- SYMBOL TABLE ---------------- */

typedef struct {
    char name[50];
    char tokenType[20];
    char argument[200];
} LocalSymbol;

LocalSymbol LST[100];
int lCount = 0;

/* ---------------- KEYWORDS ---------------- */

const char *keywords[] = {"let", "function", "document"};
const char *functions[] = {
    "ready","on","val","split","map",
    "filter","text","join","isNaN"
};

int isKeyword(char *str) {
    for(int i=0;i<3;i++)
        if(strcmp(str, keywords[i])==0)
            return 1;
    return 0;
}

int isFunction(char *str) {
    for(int i=0;i<9;i++)
        if(strcmp(str, functions[i])==0)
            return 1;
    return 0;
}

/* ---------------- TOKEN PRINTER ---------------- */

void printToken(Token t) {
    printf("<%s,%d,%d>\n", t.lexeme, t.row, t.col);
}

/* ---------------- STORE FUNCTION ---------------- */

void storeFunction(char *name, char *arg) {
    strcpy(LST[lCount].name, name);
    strcpy(LST[lCount].tokenType, "FUNC");
    strcpy(LST[lCount].argument, arg);
    lCount++;
}

/* ---------------- LEXICAL ANALYZER ---------------- */

Token getNextToken(FILE *fp) {
    static int row=1, col=0;
    Token token;
    int c, next;
    int i;

    while((c=fgetc(fp))!=EOF) {

        col++;

        if(c=='\n') {
            row++;
            col=0;
            continue;
        }

        if(isspace(c))
            continue;

        token.row=row;
        token.col=col;
        i=0;

        /* ---------- STRING or #IDENTIFIER ---------- */
        if(c=='"') {
            c=fgetc(fp);
            if(c=='#') {
                token.lexeme[i++]='#';
                while((c=fgetc(fp))!='"' && c!=EOF)
                    token.lexeme[i++]=c;
                token.lexeme[i]='\0';
                token.type=IDENTIFIER;
                return token;
            } else {
                token.lexeme[i++]='"';
                while(c!='"' && c!=EOF) {
                    token.lexeme[i++]=c;
                    c=fgetc(fp);
                }
                token.lexeme[i++]='"';
                token.lexeme[i]='\0';
                token.type=STRING_LITERAL;
                return token;
            }
        }

        /* ---------- IDENTIFIER / KEYWORD / FUNC ---------- */
        if(isalpha(c) || c=='_' || c=='#') {
            token.lexeme[i++]=c;
            while(isalnum(c=fgetc(fp)) || c=='_' )
                token.lexeme[i++]=c;
            token.lexeme[i]='\0';
            ungetc(c,fp);

            if(isKeyword(token.lexeme))
                token.type=KEYWORD;
            else if(isFunction(token.lexeme))
                token.type=FUNC;
            else
                token.type=IDENTIFIER;

            return token;
        }

        /* ---------- NUMBER ---------- */
        if(isdigit(c)) {
            token.lexeme[i++]=c;
            while(isdigit(c=fgetc(fp)))
                token.lexeme[i++]=c;
            token.lexeme[i]='\0';
            ungetc(c,fp);
            token.type=NUMBER;
            return token;
        }

        /* ---------- REGEX ---------- */
        if(c=='/') {
            next=fgetc(fp);
            if(next=='\\') {
                token.lexeme[i++]='/';
                token.lexeme[i++]='\\';
                while((c=fgetc(fp))!='/' && c!=EOF)
                    token.lexeme[i++]=c;
                token.lexeme[i++]='/';
                token.lexeme[i]='\0';
                token.type=STRING_LITERAL;
                return token;
            } else {
                ungetc(next,fp);
            }
        }

        /* ---------- MULTI CHAR OPERATORS ---------- */
        if(c=='&') {
            next=fgetc(fp);
            if(next=='&') {
                strcpy(token.lexeme,"&&");
                token.type=OPERATOR;
                return token;
            }
            ungetc(next,fp);
        }

        if(c=='=') {
            next=fgetc(fp);
            if(next=='=') {
                strcpy(token.lexeme,"==");
            } else if(next=='>') {
                strcpy(token.lexeme,"=>");
            } else {
                ungetc(next,fp);
                strcpy(token.lexeme,"=");
            }
            token.type=OPERATOR;
            return token;
        }

        /* ---------- SINGLE OPERATORS ---------- */
        if(strchr("$+-*/%<>!?:",c)) {
            token.lexeme[0]=c;
            token.lexeme[1]='\0';
            token.type=OPERATOR;
            return token;
        }

        /* ---------- SPECIAL SYMBOLS ---------- */
        if(strchr("(){};,.",c)) {
            token.lexeme[0]=c;
            token.lexeme[1]='\0';
            token.type=SPECIAL_SYMBOL;
            return token;
        }
    }

    token.type=END_OF_FILE;
    strcpy(token.lexeme,"EOF");
    token.row=row;
    token.col=col;
    return token;
}

/* ---------------- MAIN ---------------- */

int main() {
    FILE *fp=fopen(FIN,"r");
    if(fp==NULL) {
        printf("File not found\n");
        return 1;
    }

    Token t;
    Token prev;
    prev.type=END_OF_FILE;

    while((t=getNextToken(fp)).type!=END_OF_FILE) {

        printToken(t);

        /* -------- STORE FUNCTION WITH ARGUMENT -------- */
        if(t.type==FUNC) {
            Token next=getNextToken(fp);
            if(strcmp(next.lexeme,"(")==0) {
                char arg[200]="";
                int depth=1;
                Token temp;

                while(depth>0) {
                    temp=getNextToken(fp);
                    if(strcmp(temp.lexeme,"(")==0)
                        depth++;
                    else if(strcmp(temp.lexeme,")")==0)
                        depth--;

                    if(depth>0) {
                        strcat(arg,temp.lexeme);
                        strcat(arg," ");
                    }
                }

                storeFunction(t.lexeme,arg);
            }
        }

        prev=t;
    }

    fclose(fp);

    /* ---------- PRINT SYMBOL TABLE ---------- */

    printf("\nLOCAL SYMBOL TABLE\n");
    printf("--------------------------------------------\n");
    printf("Name\tTokenType\tArgument\n");
    for(int i=0;i<lCount;i++)
        printf("%s\t%s\t\t%s\n",
               LST[i].name,
               LST[i].tokenType,
               LST[i].argument);

    return 0;
}
