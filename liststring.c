#include "header.h"

/**
 * ADDnode - Adds a new node to the beginning of a linked list.
 *
 * This function creates a new node with the specified numeric value and, if
 * provided, a duplicated string. The new node is added to the beginning of
 * the linked list.
 *
 * @firstNode: Pointer to the pointer to the head of the linked list.
 * @string: The string content for the new node (NULL if not provided).
 * @number: The numeric value for the new node.
 *
 * Return: Pointer to the newly added node, or NULL on failure.
 */
stringlist_t *ADDnode(stringlist_t **firstNode, const char *string, int number)
{
	stringlist_t *newHead;

	/* Check for a valid pointer to the pointer to the head of the linked list */
	if (!firstNode)
		return (NULL);
	/* Allocate memory for the new node */
	newHead = malloc(sizeof(stringlist_t));
	if (!newHead)
		return (NULL);
	/* Initialize the new node's memory to zero */
	fillMemoryWith((void *)newHead, 0, sizeof(stringlist_t));
	/* Set the numeric value for the new node */
	newHead->number = number;
	/* Duplicate the string content if provided */
	if (string)
	{
		newHead->string = duplcatString(string);
		if (!newHead->string)
		{
			/* Free allocated memory if an error occurs */
			free(newHead);
			return (NULL);
		}
	}
	/* Add the new node to the beginning of the linked list */
	newHead->next_node = *firstNode;
	*firstNode = newHead;
	/* Return a pointer to the newly added node */
	return (newHead);
}

/**
 * ADDnodeEn - Adds a new node to the end of a linked list.
 *
 * This function creates a new node with the specified numeric value and, if
 * provided, a duplicated string. The new node is added
 * to the end of the linked list.
 * @firstNode: Pointer to the pointer to the head of the linked list.
 * @string: The string content for the new node (NULL if not provided).
 * @number: The numeric value for the new node.
 *
 * Return: Pointer to the newly added node, or NULL on failure.
 */
stringlist_t *ADDnodeEn(stringlist_t **firstNode,
	const char *string, int number)
{
	stringlist_t *newNode, *currentNode;

	 /* Check for a valid pointer to the pointer to the head of the linked list */
	if (!firstNode)
		return (NULL);

	/* Initialize the current node to the head of the linked list */
	currentNode = *firstNode;
	/* Allocate memory for the new node */
	newNode = malloc(sizeof(stringlist_t));
	if (!newNode)
		return (NULL);
	/* Initialize the new node's memory to zero */
	fillMemoryWith((void *)newNode, 0, sizeof(stringlist_t));
	/* Set the numeric value for the new node */
	newNode->number = number;
	/* Duplicate the string content if provided */
	if (string)
	{
		newNode->string = duplcatString(string);
		if (!newNode->string)
		{
			/* Free allocated memory if an error occurs */
			free(newNode);
			return (NULL);
		}
	}
	/* Add the new node to the end of the linked list */
	if (currentNode)
	{
		while (currentNode->next_node)
			currentNode = currentNode->next_node;
		currentNode->next_node = newNode;
	}
	else/* If the list is empty, set the new node as the head of the list */
		*firstNode = newNode;
	/* Return a pointer to the newly added node */
	return (newNode);
}

/**
 * printListString - Prints the string content of each node in a linked list.
 *
 * Given the head of a linked list, this function prints the string content of
 * each node. If a node's string is NULL, it prints "(Null)" for that node.
 *
 * @head: Pointer to the head of the linked list (stringlist_t).
 *
 * Return: The number of nodes in the linked list.
 */
size_t printListString(const stringlist_t *head)
{
	size_t x = 0;

	 /* Traverse the linked list and print the string content of each node */
	while (head)
	{
		Puts(head->string ? head->string : "(Null)");
		Puts("\n");
		head = head->next_node;
		x++;
	}
	/* Return the total number of nodes in the linked list */
	return (x);
}

/**
 * deletNode - Deletes a node at a specified index in a linked list.
 *
 * This function deletes the node at the specified index in the linked list.
 * If the index is 0, it deletes the first node. Returns 1 on success,
 * 0 if the index is out of bounds or if the list is empty.
 *
 * @firstNode: Pointer to the pointer to the head of the linked list.
 * @nodeindex: The index of the node to be deleted.
 *
 * Return: 1 on success, 0 on failure.
 */
int deletNode(stringlist_t **firstNode, unsigned int nodeindex)
{
	stringlist_t *currentNode, *previousNode;
	unsigned int x = 0;

	/* Check for a valid pointer to the pointer to the head of the linked list */
	if (!firstNode || !*firstNode)
		return (0);

	 /* If nodeindex is 0, delete the first node */
	if (!nodeindex)
	{
		currentNode = *firstNode;
		*firstNode = (*firstNode)->next_node;
		free(currentNode->string);
		free(currentNode);
		return (1);
	}
	/* Traverse the linked list to find the node at the specified index */
	currentNode = *firstNode;
	while (currentNode)
	{
		if (x == nodeindex)
		{
			previousNode->next_node = currentNode->next_node;
			free(currentNode->string);
			free(currentNode);
			return (1);
		}
		x++;
		previousNode = currentNode;
		currentNode = currentNode->next_node;
	}
	/* Return 0 if the index is out of bounds or the list is empty */
	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @headPointr: address of pointer to firstNode currentNode
 *
 * Return: void
 */
void freeList(stringlist_t **headPointr)
{
	stringlist_t *currentNode, *nextNode, *firstNode;

	/* Check for a valid pointer to the pointer to the head of the linked list */
	if (!headPointr || !*headPointr)
		return;
	/* Store the original head pointer for reference */
	firstNode = *headPointr;
	currentNode = firstNode;
	/* Iterate through each node in the linked list and free memory */
	while (currentNode)
	{
		nextNode = currentNode->next_node;
		free(currentNode->string);
		free(currentNode);
		currentNode = nextNode;
	}
	/* Set the head pointer to NULL after freeing all nodes */
	*headPointr = NULL;
}
