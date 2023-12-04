#include "header.h"

/**
 * StringToInteger - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int StringToInteger(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; 
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * PrintError - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void PrintError(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	printDescriptor(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * printDescriptor - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int printDescriptor(int input, int fd)
{
	int (*__putchar)(char) = PutCharacter;
	int i, count = 0;
	unsigned int _abs_, current;

/*
* If the file descriptor is STDERR_FILENO, use _eputchar for error output
*/
	if (fd == STDERR_FILENO)
		__putchar = _eputchar;/*Function pointer for character output*/
/*Handle negative numbers*/
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

/*Loop through powers of 10 to print each digit*/
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

/*If the number is negative and the CONVERT_UNSIGNED flag is not set, adjust the sign*/
	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
/*Set the character array based on the flags for lowercase or uppercase representation*/
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

/*Set the pointer to the end of the buffer*/
	ptr = &buffer[49];
	*ptr = '\0';

/*Convert the number to the specified base and store the result in the buffer*/
	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

/*If the number was negative, add the sign character to the beginning of the buffer*/
	if (sign)
		*--ptr = sign;
/*Return a pointer to the resulting string*/
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
