#include "../btree.h"
int main() {
    nodeptr root = createBTree();
    int n1, n2;
    printf("Enter the two nodes to find the CCA: ");
    scanf("%d %d", &n1, &n2);
    nodeptr cca = findLCA(root, n1, n2);
    if (cca)
        printf("The Closest Common Ancestor of %d and %d is: %d\n", n1, n2, cca->data);
    else
        printf("One or both nodes not found in the tree.\n");
    return 0;
}