#include <stdio.h>
#include <stdlib.h>

int indexOfCharacter(char* string, char character)
{
	int index;
	for (int i = 0; string[i] != character; i++)
	{
		if (i > 50)
		{
			printf("invalid code length\n");
			exit(1);
		}
		if (string[i] == '\0')
		{
			index = -1;
			return index;
		}
		index = i;
	}
	return index;	
}

void intToBinary(int n, char* binary) 
{

    	if (binary == NULL)
	{
		printf("Could not allocate memory to turn intToBinary code\n");
		exit(1);
	}
	
	// putting the binary representation into a string that looks like this 0000100101010101
    	int i = 0;
    	for (int bit = 1 << 15; bit > 0; bit = bit / 2) {
		if (i > 16)
		{
			printf("Error A instruction too large\n");
			exit(1);
		}
		if ((n & bit) != 0) 
		{
			binary[i] = '1';
		} else 
		{
			binary[i] = '0';
		}
		i++;
    	}
    	binary[i] = '\0';
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
	while(array[length][0] != EOF)
	{
		length++;
	}
	return length;
}

