#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* left;
    struct node* right;
};
typedef struct node* Nodeptr;


Nodeptr getNode(int num){
    Nodeptr newnode = (Nodeptr)malloc(sizeof(struct node));
    newnode->right = NULL;
    newnode->left = NULL;
    newnode->data = num;
    return newnode;
}

Nodeptr construct(Nodeptr head, Nodeptr newnode){ 
    if(!head) return newnode;

    if(head->right && newnode->data > head->data) 
        construct(head->right, newnode);
    else if(head->left && newnode->data < head->data) 
        construct(head->left, newnode);
    else if(newnode->data > head->data) 
        head->right = newnode;
    else if(newnode->data < head->data)
        head->left = newnode;

    return head;
}

void in(Nodeptr head){
    if(head->left) in(head->left);
    printf("%d\t", head->data);
    if(head->right) in(head->right);
}

void pre(Nodeptr head){
    printf("%d\t", head->data);
    if(head->left) pre(head->left);
    if(head->right) pre(head->right);
}

void post(Nodeptr head){
    if(head->left) post(head->left);
    if(head->right) post(head->right);
    printf("%d\t", head->data);
}

void search(Nodeptr head, int key){
    if(key > head->data && head->right) search(head->right, key);
    else if (key < head->data && head->left) search(head->left, key);
    else if (key == head-> data) printf("\nKey found");
    else printf("Key not in tree");
}
 
int main(){
    int choice = 10;
    printf("Enter data for head of tree: ");
    int number;
    scanf("%d", &number);
    Nodeptr head = getNode(number);
    construct(NULL, head);
    while(choice != 3){
        printf("Enter choice: \n1.Insert 2.Search 3.Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1: 
            printf("Enter number: ");
            int num;
            scanf("%d", &num);
            Nodeptr newnode = getNode(num);
            construct(head, newnode);
            break;
        case 2: 
            printf("Enter number: ");
            scanf("%d", &num);
            search(head, num);
            break;
        }
    }
    printf("\nPreorder Traversal: \n");
    pre(head);
    printf("\nInorder Traversal: \n");
    in(head);
    printf("\nPostorder Traversal: \n");
    post(head);
    return 0;
}