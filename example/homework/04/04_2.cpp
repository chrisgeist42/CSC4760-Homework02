#include <mpi.h>
#include <cstdio>
#include <cstdlib>
int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sendbuf = rank + 1;
    int *recvbuf = (int *)malloc(size * sizeof(int));

    MPI_Gather(&sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(recvbuf, size, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received values: ", rank);
    for (int i = 0; i < size; i++) {
        printf("%d ", recvbuf[i]);
    }
    printf("\n");

    free(recvbuf);
    MPI_Finalize();
    return 0;
}
