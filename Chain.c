#include "header.h"

/**
 * isChain - test if current char in buffer is a chain delimeter
 * @infolist: the parameter struct
 * @mybuff: the char buffer
 * @p: address of current position in mybuff
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int isChain(infolist_t *infolist, char *mybuff, size_t *p)
{
	size_t j = *p;

	if (mybuff[j] == '|' && mybuff[j + 1] == '|')
	{
		mybuff[j] = 0;
		j++;
		infolist->cmdBufferTybe = orChain;
	}
	else if (mybuff[j] == '&' && mybuff[j + 1] == '&')
	{
		mybuff[j] = 0;
		j++;
		infolist->cmdBufferTybe = andChain;
	}
	else if (mybuff[j] == ';') /* found end of this command */
	{
		mybuff[j] = 0; /* replace semicolon with null */
		infolist->cmdBufferTybe = cmdChain;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkChain - checks we should continue chaining based on last status
 * @infolist: the parameter struct
 * @mybuff: the char buffer
 * @p: address of current position in mybuff
 * @i: starting position in mybuff
 * @mylen: length of mybuff
 *
 * Return: Void
 */
void checkChain(infolist_t *infolist, char *mybuff, size_t *p, size_t i,
size_t mylen)
{
	size_t j = *p;

	if (infolist->cmdBufferTybe == andChain)
	{
		if (infolist->my_status)
		{
			mybuff[i] = 0;
			j = mylen;
		}
	}
	if (infolist->cmdBufferTybe == orChain)
	{
		if (!infolist->my_status)
		{
			mybuff[i] = 0;
			j = mylen;
		}
	}

	*p = j;
}

/**
 * replaceAlies - replaces an aliases in the tokenized string
 * @infolist: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaceAlies(infolist_t *infolist)
{
	int i;
	stringlist_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartWith(infolist->my_alias, infolist->argument_v[0], '=');
		if (!node)
			return (0);
		free(infolist->argument_v[0]);
		p = locateChar(node->string, '=');
		if (!p)
			return (0);
		p = duplcatString(p + 1);
		if (!p)
			return (0);
		infolist->argument_v[0] = p;
	}
	return (1);
}

/**
 * replaVars - replaces vars in the tokenized string
 * @infolist: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaVars(infolist_t *infolist)
{
	int i = 0;
	stringlist_t *node;

	for (i = 0; infolist->argument_v[i]; i++)
	{
		if (infolist->argument_v[i][0] != '$' || !infolist->argument_v[i][1])
			continue;

		if (!compareStrings(infolist->argument_v[i], "$?"))
		{
			replaStr(&(infolist->argument_v[i]),
				duplcatString(convert_number(infolist->my_status, 10, 0)));
			continue;
		}
		if (!compareStrings(infolist->argument_v[i], "$$"))
		{
			replaStr(&(infolist->argument_v[i]),
				duplcatString(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartWith(infolist->envir, &infolist->argument_v[i][1], '=');
		if (node)
		{
			replaStr(&(infolist->argument_v[i]),
				duplcatString(locateChar(node->string, '=') + 1));
			continue;
		}
		replaStr(&infolist->argument_v[i], duplcatString(""));

	}
	return (0);
}

/**
 * replaStr - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replaStr(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
