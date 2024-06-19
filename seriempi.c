#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_TERMS 1000

void generar_serie(int inicio, int paso, int terminos, int *serie) {
    for (int i = 0; i < terminos; i++) {
        serie[i] = inicio + i * paso;
    }
}

int main(int argc, char *argv[]) {
    int rank, size, m, n;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Ingrese el número de términos por vector (N): ");
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    m = size; // El número de vectores es igual al número de procesos

    int paso = 2;
    int inicio = 2 + rank * paso * n;
    int terminos = (MAX_TERMS < n) ? MAX_TERMS : n;
    int serie[MAX_TERMS];

    generar_serie(inicio, paso, terminos, serie);

    if (rank == 0) {
        printf("Series generadas:\n");
    }

    MPI_Barrier(MPI_COMM_WORLD); // Sincronizar la salida

    printf("Proceso %d: ", rank);
    for (int i = 0; i < terminos; i++) {
        printf("%d ", serie[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
