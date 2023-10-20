#include "AssemblyTranslation.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// A or C instructions
const TranslationMap A_INSTRUCTION = {"@", 0};
const TranslationMap C_INSTRUCTION = {"", 111};

const TranslationMap EQUALS_SIGN = {"=", -1};
const TranslationMap COLON = {";", -1};

// computation instructions
const TranslationMap ZERO = {"0", 0101010};
const TranslationMap ONE = {"1", 0111111};
const TranslationMap MINUS_ONE = {"-1", 0111010};
const TranslationMap D = {"D", 0001100};
const TranslationMap A = {"A", 0110000};
const TranslationMap NOT_D = {"!D", 0001101};
const TranslationMap NOT_A = {"!A", 0110001};
const TranslationMap MINUS_A = {"-A", 0110011};
const TranslationMap MINUS_D = {"-D", 0001111};
const TranslationMap D_PLUS_ONE = {"D+1", 0011111};
const TranslationMap A_PLUS_ONE = {"A+1", 0110001};
const TranslationMap D_MINUS_ONE = {"D-1", 0001110};
const TranslationMap A_MINUS_ONE = {"A-1", 0110010};
const TranslationMap D_PLUS_A = {"D+A", 0000010};
const TranslationMap D_MINUS_A = {"D-A", 0010011};
const TranslationMap A_MINUS_D = {"A-D", 0000111};
const TranslationMap D_AND_A = {"D&A", 0000000};
const TranslationMap D_OR_A = {"D|A", 0010101};

const TranslationMap M = {"M", 1110000};
const TranslationMap NOT_M = {"!M", 1110001};
const TranslationMap MINUS_M = {"-M", 1110011};
const TranslationMap M_PLUS_ONE = {"M+1", 1110111};
const TranslationMap M_MINUS_ONE = {"M-1", 1110010};
const TranslationMap D_PLUS_M = {"D+M", 1000010};
const TranslationMap D_MINUS_M = {"D-M", 1010011};
const TranslationMap M_MINUS_D = {"M-D", 1000111};
const TranslationMap D_AND_M = {"D&M", 1000000};
const TranslationMap D_OR_M = {"D|M", 1010101};

// Destination instruction
const TranslationMap NULL_DESTINATION = {"null", 000};
const TranslationMap M_DESTINATION = {"M", 001};
const TranslationMap D_DESTINATION = {"D", 010};
const TranslationMap MD_DESTINATION = {"DM", 011};
const TranslationMap A_DESTINATION = {"A", 100};
const TranslationMap AM_DESTINATION = {"AM", 101};
const TranslationMap AD_DESTINATION = {"AD", 110};
const TranslationMap AMD_DESTINATION = {"AMD", 111};

// Jump instruction
const TranslationMap NULL_JUMP = {"null", 000};
const TranslationMap GREATER_THAN_JUMP = {"JGT", 001};
const TranslationMap EQUAL_TO_JUMP = {"JEQ", 010};
const TranslationMap GREATER_THAN_OR_EQUAL_TO_JUMP = {"JGE", 011};
const TranslationMap LESS_THAN_JUMP = {"JLT", 100};
const TranslationMap NOT_EQUAL_TO_JUMP = {"JNE", 101};
const TranslationMap LESS_THAN_OR_EQUAL_TO_JUMP = {"JLE", 110};
const TranslationMap JUMP = {"JMP", 111};

int GetLength(char **array)
{
	if (array == NULL)
	{
		printf("Cannot get length: array equals null");
		exit(1);
	}

	int length = 0;

	while(array[length] != NULL)
	{
		length++;
	}
	return length;
}

// functions that translates
int* TranslateASM(char** code) 
{
	if (code == NULL)
	{
		printf("No Code to translate");
		exit(1);
	}
	// int lengthOfCode = GetLength(code);

	// printf("length of code: %d\n", lengthOfCode);

	// int *binary = malloc(sizeof(int) * lengthOfCode);
	
	// if (binary == NULL)
	//{
	//	printf("Could not allocate memory for the binary code");
	//	exit(1);
	//}
	size_t total_lines = 0;

	while (code[total_lines] != NULL)
	{
		printf("%s", code[total_lines]);
		total_lines++;
	}

	return code;
}
