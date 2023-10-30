#include <stdio.h>
#include "StringArray.h"
#define MORE_LINES 1024
#define MORE_CHARS 1024

// reads files into an array of strings
// get size by checking for EOF
/*
* While not EOF size++ return size
*/ 
StringArray ReadFile(FILE *file);
FILE* OpenFile(char *filePath);
FILE* CreateFile(char *filePath);
void WriteFile(FILE* file, StringArray code);
int indexOfCharacter(char* string, char character);
