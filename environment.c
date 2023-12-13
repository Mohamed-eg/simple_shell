#include "header.h"

/**
 * my_env - Displays the current environment variables.
 * @infolist: Pointer to the infolist structure.
 *
 * This function prints the names and values of the current env variables
 * stored in the linked list (infolist->envir).
 *
 * Return: Always returns 0.
 */
int my_env(infolist_t *infolist)
{
	/* Print the list of environment variables */
	printListString(infolist->envir);
	return (0);/* Always return 0 */
}

/**
 * getEnv - Retrieves the value of a specified environment variable.
 * @infolist: Pointer to the infolist structure.
 * @var_name: The name of the environment variable to retrieve.
 *
 * This function searches for the specified environment variable (var_name) in
 * the linked list of environment var (infolist->envir) and returns its value
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *getEnv(infolist_t *infolist, const char *var_name)
{
	stringlist_t *my_node = infolist->envir;
	char *ptr;

	/* Traverse the linked list of environment variables */
	while (my_node)
	{
		/* Check if the current environment variable matches specified name*/
		ptr = startsWith(my_node->string, var_name);
		if (ptr && *ptr)
			return (ptr);
		/* Move to the next node in the linked list */
		my_node = my_node->next_node;
	}
	/* Return NULL if the environment variable is not found */
	return (NULL);
}

/**
 * mySetEnv - Sets or updates the value of an environment variable.
 * @infolist: Pointer to the infolist structure.
 *
 * This function sets or updates the value of an env variable by calling
 * the init_env_var function with the provided arguments.
 *
 * Return: 1 on success, 0 on incorrect number of arguments
 * or memory allocation failure.
 */
int mySetEnv(infolist_t *infolist)
{
	/* Check if the number of arguments is incorrect */
	if (infolist->argument_c != 3)/*3=the minmam number of argu*/
	{
		errPrintStr("The number of arguements is not ok\n");
		return (1);
	}
	/* Call init_env_var to set or update the environment variable */
	if (init_env_var(infolist, infolist->argument_v[1],
	infolist->argument_v[2]))
		return (0);
	return (1);
}

/**
 * unSetEnv - Removes specified environment variables.
 * @infolist: Pointer to the infolist structure.
 *
 * This function removes specified environment variables by calling the
 * remov_environ function with the provided arguments.
 *
 * Return: 0 on success, 1 on incorrect number of arguments.
 */
int unSetEnv(infolist_t *infolist)
{
	int x;

	/* Check if the number of arguments is incorrect */
	if (infolist->argument_c == 1)
	{
		errPrintStr("you but just one argument.\n");
		return (1);
	}
/*Loop through the provided arguments and remove corresponding env variables*/
	for (x = 1; x <= infolist->argument_c; x++)
		remov_environ(infolist, infolist->argument_v[x]);

	return (0);
}

/**
 * populateEnvList - Populates the linked list of environment variables.
 * @infolist: Pointer to the infolist structure.
 *
 * This function populates the linked list of env variables (infolist->envir)
 * with values from the external 'environ' array.
 *
 * Return: Always returns 0.
 */
int populateEnvList(infolist_t *infolist)
{
	stringlist_t *my_node = NULL;
	size_t x;

	/*Loop through the 'environ' array and add each env variable to the list*/
	for (x = 0; environ[x]; x++)
		ADDnodeEn(&my_node, environ[x], 0);
	/*Set the environment variable list in the infolist structure*/
	infolist->envir = my_node;
	/* Always return 0 */
	return (0);
}
