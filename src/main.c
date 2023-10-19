#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "IOHelpers.h"

int main(int argc, char *argv[])
{
	// Make sure user enters correct number of arguments
	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./HackAssembler filename\n");
		return 1;
	}

	FILE* openedFile = OpenFile(argv[1]);
	char** fileContents = ReadFile(openedFile);



	for (int i = 0; *fileContents[i] != EOF; i++) 
	{
		printf("%s", fileContents[i]);
	}
	
	size_t sizeOfArry = sizeof(fileContents) / sizeof(fileContents[0]);

	// free all the dynamically made memory
	for (size_t i = 0; i < sizeOfArry; i++)
	{
		free(fileContents[i]);
	}
	free(fileContents);

	return 0; 
}
