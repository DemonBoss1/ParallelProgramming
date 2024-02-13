
#include "main_header.h"

#define _GNU_SOURCE

int getSize(char *arg)
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
	int *matrix = calloc(size*size, sizeof(int));
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++){
			matrix[i*size+j]=rand()%10;
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

int main(int argc, char *argv[])
{

	if (argc == 1)
		return 1;

	int size = getSize(argv[1]);
	int *matrix = getRandomMatrix(size);

	printMatrix(matrix, size);

	return 0;
}