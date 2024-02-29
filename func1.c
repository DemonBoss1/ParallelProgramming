
#include "main_header.h"

#define _GNU_SOURCE

char* isSymmetry;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

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

double* getRandomMatrix(int size){
	srand(time(NULL));
	double *matrix = calloc(size*size, sizeof(double));
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++){
			matrix[i*size+j]=rand()%2;
		}
	return matrix;
}

double* getMatrixFromConsol(int size){
	double * matrix;
	matrix = calloc(size*size, sizeof(double));
		printf("Введите массив: ");
		for(int i=0; i<size; i++)
			for(int j=0; j<size; j++){
				scanf("%lf", &matrix[i*size+j]);		
			}
	return matrix;
}

double* getRandomMatrixSymmetry(int size){
	srand(time(NULL));
	double *matrix = calloc(size*size, sizeof(double));
	for(int i=0; i<size; i++)
		for(int j=i; j<size; j++){
			matrix[i*size+j]=rand()%2;
			if(i!=j) matrix[j*size+i] = matrix[i*size+j];
		}
	return matrix;
}

void printMatrix(double *matrix, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			printf("%10.3lf",matrix[i*size+j]);
		}
		printf("\n");
	}
}

typedef struct 
{
	double *matrix;
	int size;
} matrixStruct;

typedef struct 
{
	matrixStruct *matrix;
	int startI;
	int startJ;
	int count;
} argCheckSymmetry;

argCheckSymmetry* getArgCheckSymmetry(matrixStruct* matrix, int* startI, int* startJ, int countNumber, int countThreads, int* countOverloadedStreams){
	argCheckSymmetry* arg = calloc(1, sizeof(argCheckSymmetry));
	int count;
	count = countNumber/countThreads;
	if(*countOverloadedStreams>0){
		count++;
		(*countOverloadedStreams)--;
	}
	arg->matrix = matrix;
	arg->startI = *startI;
	arg->startJ = *startJ;
	arg->count = count;
	int nextJ = *startJ + count;
	while(nextJ>=matrix->size){
		(*startI)++;
		nextJ = nextJ - matrix->size + (*startI) + 1;			
	}
	*startJ = nextJ;
	return arg;
}

int checkSymmetry(argCheckSymmetry* arg){
	double *matrix = arg->matrix->matrix;
	int size = arg->matrix->size;
	int counter = arg->count;
	for (int i=arg->startI; i<size; i++){
		for(int j=arg->startJ; j<size; j++){
			if(matrix[i*size+j]!=matrix[j*size+i]){
				(void)pthread_mutex_lock(&mtx);
				isSymmetry = 0;
				(void)pthread_mutex_unlock(&mtx);
			}
			if(counter<1) {
				return 0;
			}
		}
		arg->startJ++;
	}
	pthread_exit((void*)0);
}

void startPthreads(double* matrix, int size, int countThreads){
	matrixStruct* matrixArg = calloc(1, sizeof(matrixStruct));
	matrixArg->matrix = matrix;
	matrixArg->size = size;

	argCheckSymmetry** arg = calloc(countThreads, sizeof(argCheckSymmetry*));
	int startI = 0;
	int startJ = 1;
	int count = size*(size-1)/2;
	int countOverloadedStreams = count % countThreads;

	isSymmetry = 1;
	pthread_t* h_process_command_thread = calloc(countThreads, sizeof(pthread_t));

	for(int i=0; i<countThreads; i++){
		arg[i] = getArgCheckSymmetry(matrixArg, &startI, &startJ, count, countThreads, &countOverloadedStreams);
		int ret;
		ret = pthread_create(
			&h_process_command_thread[i],
			NULL,
			checkSymmetry,
			arg[i]
		);
		if (ret != 0) {
			printf("ERROR: pthread_create failed [%d]\n", ret);
			return -1;
		}
	}

	for(int i=0; i<countThreads; i++){
		pthread_join(h_process_command_thread[i], NULL);
		printf("JOIN ret thread value [%d]\n", i);
	}

}

void* empty(){}

int main(int argc, char *argv[])
{
	double *matrix;
	int size;
	if(argc < 2){
		printf("Введите размер массива: ");
		scanf("%d", &size);
		matrix = getMatrixFromConsol(size);
	}
	else{
		size = getNumber(argv[1]);
		matrix = getRandomMatrix(size);
	}

	int countThreads;
	if (argc < 3){
		printf("Введите число потоков: ");
		scanf("%d", &countThreads);
    }
	else
		countThreads = getNumber(argv[2]);

	

	startPthreads(matrix, size, countThreads);

	printf("\n");

	printMatrix(matrix, size);

	printf("\n%5d\n",isSymmetry);

	return 0;
}
