#include <stdio.h>
#include <stdlib.h>

struct node {
    char data;
    int index;
    int visited;
    struct node* next;
};
typedef struct node* Nodeptr;

// Function to create a new node
Nodeptr getNode(char c) {
    Nodeptr newnode = (Nodeptr)malloc(sizeof(struct node));
    newnode->next = NULL;
    newnode->data = c;
    newnode->visited = 0;
    return newnode;
}

// Function to get the index of a node based on its data
int getIndex(Nodeptr* arrayOfPointers, int size, char c) {
    for (int i = 0; i < size; i++) {
        if (arrayOfPointers[i]->data == c) {
            return arrayOfPointers[i]->index;
        }
    }
    return -1; // Return -1 if not found
}

// Function to create the adjacency list
void adjacencyList(Nodeptr* arrayOfPointers, int n) {
    for (int i = 0; i < n; i++) {
        Nodeptr curr = arrayOfPointers[i];
        printf("Enter number of neighbours of %c: ", curr->data);
        int num;
        scanf("%d", &num);
        getchar(); // Consume newline character left in input buffer
        while (num > 0) {
            printf("Enter neighbour: ");
            char c;
            scanf("%c", &c);
            getchar(); // Consume newline character
            Nodeptr newnode = getNode(c);
            curr->next = newnode;
            curr = newnode;
            num--;
        }
    }

    // Display adjacency list
    printf("\nAdjacency List Representation:\n");
    for (int i = 0; i < n; i++) {
        Nodeptr curr = arrayOfPointers[i];
        printf("%c", curr->data);
        curr = curr->next;
        while (curr) {
            printf(" -> %c", curr->data);
            curr = curr->next;
        }
        printf("\n");
    }
}

// Function to create and display the adjacency matrix
void adjacencyMatrix(Nodeptr* arrayOfPointers, int n) {
    int grid[n][n];

    // Initialize the adjacency matrix to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = 0;
        }
    }

    // Fill the adjacency matrix
    for (int i = 0; i < n; i++) {
        Nodeptr curr = arrayOfPointers[i]->next;
        while (curr) {
            int j = getIndex(arrayOfPointers, n, curr->data);
            if (j != -1) {
                grid[i][j] = 1;
                grid[j][i] = 1; // Undirected graph
            }
            curr = curr->next;
        }
    }

    // Display adjacency matrix
    printf("\nAdjacency Matrix Representation:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    getchar(); // Consume newline character

    Nodeptr arrayOfPointers[n];

    // Create vertices
    for (int i = 0; i < n; i++) {
        printf("Enter label for vertex %d: ", i + 1);
        char c;
        scanf("%c", &c);
        getchar(); // Consume newline character
        arrayOfPointers[i] = getNode(c);
        arrayOfPointers[i]->index = i;
    }

    // Create adjacency list and display it
    adjacencyList(arrayOfPointers, n);

    // Create adjacency matrix and display it
    adjacencyMatrix(arrayOfPointers, n);

    return 0;
}
