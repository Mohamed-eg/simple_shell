#include "header.h"

/**
 * getFileHistory - Get the full path to the history file.
 * @infolist: Pointer to the infolist structure.
 *
 * This function constructs the full path to the history file based on the
 * user's home directory and the predefined history file name.
 *
 * Return: A pointer to the dynamically allocated string holding the full path
 *         to the history file, or NULL on failure.
 */
char *getFileHistory(infolist_t *infolist)
{
	char *buffer, *directo;
	/*Get the home directory from environment variables*/
	directo = getEnv(infolist, "HOME=");
	if (!directo)
		return (NULL);
	/*Allocate memory for the buffer to hold the full path*/
	buffer = malloc(sizeof(char) * (getStringLength(directo) +
	getStringLength(fileHistory) + 2));
	if (!buffer)
		return (NULL);
	/*Initialize the buffer*/
	buffer[0] = 0;
	/*Concatenate "/" to the buffer*/
	copyStrings(buffer, directo);
	/*Concatenate the history file name to the buffer*/
	concatenetStrings(buffer, "/");
	/*Return the constructed full path*/
	concatenetStrings(buffer, fileHistory);
	return (buffer);
}

/**
 * w_history - Write command history to a file.
 * @infolist: Pointer to the infolist structure.
 *
 * This function writes the command history from the infolist structure to a
 * file specified by the user's home directory and a predefined history file
 * name.
 *
 * Return: 1 on success, -1 on failure.
 */
int w_history(infolist_t *infolist)
{
	ssize_t fileDes;
	char *file_n = getFileHistory(infolist);
	stringlist_t *my_node = NULL;

	 /* If the history file name cannot be obtained, return failure */
	if (!file_n)
		return (-1);

	/* Open the history file for read-write, creating it if necessary */
	fileDes = open(file_n, O_CREAT | O_TRUNC | O_RDWR, 0644);
	/* Free the allocated memory for the history file name */
	free(file_n);
	/* If the file descriptor cannot be obtained, return failure */
	if (fileDes == -1)
		return (-1);
	/* Iterate through the command history and write each entry to the file */
	for (my_node = infolist->my_history; my_node; my_node = my_node->next_node)
	{
		/* Write the command history entry to the file */
		charsCount(my_node->string, fileDes);
		/* Write a newline character to separate entries */
		WFileDescreptor('\n', fileDes);
	}
	/* Flush the file descriptor to ensure data is written */
	WFileDescreptor(bufferFlush, fileDes);
	close(fileDes);/* Close the file descriptor */
	return (1);/* Return success */
}

/**
 * r_history - Read command history from a file and populate the history list.
 * @infolist: Pointer to the infolist structure.
 *
 * This function reads command history from a file specified by the user's home
 * directory and a predefined history file name. It populates the command
 * history list in the infolist structure.
 *
 * Return: The number of history entries read, or 0 on failure.
 */
int r_history(infolist_t *infolist)
{
	int x, end = 0, l_num = 0;
	ssize_t fileDes, read_l, file_s = 0;
	struct stat fileStat;
	char *buffer = NULL, *file_n = getFileHistory(infolist);

	if (!file_n)/*If the history file name cannot be obtained, return failure*/
		return (0);
	fileDes = open(file_n, O_RDONLY);/* Open the history file for reading */
	free(file_n);/* Free the allocated memory for the history file name */
	if (fileDes == -1)/*If the file descriptor cannot be obtained, return fail*/
		return (0);/* Get file information, including file size */
	if (!fstat(fileDes, &fileStat))
		file_s = fileStat.st_size;
	if (file_s < 2)/* If the file size is less than 2, return failure */
		return (0);/*Allocate memory for the buffer to hold the file content*/
	buffer = malloc(sizeof(char) * (file_s + 1));
	if (!buffer)/* If memory allocation fails, return failure */
		return (0);
	read_l = read(fileDes, buffer, file_s);
	buffer[file_s] = 0;/* Null-terminate the buffer */
	if (read_l <= 0)/* If reading fails or no data is read, return failure */
		return (free(buffer), 0);
	close(fileDes);/* Close the file descriptor */
	for (x = 0; x < file_s; x++)/*Parse the buffer and build the history list*/
		if (buffer[x] == '\n')
		{
			buffer[x] = 0;
			buildHistoryList(infolist, buffer + end, l_num++);
			end = x + 1;
		}
	if (end != x)/* If there is leftover data, build one more history entry */
		buildHistoryList(infolist, buffer + end, l_num++);
	free(buffer);/* Free the buffer memory */
	/* Update the number of history entries in the infolist structure */
	infolist->histnum = l_num;
	/* Trim history entries if the count exceeds the maximum allowed */
	while (infolist->histnum-- >= maxHistory)
		deletNode(&(infolist->my_history), 0);
	renumberHistory(infolist);/* Renumber the history entries */
	return (infolist->histnum);/* Return the number of history entries read */
}

/**
 * buildHistoryList - Build and add a history entry to the history list.
 * @infolist: Pointer to the infolist structure.
 * @buffer: Pointer to the buffer containing the history entry.
 * @l_num: Line number associated with the history entry.
 *
 * This function creates a new history entry, adds it to the history list,
 * and updates the infolist structure accordingly.
 *
 * Return: Always returns 0.
 */
int buildHistoryList(infolist_t *infolist, char *buffer, int l_num)
{
	stringlist_t *my_node = NULL;

	/* If the history list is not empty, traverse to the end */
	if (infolist->my_history)
		my_node = infolist->my_history;
    /* Add a new node to the history list with the provided information */
	ADDnodeEn(&my_node, buffer, l_num);

    /* If the history list was initially empty, update infolist pointer */
	if (!infolist->my_history)
		infolist->my_history = my_node;
	return (0);/* Return 0 as specified */
}

/**
 * renumberHistory - Renumber history entries in the infolist structure.
 * @infolist: Pointer to the infolist structure.
 *
 * This function iterates through the history entries in the infolist and
 * renumbers them sequentially.
 *
 * Return: The total number of history entries.
 */
int renumberHistory(infolist_t *infolist)
{
	stringlist_t *my_node = infolist->my_history;
	int x = 0;

    /* Iterate through the history entries and renumber them sequentially */
	while (my_node)
	{
		my_node->number = x++;
		my_node = my_node->next_node;
	}
    /* Iterate through the history entries and renumber them sequentially */
	return (infolist->histnum = x);
}
