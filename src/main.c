#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "IOHelpers.h"
#include "AssemblyTranslation.h"
#include "StringArray.h"
#include "Helpers.h"
#include "FirstPassTranslation.h"

int main(int argc, char *argv[])
{

	// Make sure user enters correct number of arguments
	if (argc != 2)
	{
		fprintf(stderr, "Usage: ./HackAssembler filename\n");
		return 1;
	}

	FILE* openedFile = OpenFile(argv[1]);

	StringArray fileContents = ReadFile(openedFile);

	StringArray arr = FindSymbols(fileContents);
	
	StringArray code = TranslateASM(fileContents.pContents);

	FILE* createdFile = CreateFile(argv[1]);
	WriteFile(createdFile, code);

	fclose(createdFile);

	int sizeOfArry = fileContents.length;

	// free all the dynamically made memory
	for (size_t i = 0; i < sizeOfArry; i++)
	{
		free(fileContents.pContents[i]);
		free(code.pContents[i]);
	}
	free(fileContents.pContents);
	free(code.pContents);

	printf("Finished\n");

	return 0; 
}
