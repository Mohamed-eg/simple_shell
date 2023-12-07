#include "header.h"

/**
 * listLength - determines length of linked list
 * @x: pointer to first node
 *
 * Return: size of list
 */
size_t listLength(const stringlist_t *x)
{
	size_t i = 0;/*size_t is a data type declared in <stddef.h>*/

	while (x)
	{
		x = x->next_node;/*Moves to the next_node node in the linked list.*/
		i++;
	}
	return (i);
	/*After the loop, the function returns the
	final value of i, which represents the total number of nodes
	in the linked list.*/
}

/**
 * listToStrings - returns an array of strings of the list->string
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **listToStrings(stringlist_t *head)
{
	stringlist_t *node = head;
	size_t i = listLength(head), j;
	char **strs;
	char *string;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next_node, i++)
	{
		string = malloc(getStringLength(node->string) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		string = copyStrings(string, node->string);
		strs[i] = string;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * elementList - prints all elements of a stringlist_t linked list
 * @x: pointer to first node
 *
 * Return: size of list
 */
size_t elementList(const stringlist_t *x)
{
	size_t i = 0;

	while (x)
	{
		Puts(convert_number(x->number, 10, 0));
		PutCharacter(':');
		PutCharacter(' ');
		Puts(x->string ? x->string : "(nil)");
		Puts("\n");
		x = x->next_node;
		i++;
	}
	return (i);
}

/**
 * nodeStartWith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next_node character after prefix to match
 *
 * Return: match node or null
 */
stringlist_t *nodeStartWith(stringlist_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->string, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next_node;
	}
	return (NULL);
}

/**
 * nodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t nodeIndex(stringlist_t *head, stringlist_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next_node;
		i++;
	}
	return (-1);
}
