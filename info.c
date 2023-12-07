#include "header.h"

/**
 * clearInformation - initializes infolist_t struct
 * @infolist: struct address
 */
void clearInformation(infolist_t *infolist)
{
	infolist->argument = NULL;
	infolist->argument_v = NULL;
	infolist->str_path = NULL;
	infolist->argument_c = 0;
}

/**
 * setInformation - initializes infolist_t struct
 * @infolist: struct address
 * @av: argument vector
 */
void setInformation(infolist_t *infolist, char **av)
{
	int i = 0;

	infolist->fname = av[0];
	if (infolist->argument)
	{
		infolist->argument_v = SplitString(infolist->argument, " \t");
		if (!infolist->argument_v)
		{

			infolist->argument_v = malloc(sizeof(char *) * 2);
			if (infolist->argument_v)
			{
				infolist->argument_v[0] = duplcatString(infolist->argument);
				infolist->argument_v[1] = NULL;
			}
		}
		for (i = 0; infolist->argument_v && infolist->argument_v[i]; i++)
			;
		infolist->argument_c = i;

		replaceAlies(infolist);
		replaVars(infolist);
	}
}

/**
 * freeInformation - frees infolist_t struct fields
 * @infolist: struct address
 * @all: true if freeing all fields
 */
void freeInformation(infolist_t *infolist, int all)
{
	freeFun(infolist->argument_v);
	infolist->argument_v = NULL;
	infolist->str_path = NULL;
	if (all)
	{
		if (!infolist->cmd_buf)
			free(infolist->argument);
		if (infolist->env)
			freeList(&(infolist->env));
		if (infolist->history)
			freeList(&(infolist->history));
		if (infolist->alias)
			freeList(&(infolist->alias));
		freeFun(infolist->environ);
			infolist->environ = NULL;
		freePointers((void **)infolist->cmd_buf);
		if (infolist->readfd > 2)
			close(infolist->readfd);
		PutCharacter(bufferFlush);
	}
}
