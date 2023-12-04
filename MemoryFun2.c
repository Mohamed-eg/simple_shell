#include "header.h"

/**
 * freePointers - frees a pointer and NULLs the address
 * @Pointer: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freePointers(void **Pointer)
{
	if (Pointer && *Pointer)
	{
		free(*Pointer);
		*Pointer = NULL;
		return (1);
	}
	return (0);
}
