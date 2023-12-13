#include "header.h"

/**
 * concatenatesStrings - Concatenates two strings up to a
 * specified number of bytes.
 * @str_one: The destination string to which the other string is concatenated.
 * @str_two: The source string to be concatenated.
 * @byt_num: The maximum number of bytes to concatenate from str_two.
 *
 * Return: A pointer to the concatenated string (str_one).If str_one is NULL or
 *         memory allocation fails, returns NULL.
 *
 * Note: The caller is responsible for freeing any allocated memory.
 */
char *concatenatesStrings(char *str_one, char *str_two, int byt_num)
{
	int x, y;
	char *x = str_one;
	/* Check for NULL pointers*/
	if (str_one == NULL && str_two == NULL)
		return (NULL);

	x = 0;
	y = 0;
	/*Find the end of str_one*/
	while (str_one[x] != '\0')
		x++;
	/*Concatenate str_two to str_one, up to byt_num bytes*/
	while (str_two[y] != '\0' && y < byt_num)
	{
		str_one[x] = str_two[y];
		x++;
		y++;
	}
	/*Null-terminate the concatenated string*/
	if (y < byt_num)
		str_one[x] = '\0';
	/*Return the pointer to the concatenated string*/
	return (x);
}

/**
 **locateChar - locates a character in a string
 *@x: string that we look in
 *@t: character we are looking for [target]
 *Return: x a pointer to the character
 */
char *locateChar(char *x, char t)
{
	/*loop in x to find the tardet t and retarn a pointer to it in x*/
	do {
		if (*x == t)
			return (x);
	} while (*x++ != '\0');
	/*if you don't find any thing return null*/
	return (NULL);
}

/**
 * SplitString2 - Splits a string into an array of substrings
 * based on a delimiter.
 * @string: The input string to be split.
 * @delimiter: The delimiter character used to separate substrings.
 *
 * Return: A dynamically allocated array of strings (char **), with the last
 *         element set to NULL. Returns NULL if the input string is empty or if
 *         memory allocation fails.
 *
 * Note: The caller is responsible for freeing the allocated memory.
 */
char **SplitString2(char *string, char delimiter)
{
	int x, y, z, l, n = 0;
	char **s;
	/*Check for empty string*/
	if (string == NULL || string[0] == 0)
		return (NULL);
	/*Count the number of substrings*/
	for (x = 0; string[x] != '\0'; x++)
		if ((string[x] != delimiter && string[x + 1] == delimiter) ||
		    (string[x] != delimiter && !string[x + 1]) || string[x + 1] == delimiter)
			n++;
	if (n == 0)/*Return NULL if no substrings found*/
		return (NULL);
	/*Allocate memory for the array of strings*/
	s = malloc((1 + n) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < n; y++)
	{/* Skip leading delimiters*/
		while (string[x] == delimiter && string[x] != delimiter)
			x++;
		z = 0;
		/*Count characters until the next delimiter or end of string*/
		while (string[x + z] != delimiter && string[x + z] &&
		string[x + z] != delimiter)
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)/*Free allocated memory on failure*/
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < z; l++)/*Copy substring to allocated memory*/
			s[y][l] = string[x++];
		s[y][l] = 0;/*Null-terminate the substring*/
	}
	s[y] = NULL;/*Set the last element of the array to NULL*/
	return (s);
}
