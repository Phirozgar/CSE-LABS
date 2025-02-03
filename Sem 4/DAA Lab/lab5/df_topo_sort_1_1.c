#include "../stack.h"
#define MAX 10

// Graph structure
struct Graph {
    int V; // Number of vertices
    int adj[MAX][MAX]; // Adjacency matrix
};

// Function to perform DFS and fill the stack
void dfs(struct Graph* graph, int v, int visited[], struct Stack* stack) {
    visited[v] = 1;  // Mark the current node as visited
    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[v][i] == 1 && !visited[i]) {
            dfs(graph, i, visited, stack);
        }
    }
    push(stack, v);  // Add node to stack after visiting all neighbors
}

// Function to perform Topological Sort using DFS
void topologicalSortDFS(struct Graph* graph) {
    int visited[MAX] = {0};  // Array to track visited nodes
    struct Stack stack;
    initStack(&stack);
    
    // Call DFS for each node
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            dfs(graph, i, visited, &stack);
        }
    }

    // Print the topologically sorted order
    printf("Topological Sort (using DFS): ");
    while (stack.top != -1) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
}

int main() {
    struct Graph graph = {6, {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0}
    }};

    topologicalSortDFS(&graph);

    return 0;
}
