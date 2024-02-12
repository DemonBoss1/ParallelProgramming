
#include "main_header.h"

#define _GNU_SOURCE

int getSize(char *arg)
{
	int numberLenght = 0;
	while (*arg != '\0')
	{

		printf("%c", *arg);

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

		printf("\n%5d,", (*arg - '0'));
		printf("%10d,", sum);
		printf("%5d", i);
	}
	return size;
}

int main(int argc, char *argv[])
{

	if (argc == 1)
		return 1;

	int size = getSize(argv[1]);
	int *matrix;

	printf("\n%d\n", size);

	printf("\n%s\n", argv[1]);

	return 0;
}