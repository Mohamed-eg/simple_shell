#include "header.h"

/**
 * isCMD - Checks if the specified path corresponds to a regular file.
 * @infolist: Unused parameter.
 * @str_path: The path to check.
 *
 * Return:
 * - 1 if the path corresponds to a regular file.
 * - 0 otherwise or if str_path is NULL.
 */
int isCMD(infolist_t *infolist, char *str_path)
{
	struct stat fileStat;

	/*Unused parameter*/
	(void)infolist;
	/* Check if str_path is NULL or if stat fails*/
	if (!str_path || stat(str_path, &fileStat))
		return (0);

	/*Check if the path corresponds to a regular file*/
	if (fileStat.st_mode & S_IFREG)/*S_IFREG: Regular file*/
	{
		/*file is a regular file.*/
		return (1);
	}
	/*file is not a regular file.*/
	return (0);
}

/**
 * duplCharacters - Extracts a substring from patheString.
 * @patheString: The input string.
 * @startIndex: The starting index of the substring.
 * @stopIndex: The stopping index (exclusive) of the substring.
 *
 * Return: A pointer to the extracted substring. The substring is stored in a
 * static buffer, so it is not safe for concurrent use.
 */
char *duplCharacters(char *patheString, int startIndex, int stopIndex)
{
	static char staBuff[1024];
	int y = 0, x = 0;

	/*Iterate from start to stop (exclusive)*/
	for (x = 0, y = startIndex; y < stopIndex; y++)
		/*Exclude ':' characters*/
		if (patheString[y] != ':')
			staBuff[x++] = patheString[y];
	/*Null-terminate the extracted substring*/
	staBuff[x] = 0;
	/*Return a pointer to the extracted substring*/
	return (staBuff);
}

/**
 * findPath - Searches for a command in a colon-separated list of directories.
 * @infolist: Unused parameter.
 * @patheString: The colon-separated list of directories.
 * @CMD: The command to search for.
 *
 * Return: A pointer to the full path of the command if found, or NULL otherwise.
 */
char *findPath(infolist_t *infolist, char *patheString, char *CMD)
{
	int x = 0, currentPos = 0;
	char *str_path;

	/* Check if patheString is NULL*/
	if (!patheString)
		return (NULL);

	/*Check if CMD starts with "./" and is a valid command*/
	if ((getStringLength(CMD) > 2) && startsWith(CMD, "./"))
	{
		if (isCMD(infolist, CMD))
			return (CMD);
	}

	/*Loop through the patheString*/
	while (1)
	{
		/*Check for end of string or colon separator*/
		if (!patheString[x] || patheString[x] == ':')
		{
			/*Extract the directory path from patheString*/
			str_path = duplCharacters(patheString, currentPos, x);
			/*If str_path is empty, concatenate CMD directly*/
			if (!*str_path)
				concatenetStrings(str_path, CMD);
			else
			{
				/*Concatenate str_path, "/", and CMD*/
				concatenetStrings(str_path, "/");
				concatenetStrings(str_path, CMD);
			}
			/*Check if the concatenated path is a valid command*/
			if (isCMD(infolist, str_path))
				return (str_path);
			/*Break if end of string is reached*/
			if (!patheString[x])
				break;
			/*Update currentPos for the next directory*/
			currentPos = x;
		}
		/*Move to the next character*/
		x++;
	}
	return (NULL);/*Return NULL if the command is not found in any directory*/
}
