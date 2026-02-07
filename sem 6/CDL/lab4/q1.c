#include <stdio.h>
#include <string.h>
#include "token.h"

#define FIN "../ip2.txt"

/* ---------- SYMBOL TABLE STRUCTURES ---------- */

typedef struct {
    char name[50];
    char datatype[20];
    char tokenClass[25];   // IDENTIFIER, KEYWORD, etc.
    int row;
} GlobalSymbol;

typedef struct {
    char name[50];
    char datatype[20];
    char tokenClass[25];   // IDENTIFIER, KEYWORD, etc.
    char functionName[50];
    int row;
} LocalSymbol;

/* ---------- TABLES & COUNTERS ---------- */

GlobalSymbol GST[50];
LocalSymbol LST[50];
int gCount = 0;
int lCount = 0;

/* ---------- HELPER FUNCTIONS ---------- */

int isDataType(char *s) {
    return (strcmp(s, "int") == 0 ||
            strcmp(s, "float") == 0 ||
            strcmp(s, "char") == 0 ||
            strcmp(s, "double") == 0 ||
            strcmp(s, "void") == 0);
}

const char *tokenTypeToString(TokenType type) {
    switch (type) {
        case KEYWORD:         return "KEYWORD";
        case IDENTIFIER:      return "IDENTIFIER";
        case NUMBER:          return "NUMBER";
        case OPERATOR:        return "OPERATOR";
        case SPECIAL_SYMBOL:  return "SPECIAL_SYMBOL";
        case END_OF_FILE:     return "EOF";
        default:              return "UNKNOWN";
    }
}

/* ---------- MAIN ---------- */

int main() {
    FILE *fp = fopen(FIN, "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    Token prev, curr;
    int scope = 0;                  // 0 = global, 1 = local
    char currentFunction[50] = "";

    prev.type = END_OF_FILE;

    while ((curr = getNextToken(fp)).type != END_OF_FILE) {

        /* -------- FUNCTION NAME DETECTION -------- */
        if (curr.type == IDENTIFIER) {
            Token next = getNextToken(fp);

            if (strcmp(next.lexeme, "(") == 0) {
                strcpy(currentFunction, curr.lexeme);
                // Do not enter local scope here
            }

            fseek(fp, -strlen(next.lexeme), SEEK_CUR);
        }

        /* -------- ENTER LOCAL SCOPE -------- */
        if (strcmp(curr.lexeme, "{") == 0 && strlen(currentFunction) > 0) {
            scope = 1;
        }

        /* -------- VARIABLE DECLARATION -------- */
        if (curr.type == IDENTIFIER &&
            prev.type == KEYWORD &&
            isDataType(prev.lexeme)) {

            if (scope == 0) {
                /* GLOBAL SYMBOL */
                strcpy(GST[gCount].name, curr.lexeme);
                strcpy(GST[gCount].datatype, prev.lexeme);
                strcpy(GST[gCount].tokenClass,
                       tokenTypeToString(curr.type));
                GST[gCount].row = curr.row;
                gCount++;
            } else {
                /* LOCAL SYMBOL */
                strcpy(LST[lCount].name, curr.lexeme);
                strcpy(LST[lCount].datatype, prev.lexeme);
                strcpy(LST[lCount].tokenClass,
                       tokenTypeToString(curr.type));
                strcpy(LST[lCount].functionName, currentFunction);
                LST[lCount].row = curr.row;
                lCount++;
            }
        }

        /* -------- EXIT LOCAL SCOPE -------- */
        if (strcmp(curr.lexeme, "}") == 0) {
            scope = 0;
            strcpy(currentFunction, "");
        }

        prev = curr;
    }

    fclose(fp);

    /* ---------- OUTPUT ---------- */

    printf("\nGLOBAL SYMBOL TABLE\n");
    printf("------------------------------------------------\n");
    printf("Name\tDatatype\tTokenType\tRow\n");
    for (int i = 0; i < gCount; i++) {
        printf("%s\t%s\t\t%s\t\t%d\n",
               GST[i].name,
               GST[i].datatype,
               GST[i].tokenClass,
               GST[i].row);
    }

    printf("\nLOCAL SYMBOL TABLE\n");
    printf("------------------------------------------------\n");
    printf("Name\tDatatype\tTokenType\tFunction\tRow\n");
    for (int i = 0; i < lCount; i++) {
        printf("%s\t%s\t\t%s\t\t%s\t\t%d\n",
               LST[i].name,
               LST[i].datatype,
               LST[i].tokenClass,
               LST[i].functionName,
               LST[i].row);
    }

    return 0;
}
