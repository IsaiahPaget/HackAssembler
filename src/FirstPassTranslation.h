#include "StringArray.h"
#include "TranslationMap.h"
#define MORE_SYMBOLS 64
void TranslateSymbols(char* address, TranslationMap* symbolsAndVariables, int totalSymbolsAndVariables);
StringArray FindSymbols(StringArray lines);
