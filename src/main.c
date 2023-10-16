#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

FILE* OpenFile(char* filePath) 
{
	printf("Initiate OpenFile\n");
	FILE* fptr;
	fptr = fopen(filePath, "r");

	if (fptr == NULL)
	{
		perror("Error, could not open file\n");
		exit(1);
	}

	return fptr; 
}

char* ReadFile(FILE* file) 
{
	printf("Intiate ReadFile\n");
	char* code;
	char* contents;
	int index = 0;
	int asci;

	// allocate memory by size of file
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	code = malloc(fileSize);

	// read the contents of the file into an array
	while ((asci = fgetc(file)) != EOF)
	{
		code[index] = (char)asci;
		index++;
	}

	code[index] = '\0';

	fclose(file);

	strcpy(contents, code);

	free(code);

	return contents;
}

int main(int argc, char *argv[])
{
	// Make sure user enters correct number of arguments
	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./HackAssembler filename\n");
		return 1;
	}

	FILE* openedFile = OpenFile(argv[1]);
	char* fileContents = ReadFile(openedFile);


	for (int i = 0; fileContents[i] != EOF; i++) 
	{
		printf("%c", fileContents[i]);
	
	}

	return 0; 
}
