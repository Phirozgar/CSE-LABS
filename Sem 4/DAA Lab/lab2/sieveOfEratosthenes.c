int* sieveOfEratosthenes(int num){
    int sieve[2][num]; // first row of matrix is for primes, second row is for their frequency
    
    for (int i = 2; i < num+1 ; i++)
        sieve[0][i] = i;

    for (int i = 2; i*i < num ; i++){
        if(sieve[0][i]){
            int j = i*i;
            while(j <= num){
                sieve[0][j] = 0;
                j += i;
            }
        }
    }
}