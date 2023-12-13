#include "header.h"

/**
 * StringToInteger - Convert error string to an integer.
 * @str: Pointer to the string to be converted.
 *
 * Return: The integer value, or -1 if conversion fails.
 */
int StringToInteger(char *str)
{
	int x = 0;
	unsigned long int rest = 0;

	/* Skip leading '+' if present */
	if (*str == '+')
		str++;
	/* Iterate through the string characters */
	for (x = 0;  str[x] != '\0'; x++)
	{
		/* Check if the character is a digit */
		if (str[x] >= '0' && str[x] <= '9')
		{
			rest *= 10;
			rest += (str[x] - '0');
			/* Check for integer overflow */
			if (rest > INT_MAX)/* constant defined in the <limits.h>*/
				return (-1);
		}
		else/* Non-digit character found, return -1 for failure */
			return (-1);
	}
	return (rest);
}

/**
 * PrintError - Print an error message to standard error.
 * @infolist: Pointer to the infolist_t structure containing information.
 * @emst: Pointer to the error message string.
 * Return: 0 if no number in string
 *        -1 if there is an error
 */
void PrintError(infolist_t *infolist, char *emst)
{
/* Print the filename, error line number, program name, and error message */
	errPrintStr(infolist->filename);
	errPrintStr(": ");
	printDescriptor(infolist->err_line_num, STDERR_FILENO);
	errPrintStr(": ");
	errPrintStr(infolist->argument_v[0]);
	errPrintStr(": ");
	errPrintStr(emst);
}

/**
 * printDescriptor - Print an integer to a specified file descriptor.
 * @int_put: The integer to be printed.
 * @fileDes: The file descriptor to which the integer is printed.
 *
 * Return: number of characters that has been printed.
 */
int printDescriptor(int int_put, int fileDes)
{
	int (*put_chr)(char) = PutCharacter;
	int iter, num = 0;
	unsigned int ABS, curdir;

/*
* If the file descriptor is STDERR_FILENO, use errPrintChar for error output
*/
	if (fileDes == STDERR_FILENO)
		put_chr = errPrintChar;/*Function pointer for character output*/
/*Handle negative numbers*/
	if (int_put < 0)
	{
		ABS = -int_put;
		put_chr('-');
		num++;
	}
	else
		ABS = int_put;
	curdir = ABS;

/*Loop through powers of 10 to print each digit*/
	for (iter = 1000000000; iter > 1; iter /= 10)
	{
		if (ABS / iter)
		{
			put_chr('0' + curdir / iter);
			num++;
		}
		curdir %= iter;
	}
	put_chr('0' + curdir);
	num++;

	return (num);
}

/**
 * convert_number - converter function, a clone of itoa
 * @number: number
 * @my_base: my_base
 * @my_flags: argument my_flags
 *
 * Return: string
 */
char *convert_number(long int number, int my_base, int my_flags)
{
	static char buf[50];
	static char *my_array;
	char *pointr;
	char num_sign = 0;
	unsigned long nu = number;

/*
* If the number is negative and the unsignedConverter
* flag is not set, adjust the num_sign
*/
	if (!(my_flags & unsignedConverter) && number < 0)
	{
		nu = -number;
		num_sign = '-';

	}
/*
* Set the character my_array based on the
* my_flags for lowercase or uppercase representation
*/
my_array = (my_flags & lowerCaseConverter) ?
			"0123456789abcdef" : "0123456789ABCDEF";

/*Set the pointer to the end of the buf*/
	pointr = &buf[49];
	*pointr = '\0';

/*Convert the number to the specified my_base and store the result in the buf*/
	do	{
		*--pointr = my_array[nu % my_base];
		nu /= my_base;
	} while (nu != 0);

/*
* If the number was negative,
* the num_sign character to the beginning of the buf
*/
	if (num_sign)
		*--pointr = num_sign;
/*Return a pointer to the resulting string*/
	return (pointr);
}

/**
 * re_comm - Remove comments from a string by replacing characters after '#'
 *            with null characters.
 * @mybuff: Pointer to the string to be processed.
 *
 * Return: Always 0;
 */
void re_comm(char *mybuff)
{
	int x;

	for (x = 0; mybuff[x] != '\0'; x++)
		if (mybuff[x] == '#' && (!x || mybuff[x - 1] == ' '))
		{/* Replace characters after '#' with null characters */
			mybuff[x] = '\0';
			break;/* Stop processing after the first '#' is encountered */
		}
}
