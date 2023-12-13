#include "header.h"

/**
 * my_env - prints all the current environ
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(infolist_t *infolist)
{
	printListString(infolist->envir);
	return (0);
}

/**
 * getEnv - gets the value of an environ variable
 * @infolist: Structure containing potential arguments. Used to maintain
 * @var_name: envir var var_name
 *
 * Return: the value
 */
char *getEnv(infolist_t *infolist, const char *var_name)
{
	stringlist_t *node = infolist->envir;
	char *p;

	while (node)
	{
		p = startsWith(node->string, var_name);
		if (p && *p)
			return (p);
		node = node->next_node;
	}
	return (NULL);
}

/**
 * mySetEnv - Initialize a new environ variable,
 *             or modify an existing one
 * @infolist: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int mySetEnv(infolist_t *infolist)
{
	if (infolist->argument_c != 3)/*3=the minmam number of argu*/
	{
		errPrintStr("the number of arguements is not 3\n");
		return (1);
	}
	if (init_env_var(infolist, infolist->argument_v[1], infolist->argument_v[2]))
		return (0);
	return (1);
}

/**
 * unSetEnv - Remove an environ variable
 * @infolist: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unSetEnv(infolist_t *infolist)
{
	int i;

	if (infolist->argument_c == 1)
	{
		errPrintStr("you but just one argument.\n");
		return (1);
	}
	for (i = 1; i <= infolist->argument_c; i++)
		remov_environ(infolist, infolist->argument_v[i]);

	return (0);
}

/**
 * populateEnvList - populates envir linked list
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populateEnvList(infolist_t *infolist)
{
	stringlist_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		ADDnodeEn(&node, environ[i], 0);
	infolist->envir = node;
	return (0);
}
