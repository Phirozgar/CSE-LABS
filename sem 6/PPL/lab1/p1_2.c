#include <mpi.h>
#include <stdio.h>
#include <math.h>
int main(int argc, char* argv[]) {
	int rank, size, n, x = 5;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_rank(MPI_COMM_WORLD, &size);
	if(rank % 2 == 0) printf("\nHello from %d", rank);
	else printf("\nWorld");
	MPI_Finalize();
	return 0;
}
