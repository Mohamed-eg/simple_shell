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
 * freeInformation - Frees memory associated with an infolist structure.
 * @infolist: Pointer to the infolist structure to be freed.
 * @alllist: Integer flag indicating whether to free all associated lists.
 *
 * This function frees the memory allocated for various fields within the
 * infolist structure. The memory for individual fields is freed based on the
 * conditions specified by the `alllist` flag.
 */
void freeInformation(infolist_t *infolist, int alllist)
{
	/* Free the argument_v field */
	freeFun(infolist->argument_v);
	infolist->argument_v = NULL;
	/* Set str_path to NULL */
	infolist->str_path = NULL;
	/* Check if alllist flag is set */
	if (alllist)
	{/* Free the argument field if cmdBuffer is not set */
		if (!infolist->cmdBuffer)
			free(infolist->argument);
		/* Free the envir list */
		if (infolist->envir)
			freeList(&(infolist->envir));
		/* Free the my_history list */
		if (infolist->my_history)
			freeList(&(infolist->my_history));
		/* Free the my_alias list */
		if (infolist->my_alias)
			freeList(&(infolist->my_alias));
		/* Free the environ field */
		freeFun(infolist->environ);
			infolist->environ = NULL;
		/* Free pointers in cmdBuffer */
		freePointers((void **)infolist->cmdBuffer);
		/* Close file descriptor if rfd is greater than 2 */
		if (infolist->rfd > 2)
			close(infolist->rfd);
		/* Put a character to bufferFlush */
		PutCharacter(bufferFlush);
	}
}
