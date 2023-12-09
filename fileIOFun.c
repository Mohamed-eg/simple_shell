#include "header.h"

/**
 * getFileHistory - gets the history file
 * @infolist: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getFileHistory(infolist_t *infolist)
{
	char *buffer, *dir;
	/*Get the home directory from environment variables*/
	dir = getEnv(infolist, "HOME=");
	if (!dir)
		return (NULL);
	/*Allocate memory for the buffer to hold the full path*/
	buffer = malloc(sizeof(char) * (getStringLength(dir) + getStringLength(fileHistory) + 2));
	if (!buffer)
		return (NULL);
	/*Initialize the buffer*/
	buffer[0] = 0;
	/*Concatenate "/" to the buffer*/
	copyStrings(buffer, dir);
	/*Concatenate the history file name to the buffer*/
	concatenetStrings(buffer, "/");
	/*Return the constructed full path*/
	concatenetStrings(buffer, fileHistory);
	return (buffer);
}

/**
 * w_history - creates a file, or appends to an existing file
 * @infolist: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int w_history(infolist_t *infolist)
{
	ssize_t fileDes;
	char *filename = getFileHistory(infolist);
	stringlist_t *node = NULL;

	if (!filename)
		return (-1);

	fileDes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fileDes == -1)
		return (-1);
	for (node = infolist->history; node; node = node->next_node)
	{
		charsCount(node->string, fileDes);
		WFileDescreptor('\n', fileDes);
	}
	WFileDescreptor(bufferFlush, fileDes);
	close(fileDes);
	return (1);
}

/**
 * r_history - reads history from file
 * @infolist: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int r_history(infolist_t *infolist)
{
	int i, last = 0, linecount = 0;
	ssize_t fileDes, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = getFileHistory(infolist);

	if (!filename)
		return (0);

	fileDes = open(filename, O_RDONLY);
	free(filename);
	if (fileDes == -1)
		return (0);
	if (!fstat(fileDes, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fileDes, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fileDes);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			buildHistoryList(infolist, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildHistoryList(infolist, buffer + last, linecount++);
	free(buffer);
	infolist->histcount = linecount;
	while (infolist->histcount-- >= maxHistory)
		deletNode(&(infolist->history), 0);
	renumberHistory(infolist);
	return (infolist->histcount);
}

/**
 * buildHistoryList - adds entry to a history linked list
 * @infolist: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(infolist_t *infolist, char *buffer, int linecount)
{
	stringlist_t *node = NULL;

	if (infolist->history)
		node = infolist->history;
	ADDnodeEn(&node, buffer, linecount);

	if (!infolist->history)
		infolist->history = node;
	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @infolist: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberHistory(infolist_t *infolist)
{
	stringlist_t *node = infolist->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next_node;
	}
	return (infolist->histcount = i);
}
