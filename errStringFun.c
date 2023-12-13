#include "header.h"

/**
 * errPrintStr - Prints an input string.
 * @string: The string to be printed.
 *
 * This function is responsible for printing an input string. It is typically
 * used for error messages or informational messages in the program.
 *
 * Return: Nothing.
 */
void errPrintStr(char *string)
{
	int x = 0;

	/* Check if the input string is NULL */
	if (!string)
		return;
/* Iterate through the characters of the input string */
	while (string[x] != '\0')
	{
		/* Print each character to the standard error stream */
		errPrintChar(string[x]);
		x++;
	}
}

/**
 * errPrintChar - Prints a character to the standard error stream.
 * @ch: The character to be printed.
 *
 * This function manages a static buffer to accumulate characters and flushes
 * the buffer when it reaches a specified size or when a flush character is
 * encountered. It prints characters to the standard error stream.
 *
 * Return: Always returns 1.
 */
int errPrintChar(char ch)
{
	/* Static variables for buffer management */
	static int x;
	static char mybuff[writeBufferSize];

	/* Check for buffer flush condition or buffer size limit */
	if (ch == bufferFlush || x >= writeBufferSize)
	{
	/* Flush the buffer by writing its content to the standard error stream */
		write(2, mybuff, x);
		x = 0;/* Reset buffer index after flushing */
	}
	/* If not a buffer flush character, store the character in the buffer */
	if (ch != bufferFlush)
		mybuff[x++] = ch;
	return (1);/* Always return 1 */
}

/**
 * WFileDescreptor - Writes a character to a file descriptor.
 * @x: The character to be written.
 * @fileDes: The file descriptor to write to.
 *
 * This function manages a static buffer to accumulate characters and flushes
 * the buffer when it reaches a specified size or when a flush character is
 * encountered. It writes characters to the specified file descriptor.
 *
 * Return: Always returns 1.
 */
int WFileDescreptor(char x, int fileDes)
{
	/* Static variables for buffer management */
	static int z;
	static char mybuff[writeBufferSize];

	/* Check for buffer flush condition or buffer size limit */
	if (x == bufferFlush || z >= writeBufferSize)
	{
/*Flush the buffer by writing its content to the specified file descriptor*/
		write(fileDes, mybuff, z);
		z = 0;/* Reset buffer index after flushing */
	}
	 /* If not a buffer flush character, store the character in the buffer */
	if (x != bufferFlush)
		mybuff[z++] = x;
	/* Always return 1 */
	return (1);
}

/**
 * charsCount - Writes characters from a string to a file descriptor
 * and counts them.
 * @string: The string containing characters to be written.
 * @fileDes: The file descriptor to which characters are written.
 *
 * This function iterates through characters of the input string,writes each
 * character to the specified file descriptor using WFileDescreptor, and counts
 * the number of characters written.
 *
 * Return: The total number of characters written.
 */
int charsCount(char *string, int fileDes)
{
	int x = 0;

	 /* Check if the input string is NULL */
	if (!string)
		return (0);
	/* Iterate through the characters of the input string */
	while (*string)
	{
/*Write each character to the specified file descriptor and increment count*/
		x += WFileDescreptor(*string++, fileDes);
	}
	/* Return the total number of characters written */
	return (x);
}
