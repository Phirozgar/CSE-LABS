#include <mpich/mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int x;
	if (rank == 0) {
		printf("[Master] Enter number: ");
		scanf("%d", &x);
		MPI_Ssend(&x, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
	} 
	MPI_Recv(&x, 1, MPI_INT, (rank - 1 + size) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("[Rank %d] Received: %d\n", rank, x);
	
	if (rank == 0)
		printf("[Master] Roundabout Complete. Final value: %d\n", x);
	else {
		x += 1;
		MPI_Ssend(&x, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
