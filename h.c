#include "shell.h"

/**
 * get_envir - details of environment
 * @info: pointer
 * Return: always 0
 */
char **get_envir(inform_t *info)
{
	if (!info->envir || info->envir_changed)
	{
		info->envir = list_stringo_str(info->env);
		info->envir_changed = 0;
	}

	return (info->envir);
}

/**
 * rmv_info - clears the environment
 * @info: pointer
 * @var:   variable
 *  Return: 1 , else 0
 */
int rmv_info(inform_t *info, char *var)
{
	list_string *node = info->env;
	size_t ihr = 0;
	char *ptrh;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptrh = sts_wt(node->strn, var);
		if (ptrh && *ptrh == '=')
		{
			info->envir_changed = rmv_node(&(info->env), ihr);
			ihr = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		ihr++;
	}
	return (info->envir_changed);
}

/**
 * set_info - sets environment variable
 * @info: pointer
 * @var: pointer
 * @value: pointer
 *  Return: always 0
 */
int set_info(inform_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_string *node;
	char *phr;

	if (!var || !value)
		return (0);

	buff = malloc(len_str(var) + len_str(value) + 2);
	if (!buff)
		return (1);
	string_copy(buff, var);
	str_cat(buff, "=");
	str_cat(buff, value);
	node = info->env;
	while (node)
	{
		phr = sts_wt(node->strn, var);
		if (phr && *phr == '=')
		{
			free(node->strn);
			node->strn = buff;
			info->envir_changed = 1;
			return (0);
		}
		node = node->next;
	}
	nodeend_add(&(info->env), buff, 0);
	free(buff);
	info->envir_changed = 1;
	return (0);
}

