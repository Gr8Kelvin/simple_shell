#include "shell.h"

/**
 * dis_hist - displays the history list, one command by line
 * @info: to maintain constant function prototype.
 *  Return: Always 0
 */
int dis_hist(inform_t *info)
{
	print_list(info->history);
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

	pd = str_chr(str, '=');
	if (!pd)
		return (1);
	ch = *pd;
	*pd = 0;
	retur = rmv_node(&(info->alias),
			get_id_node(info->alias, node_sts_wt(info->alias, str, -1)));
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

	pd = str_chr(str, '=');
	if (!pd)
		return (1);
	if (!*++pd)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
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
		pd = str_chr(node->str, '=');
		for (ad = node->str; ad <= pd; ad++)
			print_ch(*ad);
		print_ch('\'');
		print_s(p + 1);
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
		pd = str_chr(info->commandargs[ias], '=');
		if (pd)
			set_alias(info, info->commandargs[ias]);
		else
			print_alias(node_sts_wt(info->alias, info->commandargs[ias], '='));
	}

	return (0);
}

