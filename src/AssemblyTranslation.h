#include "StringArray.h"
typedef struct {
	char* asmCode;
	char* binary;
} TranslationMap;

typedef struct {
	char terminator;
	char semiColon;
	char equals;
} InstructionBreakKey;

int GetLengthOfString(char* string);
int GetLength(char** array);
StringArray TranslateASM(char** code);
void intToBinary(int n, char* arr);
