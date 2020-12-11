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

void funcion3(int argc, char* argv[]) {
	int rank, size, length, compi, message;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank < size / 2) {
		compi = rank + size / 2;
	} else {
		compi = rank - size / 2;
	}
	
	MPI_Status status;
	MPI_Send(&rank, 1, MPI_INT, compi, 1, MPI_COMM_WORLD);
	MPI_Recv(&message, 1, MPI_INT, compi, 1, MPI_COMM_WORLD, &status);
	
	printf("[Proceso %d] Mi compi es %d, y recibi el mensaje %d\n", rank, compi, message);
	MPI_Finalize();
	return;
}

void funcion4(int argc, char* argv[]) {
	int rank, size, length, compi, message;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank < size / 2) {
		compi = rank + size / 2;
	}
	else {
		compi = rank - size / 2;
	}

	MPI_Status status[2];
	MPI_Request request[2];

	MPI_Isend(&rank, 1, MPI_INT, compi, 1, MPI_COMM_WORLD, &request[1]);
	MPI_Irecv(&message, 1, MPI_INT, compi, 1, MPI_COMM_WORLD, &request[0]);
	
	printf("Haciendo 10 tareas: ");
	for (int i = 0; i < 10; i++) {
		printf("%d ", i);
	}
	printf("\n");

	MPI_Waitall(2, request, status);

	printf("[Proceso %d] Mi compi es %d, y recibi el mensaje %d\n", rank, compi, message);
	MPI_Finalize();
	return;
}

void funcion5(int argc, char* argv[]) {
	int rank, size, length, compi, a;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank < size / 2) {
		compi = rank + size / 2;
	}
	else {
		compi = rank - size / 2;
	}

	MPI_Status status[2];
	MPI_Request request[2];

	char messa[17];
	char message[17];
	a = sprintf_s(messa, "%d - Hola pepito", rank);
	
	MPI_Isend(&messa, 17, MPI_CHAR, compi, 1, MPI_COMM_WORLD, &request[1]);
	MPI_Irecv(&message, 17, MPI_CHAR, compi, 1, MPI_COMM_WORLD, &request[0]);

	printf("Haciendo 10 tareas: ");
	for (int i = 0; i < 10; i++) {
		printf("%d ", i);
	}
	printf("\n");

	MPI_Waitall(2, request, status);

	printf("[Proceso %d] Mi compi es %d, y recibi el mensaje %s\n", rank, compi, message);
	MPI_Finalize();
	return;
}

void funcion6_BCAST(int argc, char* argv[]) {
	int rank, size, length, root;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	root = 0;
	const int sizeBuffer = 12;
	char message[sizeBuffer];	

	if (rank == 0) {
		int a = sprintf_s(message, "Hola pepito");		
	}
	MPI_Bcast(&message, sizeBuffer, MPI_CHAR, root, MPI_COMM_WORLD);
	printf("[Proceso %d] He recibido del proceso %d, el mensaje: %s\n", rank, root, message);
			
	MPI_Finalize();
	return;
}

void funcion6_PtP(int argc, char* argv[]) {

}

int main(int argc, char* argv[])
{
	//funcion1(argc, argv);
	//funcion2(argc, argv);
	//funcion3(argc, argv);
	//funcion4(argc, argv);
	//funcion5(argc, argv);
	funcion6_BCAST(argc, argv);
	//funcion6_PtP(argc, argv);
	return 0;
}