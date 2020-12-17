#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <random>
#include <time.h>
#define vsize 1000

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

void funcion6_BCAST(int argc, char* argv[], char* text) {
	int rank, size, length, root;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	root = 0;
	const int sizeBuffer = 480001;
	char message[sizeBuffer];

	double tinicial = MPI_Wtime();
	if (rank == 0) {
		sprintf_s(message, text);
	}
	MPI_Bcast(&message, sizeBuffer, MPI_CHAR, root, MPI_COMM_WORLD);	
	double tfinal = MPI_Wtime() - tinicial;
	printf("\t[Proceso %d] He recibido del proceso %d, el mensaje de longitud %d, con tiempo: %f s.\n", rank, root, strlen(message), tfinal);
	MPI_Finalize();
	return;
}

void funcion6_PtP(int argc, char* argv[], char * text) {
	int rank, size, length, root;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	root = 0;
	const int sizeBuffer = 480001;
	char message[sizeBuffer];
	char messa[sizeBuffer];

	MPI_Status status[2];
	MPI_Request request[2];

	double tinicial = MPI_Wtime();
	if (rank == 0) {		
		sprintf_s(message, text);
		for (int i = 1; i < size; i++) {
			MPI_Isend(&message, sizeBuffer, MPI_CHAR, i, 1, MPI_COMM_WORLD, &request[1]);
		}		
	} else {		
		MPI_Irecv(&messa, sizeBuffer, MPI_CHAR, root, 1, MPI_COMM_WORLD, &request[0]);
	}
	MPI_Waitall(2, request, status);
	double tfinal = MPI_Wtime() - tinicial;
	printf("\t[Proceso %d] He recibido del proceso %d, el mensaje de longitud %d, con tiempo: %f s.\n", rank, root, strlen(messa), tfinal);
	MPI_Finalize();
}

char* generateChar(int size) {
	int s = size + 1;
	char * res = new char[s];
	for (int i = 0; i < size; i++) {
		res[i] = (char) ((rand() % (122 - 97)) + 97);
	}
	res[size] = '\0';
	return res;
}

void funcion6(int argc, char* argv[], int size, bool bcast) {
	char* text = generateChar(size);
	if (bcast) {
		funcion6_BCAST(argc, argv, text);
	} else {
		funcion6_PtP(argc, argv, text);
	}		
}

void funcion7(int argc, char* argv[]) {
	int rank, size, length, root, tot;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	root = 0;
	const int mult = 2;
	tot = size*mult;

	float* values = new float[tot];
	if (rank == root) {		
		float sum = 0;
		for (int i = 0; i < tot; i++) {
			values[i] = (float)i;
			sum += values[i];
			printf("%4.2f ", values[i]);
		}		
		printf("----La suma total es: %f\n", sum);
	}

	float recv[mult];
	MPI_Scatter(values, mult, MPI_FLOAT, recv, mult, MPI_FLOAT, root, MPI_COMM_WORLD);

	float sumT = 0;
	for (int x = 0; x < mult; x++) {
		sumT += recv[x];
	}
	printf("[Proceso %d] La suma de mis elementos es: %f\n", rank, sumT);

	float* recvSum = NULL;
	if (rank == root) {
		recvSum = new float[size];
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Gather(&sumT, 1, MPI_FLOAT, recvSum, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

	if (rank == root) {
		float sumTotal = 0;
		for (int i = 0; i < size; i++) {
			sumTotal += recvSum[i];
		}
		printf("La suma de los elementos es: %f\n", sumTotal);
	}	
	MPI_Finalize();
}

void funcion8(int argc, char* argv[]) {
	int rank, size, length, root, tot;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	root = 0;
	const int mult = 10000;
	tot = size * mult;
	double startT;

	double* values = new double[tot];
	if (rank == root) {		
		for (int i = 0; i < tot; i++) {
			values[i] = (double)i;
		}

		double start = MPI_Wtime();
		double sum = 0;
		for (int j = 0; j < tot; j++) {
			for (int x = 0; x < 10000; x++) sum += values[j];
		}
		double end = MPI_Wtime() - start;
		printf("La suma total en secuencial es: %f\n", sum);
		printf("El tiempo total en secuencial es: %f\n", end);

		startT = MPI_Wtime();
	}

	double recv[mult];
	MPI_Scatter(values, mult, MPI_DOUBLE, recv, mult, MPI_DOUBLE, root, MPI_COMM_WORLD);

	double sumT = 0;
	for (int x = 0; x < mult; x++) {
		for (int i = 0; i < 10000; i++)	sumT += recv[x];
	}
	//printf("[Proceso %d] La suma de mis elementos es: %f\n", rank, sumT);

	double* recvSum = NULL;
	if (rank == root) {
		recvSum = new double[size];
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Gather(&sumT, 1, MPI_DOUBLE, recvSum, 1, MPI_DOUBLE, root, MPI_COMM_WORLD);

	if (rank == root) {
		double sumTotal = 0;
		for (int i = 0; i < size; i++) {
			sumTotal += recvSum[i];
		}
		double endT = MPI_Wtime() - startT;
		printf("La suma de los elementos en paralelo es: %f\n", sumTotal);
		printf("El tiempo total en paralelo es: %f\n", endT);
	}
	MPI_Finalize();
}

void funcion9(int argc, char* argv[]) {
	int rank, size, length, root, tot;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	root = 0;
	const int mult = 2;
	tot = size * mult;

	float* values = new float[tot];
	if (rank == root) {
		float sum = 0;
		for (int i = 0; i < tot; i++) {
			values[i] = (float)i;
			sum += values[i];
			printf("%4.2f ", values[i]);
		}
		printf("----La suma total es: %f\n", sum);
	}

	float recv[mult];
	MPI_Scatter(values, mult, MPI_FLOAT, recv, mult, MPI_FLOAT, root, MPI_COMM_WORLD);

	float sumT = 0;
	for (int x = 0; x < mult; x++) {
		sumT += recv[x];
	}
	printf("[Proceso %d] La suma de mis elementos es: %f\n", rank, sumT);

	MPI_Barrier(MPI_COMM_WORLD);

	float sumTotal;
	MPI_Reduce(&sumT, &sumTotal, 1, MPI_FLOAT, MPI_SUM, root, MPI_COMM_WORLD);

	if (rank == root) {		
		printf("La suma de los elementos es: %f\n", sumTotal);
	}
	MPI_Finalize();
}

void funcion10(int argc, char* argv[]) {
	int rank, size, length, root, tot;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	MPI_Get_processor_name(name, &length);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	root = 0;
	const int mult = 10000;
	tot = size * mult;
	double startT = MPI_Wtime();

	double* values = new double[tot];
	if (rank == root) {
		for (int i = 0; i < tot; i++) {
			values[i] = (double)i;
		}

		double start = MPI_Wtime();
		double sum = 0;
		for (int j = 0; j < tot; j++) {
			for (int x = 0; x < 10000; x++) sum += values[j];
		}
		double end = MPI_Wtime() - start;
		printf("La suma total en secuencial es: %f\n", sum);
		printf("El tiempo total en secuencial es: %f\n", end);

		startT = MPI_Wtime();
	}

	double recv[mult];
	MPI_Scatter(values, mult, MPI_DOUBLE, recv, mult, MPI_DOUBLE, root, MPI_COMM_WORLD);

	double sumT = 0;
	for (int x = 0; x < mult; x++) {
		for (int i = 0; i < 10000; i++) sumT += recv[x];
	}
	//printf("[Proceso %d] La suma de mis elementos es: %f\n", rank, sumT);

	MPI_Barrier(MPI_COMM_WORLD);

	double sumTotal;
	MPI_Reduce(&sumT, &sumTotal, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

	if (rank == root) {
		double endT = MPI_Wtime() - startT;
		printf("La suma de los elementos en paralelo es: %f\n", sumTotal);
		printf("El tiempo total en paralelo es: %f\n", endT);
	}
	MPI_Finalize();
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	//funcion1(argc, argv);
	//funcion2(argc, argv);
	//funcion3(argc, argv);
	//funcion4(argc, argv);
	//funcion5(argc, argv);
	//funcion6(argc, argv, 480000, true);
	//funcion7(argc, argv);

	/*SIN DEFENDER*/
	//funcion8(argc, argv);
	//Este método es igual que el 10. funcion9(argc, argv);
	funcion10(argc, argv);
	return 0;
}