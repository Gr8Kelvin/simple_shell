#include "shell.h"

/**
 * node_add - adds a node
 * @head: memory location
 * @strn: data
 * @number: node ind
 * Return: the size of list
 */
list_string *node_add(list_string **head, const char *strn, int number)
{
	list_string *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_string));
	if (!new_head)
		return (NULL);
	memory_set((void *)new_head, 0, sizeof(list_string));
	new_head->number = number;
	if (strn)
	{
		new_head->strn = string_dup(strn);
		if (!new_head->strn)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * nodeend_add - new node to the end of the list
 * @head: memory location
 * @strn: data
 * @number: node index
 * Return: size of list
 */
list_string *nodeend_add(list_string **head, const char *strn, int number)
{
	list_string *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_string));
	if (!new_node)
		return (NULL);
	memory_set((void *)new_node, 0, sizeof(list_string));
	new_node->number = number;
	if (strn)
	{
		new_node->strn = string_dup(strn);
		if (!new_node->strn)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * disp_list_str - prints
 * @hhr: stores the memory
 * Return: size of list
 */
size_t disp_list_str(const list_string *hhr)
{
	size_t ihr = 0;

	while (hhr)
	{
		print_s(hhr->strn ? hhr->strn : "(nil)");
		print_s("\n");
		hhr = hhr->next;
		ihr++;
	}
	return (ihr);
}

/**
 * rmv_node - deletes a node
 * @head: memory location
 * @ind: index
 * Return: 1 , otherwise 0
 */
int rmv_node(list_string **head, unsigned int ind)
{
	list_string *node, *prev_node;
	unsigned int ihr = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->strn);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (ihr == ind)
		{
			prev_node->next = node->next;
			free(node->strn);
			free(node);
			return (1);
		}
		ihr++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * avail_list - clears all nodes
 * @head_ptr: address
 */
void avail_list(list_string **head_ptr)
{
	list_string *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->strn);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

