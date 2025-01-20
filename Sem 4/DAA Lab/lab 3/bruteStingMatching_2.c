#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int opcount = 0;

void findSubstring(char* str, char* substr) {
    int strLength = strlen(str);
    int subStrLength = strlen(substr);
    int i, j;

    for (i = 0; i <= strLength - subStrLength; i++) {  // Fix off-by-one error here
        for (j = 0; j < subStrLength; j++) {
            opcount++;
            if (substr[j] != str[i + j]) {
                break;
            }
        }
        if (j == subStrLength) {
            printf("Substring found\n");
            return;
        }
    }
    printf("Substring not found\n");
}

int main() {
    char str[100], substr[100];  // Allocate space for the strings

    puts("\nEnter string: ");
    scanf("%s", str);
    puts("\nEnter substring: ");
    scanf("%s", substr);

    findSubstring(str, substr);
    printf("Operations: %d\n", opcount);

    return 0;
}
