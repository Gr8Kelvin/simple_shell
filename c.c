#include "shell.h"

/**
 * dis_hist -  history list
 * @info: pointer of type inform_t
 *  Return: always 0
 */
int dis_hist(inform_t *info)
{
	disp_list(info->history);
	return (0);
}

/**
 * unset_alias - changes alias to strings
 * @info: pointer of type inform_t
 * @strn: pointer, the alias string
 * Return: 0 on success, else 1 on error
 */
int unset_alias(inform_t *info, char *strn)
{
	int retn_val;
	char *ptr, chr;

	ptr = string_chr(strn, '=');
	if (!ptr)
		return (1);
	chr = *ptr;
	*ptr = 0;
	retn_val = rmv_node(&(info->alias),
			get_id_node(info->alias, node_start(info->alias, strn, -1)));
	*ptr = chr;
	return (retn_val);
}

/**
 * set_alias - alias to strings
 * @info: pointer of type inform_t
 * @strn: the string alias
 * Return: 0 , else 1 on error
 */
int set_alias(inform_t *info, char *strn)
{
	char *ptr;

	ptr = string_chr(strn, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, strn));

	unset_alias(info, strn);
	return (nodeend_add(&(info->alias), strn, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: 0 , else 1
 */
int print_alias(list_string *node)
{
	char *ptr = NULL, *ahr = NULL;

	if (node)
	{
		ptr = string_chr(node->strn, '=');
		for (ahr = node->strn; ahr <= ptr; ahr++)
			print_ch(*ahr);
		print_ch('\'');
		print_s(ptr + 1);
		print_s("'\n");
		return (0);
	}
	return (1);
}

/**
 * dis_als - build alias function
 * @info: pointer of type inform_t
 *  Return: always 0
 */
int dis_als(inform_t *info)
{
	int ihr = 0;
	char *ptr = NULL;
	list_string *node = NULL;

	if (info->numargs == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (ihr = 1; info->commandargs[ihr]; ihr++)
	{
		ptr = string_chr(info->commandargs[ihr], '=');
		if (ptr)
			set_alias(info, info->commandargs[ihr]);
		else
			print_alias(node_start(info->alias, info->commandargs[ihr], '='));
	}

	return (0);
}

