#include "shell.h"

/**
 * get_envir - returns the string array
 * @info: to maintain constant function prototype.
 * Return: Always 0
 */
char **get_envir(inform_t *info)
{
	if (!info->envir || info->env_changed)
	{
		info->envir = list_stringo_str(info->env);
		info->env_changed = 0;
	}

	return (info->envir);
}

/**
 * rmv_info - Remove an envirment variable
 * @info: to maintain constant function prototype.
 *  Return: 1 on delete otherwise 0
 * @var: the string env
 */
int rmv_info(inform_t *info, char *var)
{
	list_string *node = info->env;
	size_t ias = 0;
	char *pd;

	if (!node || !var)
		return (0);

	while (node)
	{
		pd = sts_wt(node->str, var);
		if (pd && *pd == '=')
		{
			info->env_changed = rmv_node(&(info->env), ias);
			ias = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		ias++;
	}
	return (info->env_changed);
}

/**
 * set_info - Initialize or modify envirment variable,
 * @info: to maintain constant function prototype.
 * @var: string env var property
 * @value: string env var value
 *  Return: Always 0
 */
int set_info(inform_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_string *node;
	char *pd;

	if (!var || !value)
		return (0);

	buf = malloc(len_str(var) + len_str(value) + 2);
	if (!buf)
		return (1);
	str_cpy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		pd = sts_wt(node->str, var);
		if (pd && *pd == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

