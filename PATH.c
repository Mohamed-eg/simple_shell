#include "header.h"

/**
 * isCMD - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCMD(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplCharacters - duplicates characters
 * @patheString: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplCharacters(char *patheString, int start, int stop)
{
	static char buf[1024];
	int i = 0, x = 0;

	for (x = 0, i = start; i < stop; i++)
		if (patheString[i] != ':')
			buf[x++] = patheString[i];
	buf[x] = 0;
	return (buf);
}

/**
 * findPath - finds this CMD in the PATH string
 * @info: the info struct
 * @patheString: the PATH string
 * @CMD: the CMD to find
 *
 * Return: full path of CMD if found or NULL
 */
char *findPath(info_t *info, char *patheString, char *CMD)
{
	int i = 0, currentPos = 0;
	char *path;

	if (!patheString)
		return (NULL);
	if ((getStringLength(CMD) > 2) && startsWith(CMD, "./"))
	{
		if (isCMD(info, CMD))
			return (CMD);
	}
	while (1)
	{
		if (!patheString[i] || patheString[i] == ':')
		{
			path = duplCharacters(patheString, currentPos, i);
			if (!*path)
				concatenetStrings(path, CMD);
			else
			{
				concatenetStrings(path, "/");
				concatenetStrings(path, CMD);
			}
			if (isCMD(info, path))
				return (path);
			if (!patheString[i])
				break;
			currentPos = i;
		}
		i++;
	}
	return (NULL);
}
