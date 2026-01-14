#include <mpich/mpi.h>
#include <stdio.h>
#include <string.h>

#define MAX_STR 128
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char msg[MAX_STR];
    if (rank == 0) {
        printf("[Master] Enter message: ");
        gets(msg);
        MPI_Ssend(msg, strlen(msg) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(msg, MAX_STR, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("[Master] Received message: %s\n", msg);
    } else {
        MPI_Recv(msg, MAX_STR, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; msg[i] != '\0'; i += 1)
            msg[i] ^= 32;
        MPI_Ssend(msg, strlen(msg) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
