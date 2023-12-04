#include "header.h"

/**
 **fillMemoryWith - fills memory with a constant byte
 *@a: the pointer to the memory area
 *@s: the byte to fill *a with
 *@x: the amount of bytes to be filled
 *Return: (a) a pointer to the memory area a
 */
char *fillMemoryWith(char *a, char s, unsigned int x)
{
	unsigned int i;

	for (i = 0; i < x; i++)
		a[i] = s;
	return (a);
}

/**
 * freeFun - frees a string of strings
 * @ss: string of strings
 */
void freeFun(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * reAllocat - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @oldsize: byte size of previous block
 * @newsize: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *reAllocat(void *pointer, unsigned int oldsize, unsigned int newsize)
{
	char *p;

	if (!pointer)
		return (malloc(newsize));
	if (!newsize)
		return (free(pointer), NULL);
	if (newsize == oldsize)
		return (pointer);

	p = malloc(newsize);
	if (!p)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		p[oldsize] = ((char *)pointer)[oldsize];
	free(pointer);
	return (p);
}
