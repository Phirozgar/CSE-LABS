#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_FACTORS 1024
int opCount = 0;

// Struct to store factors of a number
typedef struct
{
    int size;               // Size of the factorization
    int factors[MAX_FACTORS + 1];  // Array to store prime factors
    int freq[MAX_FACTORS + 1]; // Array to store frequency of the factors
} primeFactors;

// Function to find the prime factorization of a number
void findPrimeFactors(int number, primeFactors* pf)
{
    int currentFactor = 1;  // Start from index 1
    int remaining = number;

    for (int i = 2; i <= remaining; i++) {
        int exponentCount = 0;

        // Check if i is a divisor of remaining and count its exponent
        while (remaining % i == 0) {
            ++opCount;
            exponentCount++;
            remaining = remaining / i;
        }

        // If i is a prime factor, store it and its exponent
        if (exponentCount > 0) {
            pf->freq[currentFactor] = exponentCount;
            pf->factors[currentFactor] = i;
            currentFactor++;
        }
    }

    pf->size = currentFactor - 1; // Set the size of the factorization
}

// Function to display the prime factorization
void display(int number, primeFactors pf)
{
    printf("Prime factorization of %d = ", number);

    // Loop through the factors and display them starting from index 1
    for (int i = 1; i <= pf.size; i++) {
        ++opCount;
        printf("%d", pf.factors[i]);
        // If the exponent is greater than 1, display it
        if (pf.freq[i] > 1) 
            printf("^%d", pf.freq[i]);
        if (i < pf.size) 
            printf(" * ");
        else 
            printf("\n");
    }
}

// Function to calculate the GCD using the Middle School procedure (Prime factorization method)
int gcdUsingMiddleSchoolProcedure(int num1, int num2)
{
    primeFactors factors1, factors2;
    int gcd = 1;  // Initialize the GCD result
    int i = 1, j = 1;  // Indexes for traversing the factorizations

    findPrimeFactors(num1, &factors1);
    display(num1, factors1);

    findPrimeFactors(num2, &factors2);
    display(num2, factors2);

    // Compare prime factors and compute GCD
    while (i <= factors1.size && j <= factors2.size) {
        if (factors1.factors[i] < factors2.factors[j]) {
            i++;  // Move to the next factor of num1
            ++opCount;
        }
        else if (factors2.factors[j] < factors1.factors[i]) {
            j++;  // Move to the next factor of num2
            ++opCount;
        }
        else { // If both factors are the same
            int minExponent = (factors1.freq[i] < factors2.freq[j]) ? factors1.freq[i] : factors2.freq[j];
            // Multiply by the smallest exponent of the common factor
            int factorPower = 1;
            for (int k = 0; k < minExponent; k++) {
                ++opCount;
                factorPower *= factors1.factors[i];
            }
            gcd *= factorPower;
            i++;  // Move to the next factor of num1
            j++;  // Move to the next factor of num2
        }
    }

    return gcd;  // Return the calculated GCD
}

// Driver code
int main()
{
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    printf("GCD( %d , %d ) = %d\n", num1, num2, gcdUsingMiddleSchoolProcedure(num1, num2));
    printf("%d Operations were done\n", opCount);
    return 0;
}
