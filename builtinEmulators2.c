#include "header.h"

/**
 * historyEmulator - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @infolist: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int historyEmulator(infolist_t *infolist)
{
	elementList(infolist->my_history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @infolist: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(infolist_t *infolist, char *string)
{
	char *p, c;
	int ret;

	p = locateChar(string, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deletNode(&(infolist->my_alias),
		nodeIndex(infolist->my_alias, nodeStartWith(infolist->my_alias, string, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @infolist: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(infolist_t *infolist, char *string)
{
	char *p;

	p = locateChar(string, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(infolist, string));

	unset_alias(infolist, string);
	return (ADDnodeEn(&(infolist->my_alias), string, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(stringlist_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = locateChar(node->string, '=');
		for (a = node->string; a <= p; a++)
			PutCharacter(*a);
		PutCharacter('\'');
		Puts(p + 1);
		Puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * aliasEmulator - mimics the alias Builtin_Comands (man alias)
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int aliasEmulator(infolist_t *infolist)
{
	int i = 0;
	char *p = NULL;
	stringlist_t *node = NULL;

	if (infolist->argument_c == 1)
	{
		node = infolist->my_alias;
		while (node)
		{
			print_alias(node);
			node = node->next_node;
		}
		return (0);
	}
	for (i = 1; infolist->argument_v[i]; i++)
	{
		p = locateChar(infolist->argument_v[i], '=');
		if (p)
			set_alias(infolist, infolist->argument_v[i]);
		else
			print_alias(nodeStartWith(infolist->my_alias, infolist->argument_v[i], '='));
	}

	return (0);
}
