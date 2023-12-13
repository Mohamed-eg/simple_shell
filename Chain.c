#include "header.h"

/**
 * isChain - Identifies and handles command chaining in input string.
 * @infolist: Pointer to the infolist structure.
 * @mybuff: Input string containing commands.
 * @ptr: Pointer to the current position in the input string.
 *
 * This function identifies command chaining in the input string and updates
 * the infolist structure accordingly. It recognizes the following chaining
 * operators: '||', '&&', and ';'.
 *
 * Return: 1 if a chaining operator is identified, 0 otherwise.
 */
int isChain(infolist_t *infolist, char *mybuff, size_t *ptr)
{
	size_t z = *ptr;

	/*Check for '||', '&&', or ';'(SEMICOLON)as chaining operators*/
	if (mybuff[z] == '|' && mybuff[z + 1] == '|')
	{
		mybuff[z] = 0;
		z++;
		infolist->cmdBufferTybe = orChain;
	}
	else if (mybuff[z] == '&' && mybuff[z + 1] == '&')
	{
		mybuff[z] = 0;
		z++;
		infolist->cmdBufferTybe = andChain;
	}
	else if (mybuff[z] == ';')
	{
		mybuff[z] = 0;
		infolist->cmdBufferTybe = cmdChain;
	}
	else
		return (0);
	/* Update the current position in the input string */
	*ptr = z;
	/* Return 1 to indicate a chaining operator was identified */
	return (1);
}

/**
 * checkChain - Checks command chaining conditions and modifies input string.
 * @infolist: Pointer to the infolist structure.
 * @mybuff: Input string containing commands.
 * @ptr: Pointer to the current position in the input string.
 * @x: Current position in the input string.
 * @mylen: Length of the input string.
 *
 * This function checks command chaining conditions based on previous command's
 * exit status and modifies the input string accordingly. If previous command
 * had an exit status, and the current command is part of an AND chain,input
 * string is truncated. If the previous command had no exit status, and current
 * command is part of an OR chain, the input string is truncated.
 *
 */
void checkChain(infolist_t *infolist, char *mybuff, size_t *ptr, size_t x,
size_t mylen)
{
	size_t z = *ptr;

	/* Check if the previous command was part of an AND chain */
	if (infolist->cmdBufferTybe == andChain)
	{
/* If the previous command had a non-zero exit status, truncate input string*/
		if (infolist->my_status)
		{
			mybuff[x] = 0;
			z = mylen;
		}
	}
/* Check if the previous command was part of an OR chain */
	if (infolist->cmdBufferTybe == orChain)
	{
		if (!infolist->my_status)
		{
/*If the previous command had a zero exit status, truncate the input string*/
			mybuff[x] = 0;
			z = mylen;
		}
	}
/* Update the current position in the input string */
	*ptr = z;
}

/**
 * replaceAlies - Replaces the command with its alias if applicable.
 * @infolist: Pointer to the infolist structure.
 *
 * This function searches for the specified command in the alias list
 * (infolist->my_alias) and replaces it with its corresponding value.
 * The replacement is done up to a maximum of 10 times to avoid potential
 * infinite loops.
 *
 * Return: 1 on success, 0 on failure.
 */
int replaceAlies(infolist_t *infolist)
{
	int x;
	stringlist_t *my_node;
	char *ptr;

	/*Loop to replace the command with its alias up to a maximum of 10 times*/
	for (x = 0; x < 10; x++)
	{
	/* Find the alias node that starts with the specified command */
	my_node = nodeStartWith(infolist->my_alias, infolist->argument_v[0], '=');
	if (!my_node)
		return (0);
	/* Free the original command */
	free(infolist->argument_v[0]);
	/* Locate the value of the alias (after the '=' character) */
	ptr = locateChar(my_node->string, '=');
	if (!ptr)
		return (0);
	/* Duplicate and assign the alias value to the command */
	ptr = duplcatString(ptr + 1);
	if (!ptr)
		return (0);
	infolist->argument_v[0] = ptr;
	}
	/* Return 1 on success */
	return (1);
}

/**
 * replaVars - Replaces variables in the command arguments with their values.
 * @infolist: Pointer to the infolist structure.
 *
 * This function replaces variables in the command arguments with their
 * corresponding values. The supported variables include "$?" for the exit
 * status, "$$" for the process ID, and environment variables.
 *
 * Return: Always returns 0.
 */
int replaVars(infolist_t *infolist)
{
	int x = 0;
	stringlist_t *my_node;

	/* Loop through the command arguments */
	for (x = 0; infolist->argument_v[x]; x++)
	{
	/* Check if the argument is a variable starting with '$' */
	if (infolist->argument_v[x][0] != '$' || !infolist->argument_v[x][1])
		continue;

	/* Replace "$?" with the exit status */
	if (!compareStrings(infolist->argument_v[x], "$?"))
	{
		replaStr(&(infolist->argument_v[x]),
			duplcatString(convert_number(infolist->my_status, 10, 0)));
		continue;
	}
	/* Replace "$$" with the process ID */
	if (!compareStrings(infolist->argument_v[x], "$$"))
	{
		replaStr(&(infolist->argument_v[x]),
			duplcatString(convert_number(getpid(), 10, 0)));
		continue;
	}
	/* Find the environment variable and replace it with its value */
	my_node = nodeStartWith(infolist->envir, &infolist->argument_v[x][1], '=');
	if (my_node)
	{
		replaStr(&(infolist->argument_v[x]),
			duplcatString(locateChar(my_node->string, '=') + 1));
		continue;
	}
	/* If the variable is not recognized, replace it with an empty string */
	replaStr(&infolist->argument_v[x], duplcatString(""));

	}
	/* Always return 0 */
	return (0);
}

/**
 * replaStr - Replaces a string with a new one and frees the old string.
 * @_old_str: Pointer to the old string to be replaced.
 * @new_str: Pointer to the new string.
 *
 * This function replaces the old string with a new one and frees the memory
 * occupied by the old string. The function updates the pointer to old string.
 *
 * Return: Always returns 1.
 */
int replaStr(char **_old_str, char *new_str)
{
	/* Free the memory occupied by the old string */
	free(*_old_str);
	/* Update the pointer to the old string with the new string */
	*_old_str = new_str;
	/* Always return 1 */
	return (1);
}
