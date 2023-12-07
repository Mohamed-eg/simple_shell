#include "header.h"

/**
 * isCMD - determines if a file is an executable command
 * @infolist: the infolist struct
 * @str_path: str_path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isCMD(infolist_t *infolist, char *str_path)
{
	struct stat st;

	(void)infolist;
	if (!str_path || stat(str_path, &st))
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
 * @infolist: the infolist struct
 * @patheString: the PATH string
 * @CMD: the CMD to find
 *
 * Return: full str_path of CMD if found or NULL
 */
char *findPath(infolist_t *infolist, char *patheString, char *CMD)
{
	int i = 0, currentPos = 0;
	char *str_path;

	if (!patheString)
		return (NULL);
	if ((getStringLength(CMD) > 2) && startsWith(CMD, "./"))
	{
		if (isCMD(infolist, CMD))
			return (CMD);
	}
	while (1)
	{
		if (!patheString[i] || patheString[i] == ':')
		{
			str_path = duplCharacters(patheString, currentPos, i);
			if (!*str_path)
				concatenetStrings(str_path, CMD);
			else
			{
				concatenetStrings(str_path, "/");
				concatenetStrings(str_path, CMD);
			}
			if (isCMD(infolist, str_path))
				return (str_path);
			if (!patheString[i])
				break;
			currentPos = i;
		}
		i++;
	}
	return (NULL);
}
