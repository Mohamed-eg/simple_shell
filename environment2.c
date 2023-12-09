#include "header.h"

/**
 * our_environ - returns the string array copy of our environ
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **our_environ(infolist_t *infolist)
{
	if (!infolist->environ || infolist->env_changed)
	{
		infolist->environ = listToStrings(infolist->env);
		infolist->env_changed = 0;
	}

	return (infolist->environ);
}

/**
 * remov_environ - Remove an environ variable
 * @infolist: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int remov_environ(infolist_t *infolist, char *var)
{
	stringlist_t *node = infolist->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->string, var);
		if (p && *p == '=')
		{
			infolist->env_changed = deletNode(&(infolist->env), i);
			i = 0;
			node = infolist->env;
			continue;
		}
		node = node->next_node;
		i++;
	}
	return (infolist->env_changed);
}

/**
 * init_env_var - Initialize a new environ variable,
 *             or modify an existing one
 * @infolist: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int init_env_var(infolist_t *infolist, char *var, char *value)
{
	char *buf = NULL;
	stringlist_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(getStringLength(var) + getStringLength(value) + 2);
	if (!buf)
		return (1);
	copyStrings(buf, var);
	concatenetStrings(buf, "=");
	concatenetStrings(buf, value);
	node = infolist->env;
	while (node)
	{
		p = startsWith(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buf;
			infolist->env_changed = 1;
			return (0);
		}
		node = node->next_node;
	}
	ADDnodeEn(&(infolist->env), buf, 0);
	free(buf);
	infolist->env_changed = 1;
	return (0);
}
