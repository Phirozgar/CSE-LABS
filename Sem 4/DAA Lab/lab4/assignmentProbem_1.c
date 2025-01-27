#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to calculate the total cost of an assignment
int total_cost(int *assignment, int **cost_matrix, int n) {
    int cost = 0;
    for (int i = 0; i < n; i++) {
        cost += cost_matrix[i][assignment[i]];
    }
    return cost;
}

// Function to generate all permutations of an array
void permute(int *arr, int left, int right, int n, int **cost_matrix, int *min_cost, int *best_assignment) {
    if (left == right) {
        int cost = total_cost(arr, cost_matrix, n);
        if (cost < *min_cost) {
            *min_cost = cost;
            for (int i = 0; i < n; i++) {
                best_assignment[i] = arr[i];
            }
        }
    } else {
        for (int i = left; i <= right; i++) {
            // Swap
            int temp = arr[left];
            arr[left] = arr[i];
            arr[i] = temp;
            
            // Recur
            permute(arr, left + 1, right, n, cost_matrix, min_cost, best_assignment);
            
            // Swap back
            temp = arr[left];
            arr[left] = arr[i];
            arr[i] = temp;
        }
    }
}

// Function to generate a random cost matrix
void generate_random_cost_matrix(int **cost_matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cost_matrix[i][j] = rand() % 20 + 1;  // Random cost between 1 and 100
        }
    }
}

// Main function for Brute Force Assignment
void brute_force_assignment(int **cost_matrix, int n) {
    int min_cost = 1000000;  // Start with a large value
    int *best_assignment = (int *)malloc(n * sizeof(int));
    int *arr = (int *)malloc(n * sizeof(int));
    
    // Create an array of job indices (0 to n-1)
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    // Generate all permutations
    permute(arr, 0, n - 1, n, cost_matrix, &min_cost, best_assignment);
    
    // Print the best assignment and its cost
    printf("Minimum cost: %d\n", min_cost);
    printf("Best assignment: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", best_assignment[i]);
    }
    printf("\n");
    
    free(best_assignment);
    free(arr);
}

// Driver function to test the brute-force assignment
int main() {
    srand(time(NULL));
    int n;
    
    printf("Enter the number of workers/jobs (n): ");
    scanf("%d", &n);
    
    // Allocate memory for the cost matrix
    int **cost_matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        cost_matrix[i] = (int *)malloc(n * sizeof(int));
    }
    
    // Generate a random cost matrix
    generate_random_cost_matrix(cost_matrix, n);
    
    // Display the cost matrix
    printf("Cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", cost_matrix[i][j]);
        }
        printf("\n");
    }
    
    // Call the brute force function to solve the assignment problem
    brute_force_assignment(cost_matrix, n);
    
    // Free the allocated memory
    for (int i = 0; i < n; i++) {
        free(cost_matrix[i]);
    }
    free(cost_matrix);
    
    return 0;
}
