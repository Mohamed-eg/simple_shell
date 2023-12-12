#include "header.h"

/**
 * isChain - test if current char in buffer is a chain delimeter
 * @infolist: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int isChain(infolist_t *infolist, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		infolist->cmd_buf_type = orChain;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		infolist->cmd_buf_type = andChain;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		infolist->cmd_buf_type = cmdChain;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkChain - checks we should continue chaining based on last status
 * @infolist: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkChain(infolist_t *infolist, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (infolist->cmd_buf_type == andChain)
	{
		if (infolist->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (infolist->cmd_buf_type == orChain)
	{
		if (!infolist->status)
		{
			buf[i] = 0;
			j = len;
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
		node = nodeStartWith(infolist->alias, infolist->argument_v[0], '=');
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
				duplcatString(convert_number(infolist->status, 10, 0)));
			continue;
		}
		if (!compareStrings(infolist->argument_v[i], "$$"))
		{
			replaStr(&(infolist->argument_v[i]),
				duplcatString(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartWith(infolist->env, &infolist->argument_v[i][1], '=');
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
