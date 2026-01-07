#include <mpi.h>
#include <stdio.h>
#include <math.h>
int main(int argc, char* argv[]) {
	int rank, size, n, x = 5;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_rank(MPI_COMM_WORLD, &size);
	int result = pow(x, rank);
	printf("\nProcessor %d has value = %d", rank, result);
	MPI_Finalize();
	return 0;
}
