#include "header.h"

/**
 * our_environ - Retrieves or updates the environment variable list.
 * @infolist: Pointer to the infolist structure.
 *
 * This function returns the current environment variable list if it exists.
 * If the environment has changed, it updates the environment variable list
 * based on the contents of infolist->envir.
 *
 * Return: The environment variable list.
 */
char **our_environ(infolist_t *infolist)
{
	/* Check if the environment variable list is not present or needs update*/
	if (!infolist->environ || infolist->isenvchange)
	{
		/* Convert the linked list of environment variables to a string array*/
		infolist->environ = listToStrings(infolist->envir);
		/* Reset the environment change flag */
		infolist->isenvchange = 0;
	}
	/* Return the environment variable list */
	return (infolist->environ);
}

/**
 * remov_environ - Removes environment variables matching a specified prefix.
 * @infolist: Pointer to the infolist structure.
 * @var_prop: The prefix of the environment variables to be removed.
 *
 * This function removes environment variables whose names start with the
 * specified prefix (var_prop) from the linked list of environment
 * variables (infolist->envir).
 * Return: 1 if any environment variable is removed, 0 otherwise.
 */
int remov_environ(infolist_t *infolist, char *var_prop)
{
	stringlist_t *my_node = infolist->envir;
	size_t x = 0;
	char *ptr;

	/* Check if the environment variable list or the specified prefix is NULL*/
	if (!my_node || !var_prop)
		return (0);

		/* Iterate through the linked list of environment variables */
	while (my_node)
	{
	/* Check if the environment variable starts with the specified prefix*/
		ptr = startsWith(my_node->string, var_prop);
		if (ptr && *ptr == '=')
		{
			/* Remove the environment variable and update the change flag */
			infolist->isenvchange = deletNode(&(infolist->envir), x);
			/* Reset the index and start over from the beginning of the list*/
			x = 0;
			my_node = infolist->envir;
			continue;
		}
		/* Move to the next node in the linked list */
		my_node = my_node->next_node;
		x++;
	}
/*Return the environment change flag indicating if any variable was removed*/
	return (infolist->isenvchange);
}

/**
 * init_env_var - Initializes or updates an environment variable.
 * @infolist: Pointer to the infolist structure.
 * @var_prop: The name of the environment variable.
 * @var_value: The value to be assigned to the environment variable.
 *
 * This function initializes or updates an environment variable in the linked
 * listof environment variables (infolist->envir). If the variable already
 * exists, its value is updated; otherwise a new variable is added to the list
 *
 * Return: 0 on success, 1 on memory allocation failure.
 */
int init_env_var(infolist_t *infolist, char *var_prop, char *var_value)
{
	char *ptr;
	char *mybuff = NULL;
	stringlist_t *my_node;

	/* Check if the variable name or value is NULL */
	if (!var_prop || !var_value)
		return (0);

	/* Allocate memory for the environment variable string */
	mybuff = malloc(getStringLength(var_prop) + getStringLength(var_value) + 2);
	if (!mybuff)
		return (1);
	/* Construct the environment variable string: name=value */
	copyStrings(mybuff, var_prop);
	concatenetStrings(mybuff, "=");
	concatenetStrings(mybuff, var_value);
	/* Traverse the linked list of environment variables */
	my_node = infolist->envir;
	while (my_node)
	{
		/* Check if the environment variable already exists */
		ptr = startsWith(my_node->string, var_prop);
		if (ptr && *ptr == '=')
		{
			/* Update the existing environment variable */
			free(my_node->string);
			my_node->string = mybuff;
			infolist->isenvchange = 1;
			return (0);
		}
		/* Move to the next node in the linked list */
		my_node = my_node->next_node;
	}
	/* Add a new environment variable to the linked list */
	ADDnodeEn(&(infolist->envir), mybuff, 0);
	free(mybuff);
	infolist->isenvchange = 1;
	return (0);
}
