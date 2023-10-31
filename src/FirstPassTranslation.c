#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "StringArray.h"
#include "TranslationMap.h"
#include <string.h>
#include "FirstPassTranslation.h"

// predefined values
const TranslationMap R0 = {"R0", "0"};
const TranslationMap R1 = {"R1", "1"};
const TranslationMap R2 = {"R2", "2"};
const TranslationMap R3 = {"R3", "3"};
const TranslationMap R4 = {"R4", "4"};
const TranslationMap R5 = {"R5", "5"};
const TranslationMap R6 = {"R6", "6"};
const TranslationMap R7 = {"R7", "7"};
const TranslationMap R8 = {"R8", "8"};
const TranslationMap R9 = {"R9", "9"};
const TranslationMap R10 = {"R10", "10"};
const TranslationMap R11 = {"R11", "11"};
const TranslationMap R12 = {"R12", "12"};
const TranslationMap R13 = {"R13", "13"};
const TranslationMap R14 = {"R14", "14"};
const TranslationMap R15 = {"R15", "15"};
const TranslationMap SCREEN = {"SCREEN", "16384"};
const TranslationMap KBD = {"KBD", "24576"};
const TranslationMap SP = {"SP", "0"};
const TranslationMap LCL = {"LCL", "1"};
const TranslationMap ARG = {"ARG", "2"};
const TranslationMap THIS = {"THIS", "3"};
const TranslationMap THAT = {"THAT", "4"};

void TranslateSymbols(int total_lines, char* address)
{
	int line_number = total_lines;
	
	TranslationMap symbols[] = {
		R0,
		R1,
		R2,
		R3,
		R4,
		R5,
		R6,
		R7,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
		SCREEN,
		KBD,
		SP,
		LCL,
		ARG,
		THIS,
		THAT,
	};

	int lengthOfTranslationMap = sizeof(symbols) / sizeof(symbols[0]);
	int amountOfTimesTheLoopHasLooped;
	for (int i = 0; i < lengthOfTranslationMap; i++)
	{
		if (strcasecmp(address, symbols[i].asmCode) == 0)
		{
			strcpy(address, symbols[i].binary);
		}
		amountOfTimesTheLoopHasLooped = i;
	}
	printf("translateSymbols %s\n", address);
}

StringArray FindSymbols(StringArray lines)
{
	TranslationMap* LabelsAndVariables = malloc(sizeof(TranslationMap) * MORE_SYMBOLS);
	
	int totalLabels = 0;
	int indexOfAfterOpenParan = 1;
	int lineLabelIsAt;
	int indexOfClosedParan;
	for (int i = 0; i < lines.length; i++)
	{
		char label[16] = {0};
		if (lines.pContents[i][0] == '(')
		{
			lineLabelIsAt = i;
			for (int j = 0; j < strlen(lines.pContents[i]); j++)
			{
				if (lines.pContents[i][j] == ')')
				{
					indexOfClosedParan = j;
				}
			}
			strncpy(label, lines.pContents[i] + indexOfAfterOpenParan, indexOfClosedParan - indexOfAfterOpenParan);
			label[indexOfClosedParan - indexOfAfterOpenParan] = '\0';
			
			char number[8];
			sprintf(number, "%d", lineLabelIsAt + 1);

			strcpy(LabelsAndVariables[totalLabels].asmCode, label); 
			LabelsAndVariables[totalLabels].binary = number;

			totalLabels++;

			if (totalLabels % MORE_SYMBOLS == 0)
			{
				size_t new_size = totalLabels + MORE_SYMBOLS;
				LabelsAndVariables = realloc(LabelsAndVariables, sizeof(TranslationMap *) * new_size);
			}
		}
		else if (lines.pContents[i][0] == '@')
		{
			char charAfterAt = lines.pContents[i][1];
			if (isalpha(charAfterAt) != 0)
			{
				strcpy(label, lines.pContents[i] + 1);
				TranslationMap symbols[] = {
					R0,
					R1,
					R2,
					R3,
					R4,
					R5,
					R6,
					R7,
					R8,
					R9,
					R10,
					R11,
					R12,
					R13,
					R14,
					R15,
					SCREEN,
					KBD,
					SP,
					LCL,
					ARG,
					THIS,
					THAT,
				};

				int lengthOfTranslationMap = sizeof(symbols) / sizeof(symbols[0]);
				for (int indexOfsymbol = 0; indexOfsymbol < lengthOfTranslationMap; indexOfsymbol++)
				{
					// check if string is in symbols or a label else add more variables
				}
			}
		}
	}

	for (int i = 0; i < totalLabels; i++)
	{
		printf("labels and variables: asm %s binary %s\n",LabelsAndVariables[i].asmCode, LabelsAndVariables[i].binary);
	}

	StringArray result;
	result.pContents = lines.pContents;
	result.length = lines.length;
	return result;
}
