
#include <stdio.h>
#include <stdlib.h>
 
struct node{
    int data;
    struct node* l;
    struct node* r;  
};
typedef struct node* nodeptr;

nodeptr getNode(int num) {
    nodeptr newnode = (nodeptr)malloc(sizeof(struct node));
    newnode->data = num;
    newnode->l = newnode->r = NULL;
    return newnode;
}

nodeptr createBLeaf(nodeptr head, int num) {
    if(num > head->data && head->r) createBLeaf(head->r, num);
    if(num < head->data && head->l) createBLeaf(head->l, num);
    if(num > head->data && !head->r) head->r = getNode(num);
    if(num < head->data && !head->l) head->l = getNode(num);
}

nodeptr createBTree() {
    int num;
    printf("Enter data for header node: ");
    scanf("%d", &num);
    nodeptr head = getNode(num);
    int option = 0;
    do{
        printf("1.Add to Tree\t2.End");
        scanf("%d", &option);
        int leafData;
        printf("Enter data for leaf node: ");
        scanf("%d", &leafData);
        nodeptr leaf = createBLeaf(head, leafData);
    }while (option != 2);
}

nodeptr findLCA(nodeptr root, int n1, int n2) {
    if (!root) return root;
    if (root->data > n1 && root->data > n2) return findLCA(root->l, n1, n2);
    if (root->data < n1 && root->data < n2) return findLCA(root->r, n1, n2);
    return root;
}