#include "header.h"

/**
 *errPrintStr - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void errPrintStr(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		errPrintChar(string[i]);
		i++;
	}
}

/**
 * errPrintChar - writes the character c to stander error
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, return -1, and errno is set acording to errno stander.
 */
int errPrintChar(char c)
{
	static int i;
	static char buf[writeBufferSize];

	if (c == bufferFlush || i >= writeBufferSize)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != bufferFlush)
		buf[i++] = c;
	return (1);
}

/**
 * WFileDescreptor - writes the character c to given fileDes
 * @x: The character to print
 * @fileDes: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, return -1, and errno is set acording to errno stander.
 */
int WFileDescreptor(char x, int fileDes)
{
	static int z;
	static char buf[writeBufferSize];

	if (x == bufferFlush || z >= writeBufferSize)
	{
		write(fileDes, buf, z);
		z = 0;
	}
	if (x != bufferFlush)
		buf[z++] = x;
	return (1);
}

/**
 *charsCount - prints an input string
 * @string: the string to be printed
 * @fileDes: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int charsCount(char *string, int fileDes)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += WFileDescreptor(*string++, fileDes);
	}
	return (i);
}
