
#include "main_header.h"

#define _GNU_SOURCE

int getNumber(char *arg)
{
	int numberLenght = 0;
	while (*arg != '\0')
	{
		numberLenght++;
		arg++;
	}
	unsigned int size = 0;
	float degree = 0;
	for (int i = 0; i < numberLenght; i++)
	{
		if (i == 0)
			degree = 1;
		else
			degree *= 10;
		arg--;
		int sum = (*arg - '0');
		for(int j=0;j<i;j++) sum *= 10;
		size += sum;
	}
	return size;
}

int* getRandomMatrix(int size){
	srand(time(NULL));
	int *matrix = calloc(size*size, sizeof(int));
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++){
			matrix[i*size+j]=rand()%2;
		}
	return matrix;
}

int* getRandomMatrixSymmetry(int size){
	srand(time(NULL));
	int *matrix = calloc(size*size, sizeof(int));
	for(int i=0; i<size; i++)
		for(int j=i; j<size; j++){
			matrix[i*size+j]=rand()%2;
			if(i!=j) matrix[j*size+i] = matrix[i*size+j];
		}
	return matrix;
}

void printMatrix(int *matrix, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			printf("%5d",matrix[i*size+j]);
		}
		printf("\n");
	}
}

int checkSymmetry(int *matrix, int size){
	for (int i=0; i<size; i++){
		for(int j=i+1; j<size; j++){
			if(matrix[i*size+j] == matrix[j*size+i]) printf("1");
			else printf("0");
		}
	}
	printf("\n");
}

void* empty(){}

int main(int argc, char *argv[])
{
	if (argc == 1)
		return 1;

	int size = getNumber(argv[1]);

	int count = size/2*(size-1);
	int countThreads;
	if (argc == 2)
		countThreads = 1;
	else
		countThreads = getNumber(argv[2]);

	pthread_t* h_process_command_thread = calloc(countThreads, sizeof(pthread_t));
	for(int i=0; i<countThreads; i++){
		int ret;
		ret = pthread_create(
			&h_process_command_thread[i],
			NULL,
			empty,
			NULL
		);
		if (ret != 0) {
			printf("ERROR: pthread_create failed [%d]\n", ret);
			return -1;
		}
		printf("%ld\n",h_process_command_thread[i]);
	}
	printf("\n%5d\n",countThreads);

	int *matrix = getRandomMatrixSymmetry(size);

	checkSymmetry(matrix, size);

	printMatrix(matrix, size);

	return 0;
}