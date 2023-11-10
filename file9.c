#include "shell.h"

/**
 * get_env - prints the current envirment
 * @info: to maintain constant function prototype.
 * Return: Always 0
 */
int get_env(inform_t *info)
{
	disp_list(info->env);
	return (0);
}

/**
 * disp_env - gets the value
 * @info: to maintain
 * @name: env var name
 * Return: the value
 */
char *disp_env(inform_t *info, const char *name)
{
	list_string *node = info->env;
	char *pd;

	while (node)
	{
		pd = sts_wt(node->string, name);
		if (pd && *pd)
			return (pd);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - Initialize or modify
 * @info: to maintain constant function prototype.
 *  Return: Always 0
 */
int set_env(inform_t *info)
{
	if (info->numargs != 3)
	{
		print_str("Incorrect number of arguements\n");
		return (1);
	}
	if (set_info(info, info->commandargs[1], info->commandargs[2]))
		return (0);
	return (1);
}

/**
 * rmv_env - Remove variable
 * @info: to maintain constant function prototype.
 * Return: Always 0
 */
int rmv_env(inform_t *info)
{
	int ias;

	if (info->numargs == 1)
	{
		print_str("Too few arguements.\n");
		return (1);
	}
	for (ias = 1; ias <= info->numargs; ias++)
		rmv_info(info, info->commandargs[ias]);

	return (0);
}

/**
 * pop_env - populates env linked list
 * @info: to maintain constant function prototype.
 * Return: Always 0
 */
int pop_env(inform_t *info)
{
	
	list_string *node = NULL;
	size_t ias;

	for (ias = 0; envir[ias]; ias++)
		nodeend_add(&node, envir[ias], 0);
	info->env = node;
	return (0);
}

