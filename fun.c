#include "header.h"

/**
 * IsInteractive - returns true if shell is IsInteractive mode
 * @infolist: struct address
 *
 * Return: 1 if IsInteractive mode, 0 otherwise
 */
int IsInteractive(infolist_t *infolist)
{
	return (isatty(STDIN_FILENO) && infolist->rfd <= 2);
}

/**
 * IsDelimeter - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int IsDelimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *ISAlphabetic - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int ISAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *StrToInt - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, otherwise converted number
 *to it is valeo
 */

int StrToInt(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
/*
* for exampl
* char string[] = "-123";
* int result = StrToInt(string);
* printf("Result: %d\n", result);
* the output will be
* Result: -123 as an integer
*/
