#include "shell.h"

/**
 * add_node - adds node to start of the list
 * @head: pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
 */
list_string *add_node(list_string **head, const char *str, int num)
{
	list_string *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_string));
	if (!n_head)
		return (NULL);
	mem_set((void *)n_head, 0, sizeof(list_string));
	new_head->num = num;
	if (str)
	{
		n_head->str = str_dup(str);
		if (!n_head->str)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * add_node_end - adds node to end of the list
 * @head: pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
 */
list_string *add_node_end(list_string **head, const char *str, int num)
{
	list_string *n_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	n_node = malloc(sizeof(list_string));
	if (!n_node)
		return (NULL);
	mem_set((void *)n_node, 0, sizeof(list_string));
	n_node->num = num;
	if (str)
	{
		n_node->str = str_dup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * disp_list - prints the string element of a list_string linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t disp_list(const list_string *h)
{
	size_t ias = 0;

	while (h)
	{
		print_s(h->str ? h->str : "(nil)");
		print_s("\n");
		h = h->next;
		ias++;
	}
	return (ias);
}

/**
 * rmv_node - deletes node at given index
 * @head: pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int rmv_node(list_string **head, unsigned int index)
{
	list_string *node, *prev_node;
	unsigned int ias = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (ias == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		ias++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * avail_list - frees all nodes of a list
 * @head_ptr: pointer to head node
 * Return: void
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
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
