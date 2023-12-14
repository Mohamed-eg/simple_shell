#include "header.h"

/**
 * historyEmulator - Displays the command history.
 * @infolist: Pointer to the infolist structure.
 *
 * This function displays the command history stored in the infolist structure.
 * It prints each command along with its corresponding line number.
 *
 * Return: Always returns 0.
 */
int historyEmulator(infolist_t *infolist)
{
	/* Call the elementList function to display the command history */
	elementList(infolist->my_history);
	 /* Always return 0 */
	return (0);
}

/**
 * removeAlias - Removes an alias from the alias list.
 * @infolist: Pointer to the infolist structure.
 * @string: The alias to be removed.
 *
 * This function removes the specified alias from the alias list stored
 * in the infolist structure. The alias is identified by its name, and the
 * function updates the alias list accordingly.
 *
 * Return: 1 on success, 0 on failure.
 */
int removeAlias(infolist_t *infolist, char *string)
{
	int restr;
	char *ptr, chr;

	/* Locate the position of the '=' character in the alias */
	ptr = locateChar(string, '=');
	if (!ptr)
		return (1);
	/* Temporarily replace '=' with null character to extract the alias name*/
	chr = *ptr;
	*ptr = 0;
	/* Remove the alias by calling the deletNode function */
	restr = deletNode(&(infolist->my_alias),
		nodeIndex(infolist->my_alias,
		nodeStartWith(infolist->my_alias, string, -1)));
	/* Restore the original character at the '=' position */
	*ptr = chr;
	/* Return 1 on success, 0 on failure */
	return (restr);
}

/**
 * defineAlias - Defines or updates an alias in the alias list.
 * @infolist: Pointer to the infolist structure.
 * @string: The alias definition string.
 *
 * This function defines or updates an alias in the alias list stored
 * in the infolist structure. If the alias already exists, it is updated;
 * otherwise, a new alias is added to the list.
 *
 * Return: 1 on success, 0 on failure.
 */
int defineAlias(infolist_t *infolist, char *string)
{
	char *ptr;

	/* Locate the position of the '=' character in the alias definition */
	ptr = locateChar(string, '=');
	if (!ptr)
		return (1);
	/* Check if the alias definition string is empty after '=' */
	if (!*++ptr)
		return (removeAlias(infolist, string));

	/* Remove the existing alias and add the new one to the list */
	removeAlias(infolist, string);
	return (ADDnodeEn(&(infolist->my_alias), string, 0) == NULL);
}

/**
 * prtAlias - Prints an alias definition.
 * @my_node: Pointer to the stringlist node representing the alias.
 *
 * This function prints the definition of an alias stored in the provided
 * stringlist node. The alias definition is printed in the format 'alias_name'
 * 'alias_value'\n.
 *
 * Return: 0 on success, 1 if the provided node is NULL.
 */
int prtAlias(stringlist_t *my_node)
{
	char *ptr = NULL, *m = NULL;

	/* Check if the provided node is not NULL */
	if (my_node)
	{
/* Locate the position of the '=' character in the alias definition */
		ptr = locateChar(my_node->string, '=');
/* Loop through the characters of the alias name and print each one */
		for (m = my_node->string; m <= ptr; m++)
			PutCharacter(*m);
/* Print a single quote to separate the alias name from the value */
		PutCharacter('\'');
/* Print the alias value starting from the character after '=' */
		Puts(ptr + 1);
/* Print a new line character to end the alias definition */
		Puts("'\n");
/* Return 0 to indicate success */
		return (0);
	}
	/* Return 1 to indicate failure if the provided node is NULL */
	return (1);
}

/**
 * aliasEmulator - Emulates the 'alias' command functionality.
 * @infolist: Pointer to the infolist structure.
 *
 * This function emulates the behavior of the 'alias' command.If called without
 * arguments,it prints all defined aliases.If called with arguments,it defines
 * new aliases or prints the definitions of existing ones.
 *
 * Return: Always returns 0.
 */
int aliasEmulator(infolist_t *infolist)
{
	char *ptr = NULL;
	int x = 0;
	stringlist_t *my_node = NULL;

	/* Check if the 'alias' command is called without arguments */
	if (infolist->argument_c == 1)
	{
		/* Loop through all defined aliases and print their definitions */
		my_node = infolist->my_alias;
		while (my_node)
		{
			prtAlias(my_node);
			my_node = my_node->next_node;
		}
		return (0);
	}
/*Loop through the provided arguments and define or print aliases accordingly*/
	for (x = 1; infolist->argument_v[x]; x++)
	{
		/* Locate the position of the '=' character in the argument */
		ptr = locateChar(infolist->argument_v[x], '=');
/* Check if '=' is present to decide whether to define or print the alias */
		if (ptr)
			defineAlias(infolist, infolist->argument_v[x]);
		else
			prtAlias(nodeStartWith(infolist->my_alias,
		infolist->argument_v[x], '='));
	}
	/* Always return 0 */
	return (0);
}
