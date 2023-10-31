#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "IOHelpers.h"
#include "Helpers.h"
#include "AssemblyTranslation.h"
#include "StringArray.h"

FILE* OpenFile(char* filePath) 
{
	FILE* fptr;
	fptr = fopen(filePath, "rb");

	if (fptr == NULL)
	{
		perror("Error, could not open file\n");
		exit(1);
	}

	return fptr; 
}

FILE* CreateFile(char* filePath) 
{
	int index = indexOfCharacter(filePath, '.');

	if (index < 1)
	{
		printf("Usage ./HackAssembler example.asm");
		exit(1);
	}

	filePath[index + 1] = '\0';

	FILE* fptr;
	fptr = fopen(strcat(filePath, ".hack"), "a");

	if (fptr == NULL)
	{
		perror("Error, could not open file\n");
		exit(1);
	}

	return fptr; 
}

void WriteFile(FILE* file, StringArray code)
{
	for (int i = 0; i < code.length; i++)
	{
		fprintf(file, "%s\n", code.pContents[i]);
	}
}

StringArray ReadFile(FILE *file) 
{
	char **lines = malloc(sizeof(char *) * MORE_LINES);

	size_t total_lines = 0;
	size_t total_chars = 0;
	bool isCommentMode = false;

	char c;
	
	while (!feof(file))
	{
		if (ferror(file))
		{
			printf("Error reading from file\n");
			exit(1);
		}

		// get first character of file
		c = fgetc(file);
			
		if (c == '/')
		{
			isCommentMode = true;
		} 
		if (c == '\n' && isCommentMode)
		{
			isCommentMode = false;
		}

		if ( !(c == '\n' && total_chars == 0) && !isCommentMode)
		{
				// if first character read than allocate space for more characters
				if (total_chars == 0) 
				{
					lines[total_lines] = malloc(MORE_CHARS); 
				}
				if (c != ' ' || c != '	')
				{
					// assign character to the current spot in array of strings
					lines[total_lines][total_chars] = c;
	
					// move onto next characterl
					total_chars++;
				}
				
				// if next line than reallocate new space for the terminator charactor to finish the strings
				if (c == '\n')
				{

					// replace new line with terminator
					lines[total_lines][total_chars - 1] = '\0';
					
					// move onto the next line
					total_lines++;
					total_chars = 0;

					// if need more lines than add reallocate MORE_LINES
					if (total_lines % MORE_LINES == 0)
					{
						size_t new_size = total_lines + MORE_LINES;
						lines = realloc(lines, sizeof(char *) * new_size);
					}
				}
				else if (total_chars % MORE_CHARS == 0) 
				{
					size_t new_size = total_chars + MORE_CHARS;
					lines[total_lines] = realloc(lines[total_lines],new_size);
				}
		}
	}

	if (total_chars != 0)
	{
		lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
		lines[total_lines][total_chars] = '\0';
		
		total_lines++;
	}

	lines = realloc(lines, sizeof(char *) * total_lines);

	fclose(file);

	StringArray result;
	result.pContents = lines;
	result.length = total_lines;

	return result;
}
