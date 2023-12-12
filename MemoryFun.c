#include "header.h"

/**
 * fillMemoryWith - Fills a block of memory with a specified value.
 * @a: Pointer to the memory block.
 * @s: Value to fill the memory with.
 * @x: Number of bytes to fill.
 *
 * Return: A pointer to the filled memory block.
 */
char *fillMemoryWith(char *a, char s, unsigned int x)
{
	unsigned int y;
	/*Loop through the memory block and fill each byte with the specified value*/
	for (y = 0; y < x; y++)
		a[y] = s;
	return (a);/*Return a pointer to the filled memory block*/
}

/**
 * freeFun - Frees memory associated with a dynamically allocated array of strings.
 * @ss: Pointer to a pointer to strings.
 */
void freeFun(char **ss)
{
	/* Save the original pointer for freeing later*/
	char **x = ss;

	/*Check if the pointer is not NULL*/
	if (!ss)
		return;
	/*Free each individual string*/
	while (*ss)
		free(*ss++);
	/*Free the array of pointers*/
	free(x);
}

/**
 * reAllocat - Reallocates memory block to a new size.
 * @pointer: Pointer to the original memory block.
 * @oldsize: Old size of the memory block.
 * @newsize: New size to which the memory block should be reallocated.
 *
 * Return: Pointer to the newly allocated memory block.
 */
void *reAllocat(void *pointer, unsigned int oldsize, unsigned int newsize)
{
	char *x;

	/*If the original pointer is NULL, allocate new memory*/
	if (!pointer)
		return (malloc(newsize));

	/*If the new size is zero, free the original memory and return NULL*/
	if (!newsize)
		return (free(pointer), NULL);
	/*If the new size is equal to the old size, return the original pointer*/
	if (newsize == oldsize)
		return (pointer);

	/*Allocate a new memory block of the specified size*/
	x = malloc(newsize);
	if (!x)
		return (NULL);

	/*Copy the contents of the original block to the new block*/
	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		x[oldsize] = ((char *)pointer)[oldsize];
	/*Free the original memory block*/
	free(pointer);
	return (x);/*Return the pointer to the newly allocated memory block*/
}
