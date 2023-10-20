typedef struct {
	char *asmCode;
	int binary;
} TranslationMap;

int GetLength(char** array);
int* TranslateASM(char** code);
