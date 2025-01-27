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

// Function for Depth-First Search (DFS)
void dfs(Nodeptr* arrayOfPointers, int n, int startIndex) {
    printf("\nDepth-First Search Traversal:\n");

    int stack[n];
    int top = -1;
    arrayOfPointers[startIndex]->visited = 1;
    stack[++top] = startIndex;
    printf("Pushed: %c\n", arrayOfPointers[startIndex]->data);  // Push order

    while (top >= 0) {
        int currentIndex = stack[top]; // Don't pop yet, check if we need to backtrack
        Nodeptr curr = arrayOfPointers[currentIndex]->next;
        int allVisited = 1; // Flag to check if all neighbors are visited

        while (curr) {
            int nextIndex = getIndex(arrayOfPointers, n, curr->data);
            if (!arrayOfPointers[nextIndex]->visited) {
                arrayOfPointers[nextIndex]->visited = 1;
                stack[++top] = nextIndex;
                printf("Pushed: %c\n", arrayOfPointers[nextIndex]->data);  // Push order
                allVisited = 0; // We found an unvisited neighbor
                break;
            }
            curr = curr->next;
        }

        if (allVisited) {
            // If all neighbors have been visited, pop the node
            printf("Popped: %c\n", arrayOfPointers[currentIndex]->data);
            top--; // Backtrack
        }
    }
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    Nodeptr arrayOfPointers[n];

    // Create vertices
    for (int i = 0; i < n; i++) {
        printf("Enter label for vertex %d: ", i + 1);
        char c;
        scanf(" %c", &c);  // Notice the space before %c to consume any leftover newline
        arrayOfPointers[i] = getNode(c);
        arrayOfPointers[i]->index = i;
    }

    // Create adjacency list and display it
    adjacencyList(arrayOfPointers, n);

    // Perform DFS for each node (in case of disconnected graph)
    for (int i = 0; i < n; i++) {
        if (!arrayOfPointers[i]->visited) {
            // Perform DFS starting from this unvisited node
            dfs(arrayOfPointers, n, i);
        }
    }

    // Reset visited status for future traversals (optional)
    for (int i = 0; i < n; i++) {
        arrayOfPointers[i]->visited = 0;
    }

    return 0;
}
