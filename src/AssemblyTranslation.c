#include "AssemblyTranslation.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "Helpers.h"
#include "TranslationMap.h"


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
const TranslationMap A_PLUS_ONE = {"A+1", "0110111"};
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
const TranslationMap MD_DESTINATION = {"MD", "011"};
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

void PutBinaryInCurrentBinaryInstruction(TranslationMap* translateMap, int lengthOfTranslationMap, char* stringToTranslate, char* currentBinaryInstruction, int indexOfInstruction)
{

	for (int i = 0; i < lengthOfTranslationMap; i++)
	{
		if(strcasecmp(translateMap[i].asmCode, stringToTranslate) == 0)
		{
			for (int j = 0; j < GetLengthOfString(translateMap[i].binary) ; j++)
			{
				currentBinaryInstruction[indexOfInstruction] = translateMap[i].binary[j];
				indexOfInstruction++;
			}
		}
	}
}

void PopulateArrayForTranslation(char** code, char* instruction, int total_lines, int indexToStartParsing, char wherePartOfInstructionEnds)
{
	int indexOfChar = indexToStartParsing;
	int i = 0;
	while (code[total_lines][indexOfChar] != wherePartOfInstructionEnds)
	{
		if(code[total_lines][indexOfChar] == '\0')
			break;
		instruction[i] = code[total_lines][indexOfChar];
		indexOfChar++;
		i++;
	}
	instruction[i] = '\0';
}

void TranslateDestination(int total_lines, char* currentBinaryInstruction, char** code)
{
	int indexOfEquals = indexOfCharacter(code[total_lines], '=');
	if (indexOfEquals < 0)
	{
		return;
	}
	int indexOfDestinationInstruction = 10;
	char destination[GetLengthOfString(code[total_lines])];
	PopulateArrayForTranslation(code, destination, total_lines, 0, '=');

        TranslationMap destinations[] = {
		NULL_DESTINATION, 
		M_DESTINATION,  
		D_DESTINATION,  
		MD_DESTINATION,
		A_DESTINATION,    
		AM_DESTINATION, 
		AD_DESTINATION, 
		AMD_DESTINATION
	};

        int lengthOfTranslationMap = sizeof(destinations) / sizeof(destinations[0]);
        PutBinaryInCurrentBinaryInstruction(destinations, lengthOfTranslationMap, destination, currentBinaryInstruction, indexOfDestinationInstruction);
}

void TranslateCompute(int total_lines, char* currentBinaryInstruction, char** code)
{
	int indexAfterEquals = indexOfCharacter(code[total_lines], '=');
	if (indexAfterEquals < 0)
	{
		indexAfterEquals = 0;
	}
	else 
	{
		indexAfterEquals += 2;	
	}

	int indexOfComputeInstruction = 3;
	char compute[GetLengthOfString(code[total_lines])];
	PopulateArrayForTranslation(code, compute, total_lines, indexAfterEquals, ';');

        TranslationMap computeInstructions[] = {
		ZERO,
		ONE,
		MINUS_ONE,
		D,
		A,
		NOT_D,
          	NOT_A,
          	MINUS_A,
          	MINUS_D,
          	D_PLUS_ONE,
		A_PLUS_ONE,
		D_MINUS_ONE,
		A_MINUS_ONE,
		D_PLUS_A,
		D_MINUS_A,
		A_MINUS_D,
		D_AND_A,
		D_OR_A,
		M,
		NOT_M,
		MINUS_M,
		M_PLUS_ONE,
		M_MINUS_ONE,
		D_PLUS_M,
		D_MINUS_M,
		M_MINUS_D,
		D_AND_M,
		D_OR_M
        };

	int lengthOfTranslationMap = sizeof(computeInstructions) / sizeof(computeInstructions[0]);
	PutBinaryInCurrentBinaryInstruction(computeInstructions, lengthOfTranslationMap, compute, currentBinaryInstruction, indexOfComputeInstruction);
}

void TranslateJump(int total_lines, char* currentBinaryInstruction, char** code)
{
	int indexAfterSemicolon = indexOfCharacter(code[total_lines], ';');
	if (indexAfterSemicolon < 0)
	{
		return;	
	}
	else 
	{
		indexAfterSemicolon += 2;	
	}

	int indexOfJumpInstruction = 13;
	char jump[GetLengthOfString(code[total_lines])];
	PopulateArrayForTranslation(code, jump, total_lines, indexAfterSemicolon, '\0');

	TranslationMap jumpInstructions[] = {
		NULL_JUMP,
		GREATER_THAN_JUMP,
		EQUAL_TO_JUMP,
		GREATER_THAN_OR_EQUAL_TO_JUMP,
		LESS_THAN_JUMP,
		NOT_EQUAL_TO_JUMP,
		LESS_THAN_OR_EQUAL_TO_JUMP,
		JUMP
	};

	int lengthOfTranslationMap = sizeof(jumpInstructions) / sizeof(jumpInstructions[0]);
	PutBinaryInCurrentBinaryInstruction(jumpInstructions, lengthOfTranslationMap, jump, currentBinaryInstruction, indexOfJumpInstruction);
}
void TranslateCInstruction(int total_lines, char* currentBinaryInstruction, char** code)
{
	// to keep track of what part of the currentBinaryInstruction has been already translated
	int indexOfFinishedTranslation = 0;

	// set the first three bits to 111
	for (int i = 0; i < 3; i++)
	{
		currentBinaryInstruction[i] = '1';
		indexOfFinishedTranslation++;
	}

	TranslateDestination(total_lines, currentBinaryInstruction, code);
	TranslateCompute(total_lines, currentBinaryInstruction, code);
	TranslateJump(total_lines, currentBinaryInstruction, code);
}


void TranslateAInstruction(int total_lines, char* currentBinaryInstruction, char** code)
{
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

	/* putting the value into the current instruction
	 * the indexes are at 1 because the A instruction bit is already
	 * at currentBinaryInstruction[0]
	 */
	char binaryAddress[17];
	int newAddress = atoi(address);
	intToBinary(newAddress, binaryAddress);
	int indexInCurrentInstruction = 1;
	for (int i = 1; binaryAddress[i] != '\0'; i++)
	{
		if (indexInCurrentInstruction < 16)
		{
                        currentBinaryInstruction[indexInCurrentInstruction] = binaryAddress[i];
                        indexInCurrentInstruction++;
		}
	}
	currentBinaryInstruction[16] = '\0';
}

// functions that translates
StringArray TranslateASM(char** code) 
{
	if (code == NULL)
	{
		printf("No Code to translate\n");
		exit(1);
	}
	
	int lengthOfCode = GetLength(code);

	char** binary = malloc(sizeof(char*) * lengthOfCode + 1);
	
	if (binary == NULL)
	{
		printf("Could not allocate memory for the binary code\n");
		exit(1);
	}
	
	// looping over all the lines of instruction
	for (int total_lines = 0; total_lines < lengthOfCode; total_lines++)
	{
		char currentBinaryInstruction[] = "0000000000000000";
		
		// only continue if line is NOT empty
		if (code[total_lines][0] != '\0')
		{
			
			// if A or B instruction  
			if(code[total_lines][0] == '@')
			{
				TranslateAInstruction(total_lines, currentBinaryInstruction, code);
			} 
			else if(code[total_lines][0] == '(') 
			{
				strcpy(currentBinaryInstruction, "\0");
			}
			else
			{
				TranslateCInstruction(total_lines, currentBinaryInstruction, code);
			}

			binary[total_lines] = malloc(17 * sizeof(char));
			
			if (binary[total_lines] == NULL)
        		{
        		    printf("Could not allocate memory for binary instruction\n");
        		    exit(1);
        		}

        		strcpy(binary[total_lines], currentBinaryInstruction);
		}
	}

	StringArray result;
	result.pContents = binary;
	result.length = lengthOfCode; 
	
	return result;
}
