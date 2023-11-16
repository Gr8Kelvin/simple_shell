#include <stddef.h>
#include "shell.h"

/**
 * get_env - prints the env
 * @info: pointer of type inform_t
 * Return: always 0
 */
int get_env(inform_t *info)
{
	disp_list_str(info->env);
	return (0);
}

/**
 * disp_env - disp value of the envir
 * @info: pointer of type inform_t
 * @name: pointer
 * Return: the value
 */
char *disp_env(inform_t *info, const char *name)
{
	list_string *node = info->env;
	char *ptrd;

	while (node)
	{
		ptrd = sts_wt(node->strn, name);
		if (ptrd && *ptrd)
			return (ptrd);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - sets a new, modifies
 * @info: pointer of type inform_t
 *  Return: Always 0
 */
int set_env(inform_t *info)
{
	if (info->numargs != 3)
	{
		print_str("Invalid number of arguements\n");
		return (1);
	}
	if (set_info(info, info->commandargs[1], info->commandargs[2]))
		return (0);
	return (1);
}

/**
 * rmv_env - unsets
 * @info: pointer of type inform_t
 * Return: Always 0
 */
int rmv_env(inform_t *info)
{
	int ihr;

	if (info->numargs == 1)
	{
		print_str("Too few arguements.\n");
		return (1);
	}
	for (ihr = 1; ihr <= info->numargs; ihr++)
		rmv_info(info, info->commandargs[ihr]);

	return (0);
}

/**
 * pop_env - populates the environment
 * @info: pointer of type inform_t
 * Return: always 0
 */
int pop_env(inform_t *info)
{
	
	list_string *node = NULL;
	size_t ihr;

	for (ihr = 0; envir[ihr]; ihr++)
		nodeend_add(&node, envir[ihr], 0);
	info->env = node;
	return (0);
}


