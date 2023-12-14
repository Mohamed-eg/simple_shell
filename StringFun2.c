#include "header.h"

/**
 * copyStrings - Copies a string from source to destination.
 * @destina: The destination string.
 * @source: The source string.
 *
 * Return: A pointer to the destination string.
 *
 * Note: If destination and source are the same or if source is NULL, the
 * function returns the original destination string.
 */
char *copyStrings(char *destina, char *source)
{
	int i = 0;

	if (destina == source || source == 0)
		return (destina);

/* Copy the characters from source to destina */
	while (source[i])
	{
		destina[i] = source[i];
		i++;
	}

/*
* at the end of src when src[i]=null the loop end
* and we need to copy the laste null index so we do that
*/
	destina[i] = 0;
	return (destina);
}

/**
 * PutCharacter - Buffers and writes a character to the standard output.
 * @x: The character to be buffered and written.
 *
 * Return: 1 on success.
 */
int PutCharacter(char x)
{
	/*Define a static buffer and its size*/
	static int i;
	static char mybuff[writeBufferSize];

	/*Check if the character is the flush trigger or the buffer is full*/
	if (x == bufferFlush || i >= writeBufferSize)
	{
	/*Flush the buffer to the standard output*/
		write(1, mybuff, i);
	/*Reset the buffer index*/
		i = 0;
	}
	/*Buffer the character if it is not the flush trigger*/
	if (x != bufferFlush)
		mybuff[i++] = x;
	/*Indicate success*/
	return (1);
}

/**
 *Puts - Writes a string to the standard output.
 *@string: The string to be written.
 * Return: Nothing
 * Note: you must build PutCharacter() fun befor
 */
void Puts(char *string)
{
	int i = 0;

	/*Check if the input string is NULL*/
	if (!string)
		return;
	/*Iterate through the string and call PutCharacter for each character*/
	while (string[i] != '\0')
	{
		PutCharacter(string[i]);
		i++;
	}
}

/**
 * duplcatString - Duplicates a string and reverses its characters.
 * @string: The input string to be duplicated and reversed.
 * Return: A pointer to the duplicated and reversed string.
 *         Returns NULL if the input is NULL or if memory allocation fails.
 * Note: The caller is responsible for freeing the allocated memory.
 * you need to include <stdlib.h> for malloc
 */
char *duplcatString(const char *string)
{
	int length = 0;
	char *ret;

	/*Check if the input string is NULL*/
	if (string == NULL)
		return (NULL);
	/*Calculate the length of the input string*/
	while (*string++)
		length++;
	/*Allocate memory for the reversed string*/
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	/*Copy and reverse the characters*/
	for (length++; length--;)
		ret[length] = *--string;
	return (ret);
}

/**
 * SplitString - splits a string into array of substrings based on delimiters.
 * IsDelimiter - Checks if a character is a delimiter.
 * @string: the input string to be split.
 * @deli: the delimeter string
 * Return: A dynamically allocated array of strings (char **),
 * where each element represents a substring. The last element is set to NULL
 * Returns NULL if the input string is empty or if memory allocation fails.
 * Note: The caller is responsible for freeing the allocated memory.
 */

char **SplitString(char *string, char *deli)
{
	int x, y, z, l, n = 0;
	char **s;

	if (string == NULL || string[0] == 0)/*Check for empty string*/
		return (NULL);
	/*If delimiters are not provided, use a space as the default delimiter*/
	if (!deli)
		deli = " ";
	/*Count the number of words based on delimiters*/
	for (x = 0; string[x] != '\0'; x++)
		if (!IsDelimeter(string[x], deli) &&
		(IsDelimeter(string[x + 1], deli) || !string[x + 1]))
			n++;
	if (n == 0)/* Return NULL if no words found*/
		return (NULL);/*Allocate memory for the array of strings*/
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < n; y++)
	{	/*Skip leading delimiters*/
		while (IsDelimeter(string[x], deli))
			x++;
		z = 0;/*Count characters until the next delimiter or end of string*/
		while (!IsDelimeter(string[x + z], deli) && string[x + z])
			z++;/*Allocate memory for the substring*/
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{	/*Free allocated memory on failure*/
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < z; l++)/*Copy substring to allocated memory*/
			s[y][l] = string[x++];
		s[y][l] = 0;
	}
	s[y] = NULL;/*Set the last element of the array to NULL*/
	return (s);/*Return the array of substrings*/
}
