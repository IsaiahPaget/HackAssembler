#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "StringArray.h"
#include "TranslationMap.h"
#include <string.h>
#include <strings.h>
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

void MakeMoreRoomForSymbols(TranslationMap* labels, int totalLabels)
{
	size_t new_size = totalLabels + MORE_SYMBOLS;
	labels = realloc(labels, sizeof(TranslationMap *) * new_size);
	if (labels == NULL) 
	{
		printf("Could not allocate more memory for LabelsAndVariables\n");
		exit(1);
	}
}
void TranslateSymbols(StringArray code, TranslationMap* labels, int totalLabels, TranslationMap* variables, int totalVariables)
{
	for (int currentLine = 0; currentLine < code.length; currentLine++)
	{
		char* address = code.pContents[currentLine] + 1;

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

		for (int i = 0; i < lengthOfTranslationMap; i++)
		{
			if (strcasecmp(address, symbols[i].asmCode) == 0)
			{
				strcpy(address, symbols[i].binary);
			}
			else 
			{
				for (int j = 0; j < totalLabels; j++)
				{
					if (strcasecmp(address, labels[j].asmCode) == 0)
					{
						strcpy(address, labels[j].binary);
					}
					else 
					{
						for (int k = 0; k < totalVariables; k++)
						{
							if (strcasecmp(address, variables[k].asmCode) == 0)
							{
								strcpy(address, variables[k].binary);
							}
						}
					}
				}
			}
		}
	}
}

bool isAlreadyDefined(char label[], TranslationMap* labels, int totalLabels)
{
	for (int indexOfLabel = 0; indexOfLabel < totalLabels; indexOfLabel++)
	{
		if (strcasecmp(label, labels[indexOfLabel].asmCode) == 0)
		{
			return true;
		}
	}
	return false;
}

int FindVariables(StringArray lines, TranslationMap* variables, TranslationMap* labels, int totalLabels, int total_variables)
{
	int lineVariableIsAt = 16;
	int totalVariables = total_variables;
	
	for (int i = 0; i < lines.length; i++)
	{	
		char label[16] = {0};
		if (lines.pContents[i][0] == '@')
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

				bool isSymbol = isAlreadyDefined(label, symbols, lengthOfTranslationMap);
				if (!isSymbol)
				{
					bool isLabel = isAlreadyDefined(label, labels, totalLabels);
					if (!isLabel)
					{
						bool isAlreadyVariable = isAlreadyDefined(label, variables, totalVariables);
						if (!isAlreadyVariable)
						{
							char number[8];
							sprintf(number, "%d", lineVariableIsAt);

							lineVariableIsAt++;

							strcpy(variables[totalVariables].asmCode, label); 
							strcpy(variables[totalVariables].binary, number);

							totalVariables++;

							if (totalVariables % MORE_SYMBOLS == 0)
							{
								MakeMoreRoomForSymbols(variables, totalVariables);
							}
						}
					}
				}
			}
		}
	}
	return totalVariables;
}


int FindLabels(StringArray lines, TranslationMap* labels, int total_labels)
{
	int totalLabels = total_labels;
	int amountToDecreaseByForLabels = 0;
	int indexOfAfterOpenParan = 1;
	int indexOfClosedParan;
	for (int i = 0; i < lines.length; i++)
	{
		char label[16] = {0};
		if (lines.pContents[i][0] == '(')
		{
			for (int j = 0; j < strlen(lines.pContents[i]); j++)
			{
				if (lines.pContents[i][j] == ')')
				{
					indexOfClosedParan = j;
				}
			}
			strncpy(label, lines.pContents[i] + indexOfAfterOpenParan, indexOfClosedParan - indexOfAfterOpenParan);
			label[indexOfClosedParan - indexOfAfterOpenParan] = '\0';
			
			char number[8] = {0};
			sprintf(number, "%d", i - amountToDecreaseByForLabels);

			labels[totalLabels].asmCode[0] = '\0';
			labels[totalLabels].binary[0] = '\0';

			strcpy(labels[totalLabels].binary, number);
			strcpy(labels[totalLabels].asmCode, label); 

			amountToDecreaseByForLabels++;
			totalLabels++;

			if (totalLabels % MORE_SYMBOLS == 0)
			{
				MakeMoreRoomForSymbols(labels, totalLabels);
			}
		}
	}
	return totalLabels;
}

StringArray FindSymbols(StringArray lines)
{
	TranslationMap* labels = malloc(sizeof(TranslationMap) * MORE_SYMBOLS);
	TranslationMap* variables = malloc(sizeof(TranslationMap) * MORE_SYMBOLS);
	
	int totalLabels = 0;
	int totalVariables = 0;

	totalLabels = FindLabels(lines, labels, totalLabels);
	totalVariables = FindVariables(lines, variables, labels, totalLabels, totalVariables);

	TranslateSymbols(lines, labels, totalLabels, variables, totalVariables);

	StringArray result;
	result.pContents = lines.pContents;
	result.length = lines.length;

	free(labels);
	free(variables);
	return result;
}
