#include "StringArray.h"
#include "TranslationMap.h"
#define MORE_SYMBOLS 64
void TranslateSymbols(StringArray code, TranslationMap* labels, int totalLabels, TranslationMap* variables, int totalVariables);
StringArray FindSymbols(StringArray lines);
