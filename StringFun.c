#include "header.h"

/**
 * getStringLength - Calculates the length of a string.
 * @str_ch: The input string.
 *
 * Return: The length of the string. Returns 0 if the string is NULL.
 */
int getStringLength(char *str_ch)
{
	int length = 0;
	/*Check if the input string is NULL*/
	if (!str_ch)
		return (0);
	/*Iterate through the string until the null terminator is encountered*/
	while (*str_ch++)
		length++;
	return (length);
}

/**
 * compareStrings - Compares two strings lexicographically.
 * @strone: The first string to compare.
 * @strtwo: The second string to compare.
 *
 * Return:
 * - 0 if the strings are equal.
 * - A negative value if strone is less than strtwo.
 * - A positive value if strone is greater than strtwo.
 */
int compareStrings(char *strone, char *strtwo)
{
	/*Iterate through both strings*/
	while (*strone && *strtwo)
	{
		/*Compare characters at the current position*/
		if (*strone != *strtwo)
			return (*strone - *strtwo);
		/*Move to the next character in both strings*/
		strone++;
		strtwo++;
	}
	/*Check if both strings are equal*/
	if (*strone == *strtwo)
		return (0);
	else/*Return -1 if s1 is less, 1 if s1 is greater*/
		return (*strone < *strtwo ? -1 : 1);
}

/**
 * startsWith - Checks if a string starts with a given prefix.
 * @check_str: The string to check if it starts with the prefix.
 * @prefix_in: The prefix to check for at the beginning of the check_str.
 *
 * Return:
 * - A pointer to the remaining part of the check_str if it starts
 * with the prefix.
 * - NULL if the check_str does not start with the prefix.
 */
char *startsWith(const char *check_str, const char *prefix_in)
{
	/*Iterate through the characters in the prefix*/
	while (*prefix_in)
		/*Compare characters at the current position*/
		if (*prefix_in++ != *check_str++)
			return (NULL);/*Return NULL if the characters do not match*/
	/*Return a pointer to the remaining part of check_str*/
	return ((char *)check_str);
}

/**
 * concatenetStrings - Concatenates two strings.
 * @destination: The destination string.
 * @source: The source string to be concatenated to the destination.
 *
 * Return: A pointer to the concatenated string (destination).
 */
char *concatenetStrings(char *destination, char *source)
{
	char *res = destination;

/* Move destination pointer to the end of the destination string*/
	while (*destination)
		destination++;

/* Copy characters from source to destination */
	while (*source)
		*destination++ = *source++;

	*destination = *source;
/*
* After the loops, the null from source is
* copieing to the end of the concatenated string
*/
	return (res);
}

/**
 * StringCopy - Copies at most max_char characters from source to destination.
 * @destination: The destination string.
 * @source: The source string to be copied.
 * @max_char: The maximum number of characters to copy.
 *
 * Return: A pointer to the destination string.
 */
char *StringCopy(char *destination, char *source, int max_char)
{
	int x, y;
	char *str_ch = destination;

	x = 0;
	/*Copy at most n-1 characters from source to destination*/
	while (source[x] != '\0' && x < max_char - 1)
	{
		destination[x] = source[x];
		x++;
	}
	/*If i is less than n, fill the remaining characters with null*/
	if (x < max_char)
	{
		y = x;
		while (y < max_char)
		{
			destination[y] = '\0';
			y++;
		}
	}
	return (str_ch);
}
