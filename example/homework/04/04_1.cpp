#include <mpi.h>
#include <cstdio>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int sendbuf = 10;
    int recvbuf;

    MPI_Bcast(&sendbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Reduce(&sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Bcast(&recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received value %d\n", rank, recvbuf);

    MPI_Finalize();
    return 0;
}
