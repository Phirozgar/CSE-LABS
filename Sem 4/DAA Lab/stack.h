#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct Stack {
    int items[MAX];
    int top;
};

// Function to initialize the stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Function to push an item to the stack
void push(struct Stack* stack, int value) {
    stack->items[++(stack->top)] = value;
}

// Function to pop an item from the stack
int pop(struct Stack* stack) {
    return stack->items[(stack->top)--];
}