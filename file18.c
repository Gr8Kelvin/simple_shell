#include "shell.h"

/**
 * length_list - determines the length of a linked list
 * @hd: points to first node
 * Return: size of list
 */
size_t length_list(const list_string *hd)
{
	size_t ias = 0;

	while (hd)
	{
		hd = hd->next;
		ias++;
	}
	return (ias);
}

/**
 * list_stringo_str - returns an array of strings
 * @head: points to first node
 * Return: array of strings
 */
char **list_stringo_str(list_string *head)
{
	list_string *node = head;
	size_t isd = length_list(head), jsd;
	char **strs;
	char *str;

	if (!head || !isd)
		return (NULL);
	strs = malloc(sizeof(char *) * (isd + 1));
	if (!strs)
		return (NULL);
	for (isd = 0; node; node = node->next, isd++)
	{
		str = malloc(len_str(node->string) + 1);
		if (!str)
		{
			for (jsd = 0; jsd < isd; jsd++)
				free(strs[jsd]);
			free(strs);
			return (NULL);
		}

		str = string_copy(str, node->string);
		strs[isd] = str;
	}
	strs[isd] = NULL;
	return (strs);
}

/**
 * disp_list - display elements of a list_string list
 * @hsd: points to first node
 * Return: size of list
 */
size_t disp_list(const list_string *hsd)
{
	size_t ias = 0;

	while (hsd)
	{
		print_s(con_num(hsd->number, 10, 0));
		print_ch(':');
		print_ch(' ');
		print_s(hsd->string ? hsd->string : "(nil)");
		print_s("\n");
		hsd = hsd->next;
		ias++;
	}
	return (ias);
}

/**
 * node_start - returns node
 * @node: points to list
 * @prefix: string
 * @c: next character
 * Return: match node or null
 */
list_string *node_start(list_string *node, char *prefix, char c)
{
	char *psd = NULL;

	while (node)
	{
		psd = sts_wt(node->string, prefix);
		if (psd && ((c == -1) || (*psd == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_id_node - gets the id of a node
 * @head: points to list head
 * @node: points to the node
 * Return: id of node or -1
 */
ssize_t get_id_node(list_string *head, list_string *node)
{
	size_t isd = 0;

	while (head)
	{
		if (head == node)
			return (isd);
		head = head->next;
		isd++;
	}
	return (-1);
}


