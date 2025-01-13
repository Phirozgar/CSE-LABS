#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    int min = (a < b) ? a : b; 
    // Check all integers from the smaller number down to 1
    for (int i = min; i > 0; i--) {
        if (a % i == 0 && b % i == 0) {
            return i; // Return the first common divisor, which is the GCD
        }
    }
    return 1; // If no common divisor found other then return 1
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    printf("The GCD of %d and %d is: %d\n", a, b, gcd(a, b));
    return 0;
}
