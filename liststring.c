#include "header.h"

/**
 * ADDnode - adds a node to the start of the list
 * @firstNode: address of pointer to firstNode node
 * @string: string field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
stringlist_t *ADDnode(stringlist_t **firstNode, const char *string, int number)
{
	stringlist_t *new_head;

	if (!firstNode)
		return (NULL);
	new_head = malloc(sizeof(stringlist_t));
	if (!new_head)
		return (NULL);
	fillMemoryWith((void *)new_head, 0, sizeof(stringlist_t));
	new_head->number = number;
	if (string)
	{
		new_head->string = duplcatString(string);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next_node = *firstNode;
	*firstNode = new_head;
	return (new_head);
}

/**
 * ADDnodeEn - adds a node to the end of the list
 * @firstNode: address of pointer to firstNode node
 * @string: string field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
stringlist_t *ADDnodeEn(stringlist_t **firstNode, const char *string, int number)
{
	stringlist_t *new_node, *node;

	if (!firstNode)
		return (NULL);

	node = *firstNode;
	new_node = malloc(sizeof(stringlist_t));
	if (!new_node)
		return (NULL);
	fillMemoryWith((void *)new_node, 0, sizeof(stringlist_t));
	new_node->number = number;
	if (string)
	{
		new_node->string = duplcatString(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next_node)
			node = node->next_node;
		node->next_node = new_node;
	}
	else
		*firstNode = new_node;
	return (new_node);
}

/**
 * printListString - prints only the string element of a stringlist_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printListString(const stringlist_t *h)
{
	size_t i = 0;

	while (h)
	{
		Puts(h->string ? h->string : "(nil)");
		Puts("\n");
		h = h->next_node;
		i++;
	}
	return (i);
}

/**
 * deletNode - deletes node at given index
 * @firstNode: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deletNode(stringlist_t **firstNode, unsigned int index)
{
	stringlist_t *node, *prev_node;
	unsigned int i = 0;

	if (!firstNode || !*firstNode)
		return (0);

	if (!index)
	{
		node = *firstNode;
		*firstNode = (*firstNode)->next_node;
		free(node->string);
		free(node);
		return (1);
	}
	node = *firstNode;
	while (node)
	{
		if (i == index)
		{
			prev_node->next_node = node->next_node;
			free(node->string);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next_node;
	}
	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @head_ptr: address of pointer to firstNode node
 *
 * Return: void
 */
void freeList(stringlist_t **head_ptr)
{
	stringlist_t *node, *next_node, *firstNode;

	if (!head_ptr || !*head_ptr)
		return;
	firstNode = *head_ptr;
	node = firstNode;
	while (node)
	{
		next_node = node->next_node;
		free(node->string);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
