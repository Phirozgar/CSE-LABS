#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	int rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	char msg[] = "PhIrOz";
	printf("\nRank %d : %s", rank, msg); 
	msg[rank] ^= 32;
	printf("\t%s", msg); 
	MPI_Finalize();
	return 0;
}

