#include "header.h"

/**
 * clearInformation - Initializes an infolist_t structure.
 *
 * This function takes the address of an infolist_t structure and sets its
 * members to default values (NULL and 0) to ensure a clean initialization.
 *
 * @infolist: Pointer to the infolist_t structure to be initialized.
 */
void clearInformation(infolist_t *infolist)
{
	/* Set members to default values (NULL and 0) */
	infolist->argument = NULL;
	infolist->argument_v = NULL;
	infolist->str_path = NULL;
	infolist->argument_c = 0;
}

/**
 * setInformation - Sets information in an infolist_t structure.
 *
 * This function takes an infolist_t structure and a command-line argument
 * vector. It sets the filename, argument, argument_v, and argument_c members
 * of the infolist_t structure based on the provided arguments.
 *
 * @infolist: Pointer to the infolist_t structure to be updated.
 * @arg_vec: Command-line argument vector.
 */
void setInformation(infolist_t *infolist, char **arg_vec)
{
	int x = 0;

	/* Set the filename member to the first element of arg_vec */
	infolist->filename = arg_vec[0];
	/* Check if argument is not NULL and process it */
	if (infolist->argument)
	{
		/* Split the argument into tokens and set argument_v */
		infolist->argument_v = SplitString(infolist->argument, " \t");
		/* If SplitString fails, set a default argument_v with one element */
		if (!infolist->argument_v)
		{
			infolist->argument_v = malloc(sizeof(char *) * 2);
			if (infolist->argument_v)
			{
				infolist->argument_v[0] = duplcatString(infolist->argument);
				infolist->argument_v[1] = NULL;
			}
		}
		/* Count the number of elements in argument_v and set argument_c */
		for (x = 0; infolist->argument_v && infolist->argument_v[x]; x++)
			;
		infolist->argument_c = x;

		/* Perform additional processing on the infolist */
		replaceAlies(infolist);
		replaVars(infolist);
	}
}

/**
 * freeInformation - frees infolist_t struct fields
 * @infolist: struct address
 * @alllist: true if freeing alllist fields
 */
void freeInformation(infolist_t *infolist, int alllist)
{
	freeFun(infolist->argument_v);
	infolist->argument_v = NULL;
	infolist->str_path = NULL;
	if (alllist)
	{
		if (!infolist->cmdBuffer)
			free(infolist->argument);
		if (infolist->env)
			freeList(&(infolist->env));
		if (infolist->history)
			freeList(&(infolist->history));
		if (infolist->alias)
			freeList(&(infolist->alias));
		freeFun(infolist->environ);
			infolist->environ = NULL;
		freePointers((void **)infolist->cmdBuffer);
		if (infolist->rfd > 2)
			close(infolist->rfd);
		PutCharacter(bufferFlush);
	}
}
