#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

FILE OpenFile(char* filePath) 
{
	bool isSuccess = false;
	FILE *fptr;
	fptr = fopen(filePath, "r");

	if (fptr == NULL)
	{
		printf("Error, file not opened");
		exit(1);
	}

	return *fptr; 
}

int main(int argc, char *argv[])
{
	FILE openedFile = OpenFile("./file.txt");
	return 0; 
}
