#include "header.h"

/**
 * freePointers - Frees the memory pointed to by a pointer and sets it to NULL.
 * @Pointer: A pointer to the memory to be freed.
 *
 * Return:
 * - 1 if the memory was successfully freed.
 * - 0 if the pointer is NULL or points to NULL.
 */
int freePointers(void **Pointer)
{
	/*Check if the pointer is not NULL and points to a valid memory location*/
	if (Pointer && *Pointer)
	{
		free(*Pointer);/*Free the memory*/
		*Pointer = NULL;/*Set the pointer to NULL*/
		return (1);/* Return 1 indicating success*/
	}
	return (0);/*Return 0 indicating failure*/
}
