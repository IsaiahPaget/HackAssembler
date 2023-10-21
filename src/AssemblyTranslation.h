typedef struct {
	char* asmCode;
	char* binary;
} TranslationMap;
int GetLengthOfString(char* string);
int GetLength(char** array);
int* TranslateASM(char** code);
char* intToBinary(int n);
