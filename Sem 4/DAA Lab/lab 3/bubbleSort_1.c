#include <stdio.h>
#include <stdlib.h>
int opcount = 0;

void bubbleSort(int* array, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            opcount++;
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &array[i]);
    }
    bubbleSort(array, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("%d", opcount);
    return 0;
}
