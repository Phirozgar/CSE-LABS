#include <stdio.h>
#include <stdlib.h>
 
struct node{
    int data;
    int index;
    int visited;
    struct node* next;
};
typedef struct node* Nodeptr;

Nodeptr getNode(char c){
    Nodeptr newnode = (Nodeptr)malloc(sizeof(struct node));
    newnode->next = NULL;
    newnode->data = c;
    newnode->visited = 0;
    return newnode;
}

int getIndex(Nodeptr* arrayOfPointers, char c){
    for (int i = 0; i < sizeof(arrayOfPointers); i++)
    {
        if(arrayOfPointers[i]->data == c) 
            return arrayOfPointers[i]->index;
    }
}

void adjacencyList(Nodeptr* arrayOfPointers){ //takes an array of Nodeptrs as argument, each Nodeptr is a vertex in the graph
    for (int i = 0; i < sizeof(arrayOfPointers); i++)
    {
        Nodeptr curr = arrayOfPointers[i]; // to make the liked list at each node you need a traversing pointer to link the neighbour nodes 
        printf("Enter number of neighbours to %c", curr->data);
        int num;
        scanf("%d", &num);
        while (num > 0)
        {
            printf("Enter neighbour: ");
            char c;
            scanf("%c", &c);
            Nodeptr newnode = getNode(c); // get data of neighbour and assign it some space
            curr->next = newnode; // link the neighbour to the list
            curr = newnode; // shift the current ptr to the newly added neighbour so next neighbour can be linked to it in the next iteration
            num--;
        }
    } 
    for (int i = 0; i < sizeof(arrayOfPointers); i++)
    {
        Nodeptr curr = arrayOfPointers[i]; // to display each node in each linked list you need a traversing ptr
        printf("\n%c", curr->data); //display starting vertex
        while (curr->next)
        {
            printf("--%c", curr->data); //display all neighbours
            curr = curr->next;
        }
    } 
    printf("\n");
}

void adjacencyMatrix(Nodeptr* arrayOfPointers){
    int n = sizeof(arrayOfPointers);
    int grid[n][n];

    for (int i = 0; i < n; i++)
    {
        Nodeptr curr = arrayOfPointers[i];
        while(curr->next){
            if(curr->next->visited == 1) continue;
            int j = getIndex(arrayOfPointers, curr->next->data);
            grid[i][j] = grid[j][i] = 1;
            curr->visited = curr->next->visited = 1;
            curr = curr->next;
        }        
    }
    for (int i = 0; i < n; i++)
    {
        for (int i = 0; i < n; i++)
        {
            
        }
              
    }
    
}
 
int main(){
    int n; 
    
    return 0;
}