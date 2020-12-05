#include "mpi.h"
#include <stdio.h>

void funcion1(int argc, char* argv[]) {
	int rank, size, length;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("[Proceso %d] Hola desde %s!\n", rank, name);
	if (rank == 0) printf("El nUmero total de procesos MPI es % d.\n", size);
	MPI_Finalize();
	return;
}

void funcion2(int argc, char* argv[]) {
	int rank, size, length;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double tinicial = MPI_Wtime();
	float res = 48.5;
	for (float i = 1; i < 15000000; i++) {
		res *= i*i*i*i*i;
	}
	double tfinal = MPI_Wtime();
	double tiempo = tfinal - tinicial;
	printf("[Proceso %d] Ha tardado %4.8f s!, el resultado es %4.4f\n", rank, tiempo, res);
	MPI_Finalize();
	return;
}

int main(int argc, char* argv[])
{
	//funcion1(argc, argv);
	funcion2(argc, argv);
	return 0;
}