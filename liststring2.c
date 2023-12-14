#include "header.h"

/**
 * listLength - Calculates the length of a linked list.
 *
 * @x: Pointer to the firstNode of the linked list (stringlist_t).
 *
 * Return: The number of nodes in the linked list.
 */
size_t listLength(const stringlist_t *x)
{
	size_t j = 0;/*size_t is a data type declared in <stddef.h>*/

	while (x)
	{
		x = x->next_node;/*Moves to the next_node node in the linked list.*/
		j++;
	}
	return (j);
	/*
	* After the loop, the function returns the
	* final value of j, which represents the total number of nodes
	* in the linked list.
	*/
}

/**
 * listToStrings - Converts a linked list of strings to an array of strings.
 *
 * Given the firstNode of a linked list of strings, this function creates
 * an array of strings, each containing the content of a
 * node in the linked list.
 * @firstNode: Pointer to the firstNode of the linked list (stringlist_t).
 *
 * Return: An array of strings representing the linked list,or NULL on failure.
 *         The caller is responsible for freeing the memory allocated for the
 *         array and its strings.
 */
char **listToStrings(stringlist_t *firstNode)
{
	stringlist_t *currentNode = firstNode;
	size_t x = listLength(firstNode), z;
	char **strs;
	char *string;

	if (!firstNode || !x)/* Check for invalid input or an empty list */
		return (NULL);
	/* Allocate memory for the array of strings */
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
/* Traverse the linked list and convert each Node's content to a string */
	for (x = 0; currentNode; currentNode = currentNode->next_node, x++)
	{/* Allocate memory for the string */
		string = malloc(getStringLength(currentNode->string) + 1);
		if (!string)
		{/* Free allocated memory if an error occurs */
			for (z = 0; z < x; z++)
				free(strs[z]);
			free(strs);
			return (NULL);
		}

		/* Copy the content of the currentNode to the string */
		string = copyStrings(string, currentNode->string);
		strs[x] = string;
	}
	strs[x] = NULL;/* Set the last element of the array to NULL */
	return (strs);/* Return the array of strings */
}


/**
 * elementList - Prints elements of a linked list.
 *
 * Given the head of a linked list, this function prints the elements of the
 * list, including the numeric value and string content of each node.
 *
 * @x: Pointer to the head of the linked list (stringlist_t).
 *
 * Return: The number of elements in the linked list.
 */
size_t elementList(const stringlist_t *x)
{
	size_t j = 0;

	/* Traverse the linked list and print each element */
	while (x)
	{
		Puts(convert_number(x->number, 10, 0));
		PutCharacter(':');
		PutCharacter(' ');
		Puts(x->string ? x->string : "(Null)");
		Puts("\n");
		x = x->next_node;
		j++;
	}
	/* Return the total number of elements in the linked list */
	return (j);
}

/**
 * nodeStartWith - Finds a node with a string starting with a given prefix.
 *
 * Given the head of a linked list, this function searches for a node whose
 * string content starts with the specified prefix and optionally has specific
 * character at the next position.
 *
 * @headNode: Pointer to the head of the linked list (stringlist_t).
 * @srchprfx: The prefix to search for.
 * @chr: The optional character at the next position (-1 if not required).
 *
 * Return: Pointer to the found headNode or NULL if not found.
 */
stringlist_t *nodeStartWith(stringlist_t *headNode, char *srchprfx, char chr)
{
	char *t = NULL;

	/* Traverse the linked list and search for a matching headNode */
	while (headNode)
	{
		t = startsWith(headNode->string, srchprfx);
		if (t && ((chr == -1) || (*t == chr)))
			return (headNode);
		/* Move to the next node in the linked list */
		headNode = headNode->next_node;
	}
	/* Return NULL if no matching node is found */
	return (NULL);
}

/**
 * nodeIndex - Finds the index of a node in a linked list.
 *
 * Given the head of a linked list and a specific node, this function finds
 * the index of the node in the linked list. If the node is not found, it
 * returns -1.
 *
 * @firstNode: Pointer to the head of the linked list (stringlist_t).
 * @currentNode: The specific node whose index is to be found.
 *
 * Return: The index of the node if found; otherwise, -1.
 */
ssize_t nodeIndex(stringlist_t *firstNode, stringlist_t *currentNode)
{
	size_t x = 0;

	/* Traverse the linked list to find the index of the specified node */
	while (firstNode)
	{
		if (firstNode == currentNode)
			return (x);
		firstNode = firstNode->next_node;
		x++;
	}
	/* Return -1 if the specified node is not found in the linked list */
	return (-1);
}
