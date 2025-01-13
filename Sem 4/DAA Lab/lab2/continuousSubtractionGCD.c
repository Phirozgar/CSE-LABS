#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    // middle school algorithm is just repeated subtraction until both numbers are equal
    while (a != b) {
        if (a > b) a = a - b;
        else b = b - a;
    }
    return a; // Once a == b, that value is the GCD
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    printf("\nGCD of %d and %d is: %d\n", a, b, gcd(a, b));
    return 0;
}