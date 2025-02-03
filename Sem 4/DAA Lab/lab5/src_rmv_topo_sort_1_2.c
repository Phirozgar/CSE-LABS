#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Graph structure
struct Graph {
    int V; // Number of vertices
    int adj[MAX][MAX]; // Adjacency matrix
};

// Function to perform Topological Sort using Source Removal technique
void topologicalSortSourceRemoval(struct Graph* graph) {
    int in_degree[MAX] = {0};  // Array to store in-degrees
    int result[MAX];  // Array to store the topological order
    int index = 0;

    // Calculate in-degree of each vertex
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            if (graph->adj[j][i] == 1) in_degree[i]++;
        }
    }
    // Source removal process
    while (1) {
        int foundSource = 0;
        for (int i = 0; i < graph->V; i++) {
            if (in_degree[i] == 0) {
                result[index++] = i;  // Add source node to result
                in_degree[i] = -1;  // Mark as processed
                // Remove the source node from the graph (reduce in-degrees of its neighbors)
                for (int j = 0; j < graph->V; j++) {
                    if (graph->adj[i][j] == 1) in_degree[j]--;
                }
                foundSource = 1;
                break;
            }
        }
        if (!foundSource) break;
    }
    printf("Topological Sort (using Source Removal): ");
    for (int i = 0; i < graph->V; i++) printf("%d ", result[i]);
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

    topologicalSortSourceRemoval(&graph);

    return 0;
}
