#include "header.h"

/**
 * input_buf - buffers chained commands
 * @infolist: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(infolist_t *infolist, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*freePointers((void **)infolist->cmdBuffer);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, hamdelSigin);
#if useGetLine
		r = getline(buf, &len_p, stdin);
#else
		r = getNextLine(infolist, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			infolist->linenumflag = 1;
			remove_comments(*buf);
			buildHistoryList(infolist, *buf, infolist->histnum++);
			/* if (locateChar(*buf, ';')) is this a command chain? */
			{
				*len = r;
				infolist->cmdBuffer = buf;
			}
		}
	}
	return (r);
}

/**
 * getInput - gets a line minus the newline
 * @infolist: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(infolist_t *infolist)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(infolist->argument), *p;

	PutCharacter(bufferFlush);
	r = input_buf(infolist, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		checkChain(infolist, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (isChain(infolist, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			infolist->cmdBufferTybe = cmdNormal;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (getStringLength(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from getNextLine() */
	return (r); /* return length of buffer from getNextLine() */
}

/**
 * read_buf - reads a buffer
 * @infolist: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(infolist_t *infolist, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(infolist->rfd, buf, readBufferSize);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * getNextLine - gets the next line of input from STDIN
 * @infolist: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int getNextLine(infolist_t *infolist, char **ptr, size_t *length)
{
	static char buf[readBufferSize];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(infolist, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = locateChar(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reAllocat(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		concatenatesStrings(new_p, buf + i, k - i);
	else
		StringCopy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * hamdelSigin - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void hamdelSigin(__attribute__((unused))int sig_num)
{
	Puts("\n");
	Puts("$ ");
	PutCharacter(bufferFlush);
}
