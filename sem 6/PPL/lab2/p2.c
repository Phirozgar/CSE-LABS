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
		for (int i = 1; i < size; i += 1)
			MPI_Send(&x, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	} else {
		MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("[Rank %d] Received: %d\n", rank, x);
	}
	MPI_Finalize();
	return 0;
}
