#include "header.h"

/**
 * copyStrings - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *copyStrings(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);

/* Copy the characters from src to dest */
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

/*
* at the end of src when src[i]=null the loop end
* and we need to copy the laste null index so we do that
*/
	dest[i] = 0;
	return (dest);
}

/**
 * PutCharacter - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int PutCharacter(char c)
{
	static int i;
	static char buf[writeBufferSize];

	if (c == bufferFlush || i >= writeBufferSize)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != bufferFlush)
		buf[i++] = c;
	return (1);
}

/**
 *Puts - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void Puts(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		PutCharacter(string[i]);
		i++;
	}
}

/**
 * duplcatString - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplcatString(const char *string)
{
	int length = 0;
	char *ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--string;
	return (ret);
}

/**
 * **SplitString - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **SplitString(char *string, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; string[i] != '\0'; i++)
		if (!IsDelimeter(string[i], d) && (IsDelimeter(string[i + 1], d) || !string[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (IsDelimeter(string[i], d))
			i++;
		k = 0;
		while (!IsDelimeter(string[i + k], d) && string[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
