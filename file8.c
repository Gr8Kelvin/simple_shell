#include "shell.h"

/**
 * dis_hist - displays the history list, one command by line
 * @info: to maintain constant function prototype.
 *  Return: Always 0
 */
int dis_hist(inform_t *info)
{
	disp_list_str(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: 0 success, 1 on error
 */
int unset_alias(inform_t *info, char *str)
{

	char *pd, ch;
	int retur;

	pd = string_chr(str, '=');
	if (!pd)
		return (1);
	ch = *pd;
	*pd = 0;
	retur = rmv_node(&(info->alias),
			get_id_node(info->alias, node_start(info->alias, str, -1)));
	*pd = ch;
	return (retur);
}

/**
 * set_alias - sets alias
 * @info: parameter struct
 * @str: the string alias
 * Return: 0 success, 1 error
 */
int set_alias(inform_t *info, char *str)
{
	char *pd;

	pd = string_chr(str, '=');
	if (!pd)
		return (1);
	if (!*++pd)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (nodeend_add(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints alias string
 * @node: alias node
 * Return: 0 success, 1 error
 */
int print_alias(list_string *node)
{
	char *pd = NULL, *ad = NULL;

	if (node)
	{
		pd = string_chr(node->string, '=');
		for (ad = node->string; ad <= pd; ad++)
			print_ch(*ad);
		print_ch('\'');
		print_s(pd + 1);
		print_s("'\n");
		return (0);
	}
	return (1);
}

/**
 * dis_alias - mimics alias build
 * @info: to maintain constant function prototype.
 *  Return: Always 0
 */
int dis_alias(inform_t *info)
{
	int ias = 0;
	char *pd = NULL;
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
	for (ias = 1; info->commandargs[ias]; ias++)
	{
		pd = string_chr(info->commandargs[ias], '=');
		if (pd)
			set_alias(info, info->commandargs[ias]);
		else
			print_alias(node_start(info->alias, info->commandargs[ias], '='));
	}

	return (0);
}


