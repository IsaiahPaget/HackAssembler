#include "AssemblyTranslation.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// A or C instructions
const TranslationMap C_INSTRUCTION = {"", "111"};

// computation instructions
const TranslationMap ZERO = {"0", "0101010"};
const TranslationMap ONE = {"1", "0111111"};
const TranslationMap MINUS_ONE = {"-1", "0111010"};
const TranslationMap D = {"D", "0001100"};
const TranslationMap A = {"A", "0110000"};
const TranslationMap NOT_D = {"!D", "0001101"};
const TranslationMap NOT_A = {"!A", "0110001"};
const TranslationMap MINUS_A = {"-A", "0110011"};
const TranslationMap MINUS_D = {"-D", "0001111"};
const TranslationMap D_PLUS_ONE = {"D+1", "0011111"};
const TranslationMap A_PLUS_ONE = {"A+1", "0110001"};
const TranslationMap D_MINUS_ONE = {"D-1", "0001110"};
const TranslationMap A_MINUS_ONE = {"A-1", "0110010"};
const TranslationMap D_PLUS_A = {"D+A", "0000010"};
const TranslationMap D_MINUS_A = {"D-A", "0010011"};
const TranslationMap A_MINUS_D = {"A-D", "0000111"};
const TranslationMap D_AND_A = {"D&A", "0000000"};
const TranslationMap D_OR_A = {"D|A", "0010101"};

const TranslationMap M = {"M", "1110000"};
const TranslationMap NOT_M = {"!M", "1110001"};
const TranslationMap MINUS_M = {"-M", "1110011"};
const TranslationMap M_PLUS_ONE = {"M+1", "1110111"};
const TranslationMap M_MINUS_ONE = {"M-1", "1110010"};
const TranslationMap D_PLUS_M = {"D+M", "1000010"};
const TranslationMap D_MINUS_M = {"D-M", "1010011"};
const TranslationMap M_MINUS_D = {"M-D", "1000111"};
const TranslationMap D_AND_M = {"D&M", "1000000"};
const TranslationMap D_OR_M = {"D|M", "1010101"};

// Destination instruction
const TranslationMap NULL_DESTINATION = {"null", "000"};
const TranslationMap M_DESTINATION = {"M", "001"};
const TranslationMap D_DESTINATION = {"D", "010"};
const TranslationMap MD_DESTINATION = {"DM", "011"};
const TranslationMap A_DESTINATION = {"A", "100"};
const TranslationMap AM_DESTINATION = {"AM", "101"};
const TranslationMap AD_DESTINATION = {"AD", "110"};
const TranslationMap AMD_DESTINATION = {"AMD", "111"};

// Jump instruction
const TranslationMap NULL_JUMP = {"null", "000"};
const TranslationMap GREATER_THAN_JUMP = {"JGT", "001"};
const TranslationMap EQUAL_TO_JUMP = {"JEQ", "010"};
const TranslationMap GREATER_THAN_OR_EQUAL_TO_JUMP = {"JGE", "011"};
const TranslationMap LESS_THAN_JUMP = {"JLT", "100"};
const TranslationMap NOT_EQUAL_TO_JUMP = {"JNE", "101"};
const TranslationMap LESS_THAN_OR_EQUAL_TO_JUMP = {"JLE", "110"};
const TranslationMap JUMP = {"JMP", "111"};



char* intToBinary(int n) {
	char* binary = malloc(16 * sizeof(char));
    	if (binary == NULL)
	{
		printf("Could not allocate memory to turn intToBinary code\n");
		exit(1);
	}
    	int i = 0;
    	for (int bit = 1 << 14; bit > 0; bit = bit / 2) {
    	    if ((n & bit) != 0) {
    	        binary[i] = '1';
    	    } else {
    	        binary[i] = '0';
    	    }
    	    i++;
    	}
    	binary[i] = '\0';
	
	i = 1;
	while (binary[i] == '0')
	{
		i++;
	}
	int lengthOfBinary = 16 - (i + 1);
	
	for (int indexOfBinary = 15; indexOfBinary == 16 - lengthOfBinary; indexOfBinary--)
	{
		// TODO		
	}

    	return binary;
}


int GetLengthOfString(char* string)
{
	int length = 0;
	if (string != NULL)
	{
		while (string[length] != '\0')
		{
			length++;
		}
	}
	return length;
}
int GetLength(char **array)
{
	if (array == NULL)
	{
		printf("Cannot get length: array equals null\n");
		exit(1);
	}

	int length = 0;

	while(*array[length] != EOF)
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
		printf("No Code to translate\n");
		exit(1);
	}
	
	int lengthOfCode = GetLength(code);

	printf("length of code: %d\n", lengthOfCode);

	int *binary = malloc(sizeof(int) * lengthOfCode);
	
	if (binary == NULL)
	{
		printf("Could not allocate memory for the binary code\n");
		exit(1);
	}
	
	// looping over all the lines of instruction
	for (int total_lines = 0; total_lines < lengthOfCode; total_lines++)
	{
		char currentBinaryInstruction[16];
		
		// only continue if line is NOT empty
		if (code[total_lines][0] != '\0')
		{
			printf("%s\n", code[total_lines]);
			
			// if A or B instruction  
			if(code[total_lines][0] == '@')
			{
				printf("A instruction\n");

				// move a instruction flag into the first part of the binary instruction
				currentBinaryInstruction[0] = '0';

				// get a buffer for the integer that is after the @
				char address[GetLengthOfString(code[total_lines]) - 1];
				int indexOfChar	= 1;
				
				// move the value into the buffer
				while (code[total_lines][indexOfChar] != '\0')
				{
					address[indexOfChar - 1] = code[total_lines][indexOfChar]; 	
					indexOfChar++;
				}
				address[indexOfChar - 1] = '\0';

				int newAddress = atoi(address);

				char* binaryAddress = intToBinary(newAddress);
				
				indexOfChar = 0;
				int indexOfBinaryInstruction = 1;

				while(binaryAddress[indexOfChar] != '\0')
				{
					if (indexOfBinaryInstruction > 15)
					{
						printf("Error A instruction too large\n");
						exit(1);
					}
					printf("%c\n",binaryAddress[indexOfChar]);
					currentBinaryInstruction[indexOfBinaryInstruction] = binaryAddress[indexOfChar];
					indexOfChar++;
					indexOfBinaryInstruction++;
				}
				printf("%s\n", currentBinaryInstruction);
			} else 
			{
				printf("C instruction\n");
			}
		}
	}
	
	return binary;
}
