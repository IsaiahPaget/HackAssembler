#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "IOHelpers.h"

FILE* OpenFile(char* filePath) 
{
	printf("Initiate OpenFile\n");
	FILE* fptr;
	fptr = fopen(filePath, "rb");

	if (fptr == NULL)
	{
		perror("Error, could not open file\n");
		exit(1);
	}

	return fptr; 
}

char** ReadFile(FILE *file) 
{
	printf("Initiate ReadFile\n");
	
	char **lines = malloc(sizeof(char *) * MORE_LINES);

	size_t total_lines = 0;
	size_t total_chars = 0;

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
		
		// if first character read than allocate space for more characters
		if (total_chars == 0) 
		{
			lines[total_lines] = malloc(MORE_CHARS); 
		}
		
		// assign character to the current spot in array of strings
		lines[total_lines][total_chars] = c;

		// move onto next character
		total_chars++;
		
		// if next line than reallocate new space for the terminator charactor to finish the strings
		if (c == '\n')
		{
			lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
			lines[total_lines][total_chars] = '\0';
			
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

	if (total_chars != 0)
	{
		lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
		lines[total_lines][total_chars] = '\0';
		
		// move onto the next line
		total_lines++;
	}

	lines = realloc(lines, sizeof(char *) * total_lines);

	fclose(file);

	return lines;
}
