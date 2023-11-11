#include "shell.h"

/**
 * length_list - the length
 * @hhr: pointer
 * Return: size of list
 */
size_t length_list(const list_string *hhr)
{
	size_t ihr = 0;

	while (hhr)
	{
		hhr = hhr->next;
		ihr++;
	}
	return (ihr);
}

/**
 * list_stringo_str - array of strings
 * @head: points to the first node
 * Return: an array of strings
 */
char **list_stringo_str(list_string *head)
{
	list_string *node = head;
	size_t ihr = length_list(head), jhr;
	char **strs;
	char *strn;

	if (!head || !ihr)
		return (NULL);
	strs = malloc(sizeof(char *) * (ihr + 1));
	if (!strs)
		return (NULL);
	for (ihr = 0; node; node = node->next, ihr++)
	{
		strn = malloc(len_str(node->strn) + 1);
		if (!strn)
		{
			for (jhr = 0; jhr < ihr; jhr++)
				free(strs[jhr]);
			free(strs);
			return (NULL);
		}
		strn = string_copy(strn, node->strn);
		strs[ihr] = strn;
	}
	strs[ihr] = NULL;
	return (strs);
}


/**
 * disp_list - prints all
 * @head: points
 * Return: size of list
 */
size_t disp_list(const list_string *head)
{
	size_t ihr = 0;

	while (head)
	{
		print_s(con_num(head->number, 10, 0));
		print_ch(':');
		print_ch(' ');
		print_s(head->strn ? head->strn : "(nil)");
		print_s("\n");
		head = head->next;
		ihr++;
	}
	return (ihr);
}

/**
 * node_start - returns node
 * @node: pointer
 * @pref: the prefix string to match
 * @chr: character
 * Return: the node, or null
 */
list_string *node_start(list_string *node, char *pref, char chr)
{
	char *ptrh = NULL;

	while (node)
	{
		ptrh = sts_wt(node->strn, pref);
		if (ptrh && ((chr == -1) || (*ptrh == chr)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_id_node - index of a node
 * @head: pointer
 * @node: pointer
 * Return: node, or -1
 */
ssize_t get_id_node(list_string *head, list_string *node)
{
	size_t ihr = 0;

	while (head)
	{
		if (head == node)
			return (ihr);
		head = head->next;
		ihr++;
	}
	return (-1);
}

