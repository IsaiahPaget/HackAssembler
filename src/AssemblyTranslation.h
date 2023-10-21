typedef struct {
	char* asmCode;
	char* binary;
} TranslationMap;

int GetLength(char** array);
int* TranslateASM(char** code);
