#include <mpi.h>
#include <stdio.h>
#include <math.h>
int main(int argc, char* argv[]) {
	int rank, size, res, a = 5, b = 2;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_rank(MPI_COMM_WORLD, &size);
	
	switch(rank) {
		case 0: { res = a+b; break; }
		case 1: { res = a-b; break; }
		case 2: { res = a*b; break; } 
		case 3: { res = a/b; break; }
		case 4: { res = a%b; break; }
		defaut: printf("No can't do");
	}
	printf("\nRank: %d, Result: %d", rank, res);
	MPI_Finalize();
	return 0;
}
