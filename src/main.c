#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "IOHelpers.h"
#include "AssemblyTranslation.h"

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
	
	int* code = TranslateASM(fileContents);

	int sizeOfArry = GetLength(fileContents);

	// free all the dynamically made memory
	for (size_t i = 0; i < sizeOfArry; i++)
	{
		free(fileContents[i]);
	}
	free(fileContents);
	free(code);

	return 0; 
}
