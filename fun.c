#include "header.h"

/**
 * IsInteractive - Check if the program is running in an interactive mode.
 * @infolist: Pointer to the infolist_t structure containing information.
 *
 * Return: 1 if interactive, 0 otherwise.
 */
int IsInteractive(infolist_t *infolist)
{
	/* Check if STDIN is associated with a terminal and rfd is within*/
	/* the range of standard descriptors */
	return (isatty(STDIN_FILENO) && infolist->rfd <= 2);
}

/**
 * IsDelimeter - Check if a character is a delimiter.
 * @chr_ch: The character to be checked.
 * @dlmtr_str: The null-terminated string containing delimiter characters.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int IsDelimeter(char chr_ch, char *dlmtr_str)
{
	while (*dlmtr_str)
		if (*dlmtr_str++ == chr_ch)
			return (1);/* Character is a delimiter */
	return (0);/* Character is not a delimiter */
}

/**
 * ISAlphabetic - Check if a character is an alphabetic character.
 * @chr_in: The ASCII value of the character to be checked.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise.
 */
int ISAlphabetic(int chr_in)
{
	if ((chr_in >= 'a' && chr_in <= 'z') || (chr_in >= 'A' && chr_in <= 'Z'))
		return (1);/* Character is alphabetic */
	else
		return (0);/* Character is not alphabetic */
}

/**
 * StrToInt - Convert a string to an integer.
 * @str: Pointer to the string to be converted.
 *
 * Return: The integer value.
 */

int StrToInt(char *str)
{
	int i, my_sign = 1, my_flag = 0, my_output;
	unsigned int result = 0;

	for (i = 0;  str[i] != '\0' && my_flag != 2; i++)
	{
		if (str[i] == '-')
			my_sign *= -1;/* Handle the sign of the number */

		if (str[i] >= '0' && str[i] <= '9')
		{
			my_flag = 1;/* Set the flag to indicate the presence of digits */
			result *= 10;
			result += (str[i] - '0');
		}
/* Stop processing when a non-digit character is encountered after digits */
		else if (my_flag == 1)
			flag = 2;
	}

	if (my_sign == -1)
		my_output = -result;
	else
		my_output = result;

	return (my_output);
}
/*
* for exampl
* char string[] = "-123";
* int result = StrToInt(string);
* printf("Result: %d\n", result);
* the output will be
* Result: -123 as an integer
*/
