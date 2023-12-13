#include "header.h"

/**
 * our_environ - returns the string array copy of our environ
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **our_environ(infolist_t *infolist)
{
	if (!infolist->environ || infolist->isenvchange)
	{
		infolist->environ = listToStrings(infolist->envir);
		infolist->isenvchange = 0;
	}

	return (infolist->environ);
}

/**
 * remov_environ - Remove an environ variable
 * @infolist: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string envir var property
 */
int remov_environ(infolist_t *infolist, char *var)
{
	stringlist_t *node = infolist->envir;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->string, var);
		if (p && *p == '=')
		{
			infolist->isenvchange = deletNode(&(infolist->envir), i);
			i = 0;
			node = infolist->envir;
			continue;
		}
		node = node->next_node;
		i++;
	}
	return (infolist->isenvchange);
}

/**
 * init_env_var - Initialize a new environ variable,
 *             or modify an existing one
 * @infolist: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string envir var property
 * @value: the string envir var value
 *  Return: Always 0
 */
int init_env_var(infolist_t *infolist, char *var, char *value)
{
	char *mybuff = NULL;
	stringlist_t *node;
	char *p;

	if (!var || !value)
		return (0);

	mybuff = malloc(getStringLength(var) + getStringLength(value) + 2);
	if (!mybuff)
		return (1);
	copyStrings(mybuff, var);
	concatenetStrings(mybuff, "=");
	concatenetStrings(mybuff, value);
	node = infolist->envir;
	while (node)
	{
		p = startsWith(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = mybuff;
			infolist->isenvchange = 1;
			return (0);
		}
		node = node->next_node;
	}
	ADDnodeEn(&(infolist->envir), mybuff, 0);
	free(mybuff);
	infolist->isenvchange = 1;
	return (0);
}
