#include <stdio.h>

#define MORE_LINES 1024
#define MORE_CHARS 1024
// reads files into an array of strings
// get size by checking for EOF
/*
* While not EOF size++ return size
*/ 
char** ReadFile(FILE *file);
FILE* OpenFile(char *filePath);
int indexOfCharacter(char* string, char character);
