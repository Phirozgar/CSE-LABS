#include <mpi.h>
#include <stdio.h>
#include <math.h>

int fac(int rank) {
	if(rank == 0 || rank == 1) return 1;
	return rank * fac(rank-1);
}

int fib(int rank) {
	if(rank < 2) return rank;
	return fib(rank - 1) + fib(rank - 2);
}
	
int main(int argc, char* argv[]) {
	int rank, size, res;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_rank(MPI_COMM_WORLD, &size);
	
	if(rank % 2 == 0) res = fac(rank);
	else res = fib(rank);
	printf("\nR%d : %d", rank, res);
	
	MPI_Finalize();
	return 0;
}

