#include "header.h"

/**
 * inputBuffer - Read a line of input into a buffer.
 * @infolist: Pointer to the infolist_t structure containing information.
 * @mybuff: Pointer to the buffer where the input line is stored.
 * @mylen: Pointer to the size of the buffer.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t inputBuffer(infolist_t *infolist, char **mybuff, size_t *mylen)
{
	ssize_t x = 0;
	size_t p_lenth = 0;

	if (!*mylen)
	{
		/*freePointers((void **)infolist->cmdBuffer);*/
		free(*mybuff);
		*mybuff = NULL;/* Set up a signal handler for SIGINT */
		signal(SIGINT, hamdelSigin);/*come form <signal.h>*/
#if useGetLine/* Read input line using getline or getNextLine */
		x = getline(mybuff, &p_lenth, stdin);/*from <stdio>*/
#else/*getline() is used to read a line of text from stdin*/
		x = getNextLine(infolist, mybuff, &p_lenth);
#endif
		if (x > 0)
		{/* Remove trailing newline if present */
			if ((*mybuff)[x - 1] == '\n')
			{
				(*mybuff)[x - 1] = '\0';
				x--;
			}
			infolist->linenumflag = 1;
			re_comm(*mybuff);
			buildHistoryList(infolist, *mybuff, infolist->histnum++);
			{
				*mylen = x;
				infolist->cmdBuffer = mybuff;
			}
		}
	}
	return (x);
}

/**
 * getInput - Get input from the user and process command chains.
 * @infolist: Pointer to the infolist_t structure containing information.
 *
 * Return: The bufsize of the current command, or -1 on EOF.
 */
ssize_t getInput(infolist_t *infolist)
{
	static char *mybuff;
	static size_t iter, y, mylen;
	ssize_t x = 0;
	char **p_beff = &(infolist->argument), *p;

	PutCharacter(bufferFlush);
	x = inputBuffer(infolist, &mybuff, &mylen);
	if (x == -1)
		return (-1);
	if (mylen)
	{
		y = iter;
		p = mybuff + iter;

		/* Check for command chain and update iterators */
		checkChain(infolist, mybuff, &y, iter, mylen);
		while (y < mylen)
		{
			if (isChain(infolist, mybuff, &y))
				break;
			y++;
		}

		iter = y + 1;
		if (iter >= mylen)
		{
			iter = mylen = 0;
			infolist->cmdBufferTybe = cmdNormal;
		}

		*p_beff = p;
		return (getStringLength(p));
	}

	*p_beff = mybuff;
	return (x);
}

/**
 * readBuffer - Read data from a file descriptor into a buffer.
 * @infolist: Pointer to the infolist_t structure containing information.
 * @mybuff: Pointer to the buffer where data will be stored.
 * @iter: Pointer to the current position in the buffer.
 *
 * Return: The number of bytes read, or -1 on error.
 */
ssize_t readBuffer(infolist_t *infolist, char *mybuff, size_t *iter)
{
	ssize_t x = 0;

/* If the current position is not at the beginning of the buffer, return 0 */
	if (*iter)
		return (0);/* Read data from the file descriptor into the buffer */
	x = read(infolist->rfd, mybuff, readBufferSize);
/* If data was read successfully, update the current position */
	if (x >= 0)
		*iter = x;
	return (x);
}

/**
 * getNextLine - Read the next line from a file descriptor into a buffer.
 * @infolist: Pointer to the infolist_t structure containing information.
 * @stoline: Pointer to the buffer where the line will be stored.
 * @bufsize: Pointer to the size of the buffer.
 *
 * Return: The number of characters read, or -1 on error or EOF.
 */
int getNextLine(infolist_t *infolist, char **stoline, size_t *bufsize)
{
	static char mybuff[readBufferSize];
	static size_t iter, mylen;
	size_t z;
	ssize_t x = 0, st = 0;
	char *ptr = NULL, *newPtr = NULL, *chr;

	ptr = *stoline;
	/* If the buffer and bufsize are provided, store the current bufsize */
	if (ptr && bufsize)
		st = *bufsize;
	/* Reset indices if the buffer is fully processed */
	if (iter == mylen)
		iter = mylen = 0;

	x = readBuffer(infolist, mybuff, &mylen);/* Read data into the buffer */
	if (x == -1 || (x == 0 && mylen == 0))/* Check for read errors or EOF */
		return (-1);

	/* Find the next newline character in the buffer */
	chr = locateChar(mybuff + iter, '\n');
	z = chr ? 1 + (unsigned int)(chr - mybuff) : mylen;
	/* Reallocate memory for the buffer */
	newPtr = reAllocat(ptr, st, st ? st + z : z + 1);
	if (!newPtr) /* Handle memory allocation failure */
		return (ptr ? free(ptr), -1 : -1);

	if (st)/* Concatenate the new data to the buffer */
		concatenatesStrings(newPtr, mybuff + iter, z - iter);
	else
		StringCopy(newPtr, mybuff + iter, z - iter + 1);
	st += z - iter;
	iter = z;
	ptr = newPtr;

	if (bufsize)/* Update the bufsize and buffer pointers */
		*bufsize = st;
	*stoline = ptr;
	return (st);
}

/**
 * hamdelSigin - Signal handler for SIGINT (Ctrl+C).
 * @sig_num: The signal number (unused).
 *
 * Return: void
 */
void hamdelSigin(__attribute__((unused))int sig_num)
{
	Puts("\n");/* Print a newline character */
	Puts("$ ");/* Print the shell prompt */
	PutCharacter(bufferFlush);/* Flush the output buffer */

}
