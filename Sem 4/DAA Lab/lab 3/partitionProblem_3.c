#include <stdio.h>
#include <stdlib.h>

int opcount = 0;  // Global variable to count operations (comparisons)

int checkSum(int* array, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
        opcount++;  // Counting the comparison in the loop
    }
    return (sum % 2 == 0);  // If the sum is even, return 1, otherwise return 0
}

int subsetSum(int* array, int n, int sum) {
    int totalSubsets = 1 << n;  // There are 2^n subsets
    
    for (int mask = 0; mask < totalSubsets; mask++) {
        int subsetSum = 0;
        
        // For each bit in mask, check if it's part of the subset
        for (int i = 0; i < n; i++) {
            opcount++;  // Counting the comparison for the bitwise check
            if (mask & (1 << i)) {  // If the ith bit is set, include array[i] in the subset
                subsetSum += array[i];
            }
        }

        // If the subset sum is equal to the target sum, return true
        opcount++;  // Counting the comparison when checking subsetSum == sum
        if (subsetSum == sum) {
            return 1;
        }
    }
    return 0;  // No subset found with the desired sum
}

void partitionProblem(int* array, int n) {
    // First, check if the total sum of the array is even
    if (!checkSum(array, n)) {
        printf("\nNot Possible\n");
        printf("Total comparisons: %d\n", opcount);  // Print the operation count
        return;
    }

    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += array[i];
        opcount++;  // Counting the comparison in the loop for total sum calculation
    }
    int targetSum = totalSum / 2;  // We need to find a subset with this sum

    // Use subset sum approach to check if a subset with sum 'targetSum' exists
    if (subsetSum(array, n, targetSum)) {
        printf("\nPossible\n");
    } else {
        printf("\nNot Possible\n");
    }
    printf("Total comparisons: %d\n", opcount);  // Print the operation count
}

int main() {
    int array[] = {1, 5, 11, 5};  // Example array
    int n = sizeof(array) / sizeof(array[0]);  // Number of elements in the array
    
    partitionProblem(array, n);

    return 0;
}
