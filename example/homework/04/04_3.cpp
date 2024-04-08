#include <mpi.h>
#include <cstdio>
#include <cstdlib>
int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *sendbuf = (int *)malloc(size * sizeof(int));
    int *recvbuf = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        sendbuf[i] = rank * size + i;
    }

    MPI_Alltoall(sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, MPI_COMM_WORLD);

    printf("Process %d received values: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    free(sendbuf);
    free(recvbuf);
    MPI_Finalize();
    return 0;
}
