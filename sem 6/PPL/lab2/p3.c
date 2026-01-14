#include <mpich/mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int n = size - 1;
	int* a = malloc(n * sizeof(int));
	int pack_size;

	MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &pack_size);

	int buf_size = (pack_size + MPI_BSEND_OVERHEAD) * n;
	int* buf = malloc(buf_size);

	int x;

	if (rank == 0) {
		printf("[Master] Enter %d numbers: ", n);
		for (int i = 0; i < n; i += 1)
			scanf("%d", &a[i]);
		MPI_Buffer_attach(buf, buf_size);
		for (int i = 1; i < size; i += 1)
			MPI_Bsend(&a[i - 1], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		MPI_Buffer_detach(buf, &buf_size);
	} else {
		MPI_Recv(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("[Rank %d] Number: %d\n", rank, x * x * (x % 2 == 0 ? 1 : x));
	}
	free(a);
	free(buf);
	MPI_Finalize();
	return 0;
}
