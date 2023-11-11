#include "shell.h"

/**
 * is_chn - if current char in the buffer
 * @info: a pointer
 * @buff: the buffer that contains the character
 * @phr: memory location
 * Return: 1 otherwise 0
 */
int is_chn(inform_t *info, char *buff, size_t *phr)
{
	size_t jhr = *phr;

	if (buff[jhr] == '|' && buff[jhr + 1] == '|')
	{
		buff[jhr] = 0;
		jhr++;
		info->commandtype = CMD_OR;
	}
	else if (buff[jhr] == '&' && buff[jhr + 1] == '&')
	{
		buff[jhr] = 0;
		jhr++;
		info->commandtype = CMD_AND;
	}
	else if (buff[jhr] == ';')
	{
		buff[jhr] = 0;
		info->commandtype = CMD_CHAIN;
	}
	else
		return (0);
	*phr = jhr;
	return (1);
}

/**
 * ck_chn - checks if chaining should continue
 * @info: a pointer
 * @buff: the buffer
 * @phr: memory location
 * @ihr: starting position
 * @len: length of buffer
 */
void ck_chn(inform_t *info, char *buff, size_t *phr, size_t ihr, size_t len)
{
	size_t jhr = *phr;

	if (info->commandtype == CMD_AND)
	{
		if (info->status)
		{
			buff[ihr] = 0;
			jhr = len;
		}
	}
	if (info->commandtype == CMD_OR)
	{
		if (!info->status)
		{
			buff[ihr] = 0;
			jhr = len;
		}
	}

	*phr = jhr;
}

/**
 * als_rep - replaces an alias
 * @info: a pointer
 * Return: 1  otherwise 0
 */
int als_rep(inform_t *info)
{
	int ihr;
	list_string *node;
	char *pthr;

	for (ihr = 0; ihr < 10; ihr++)
	{
		node = node_start(info->alias, info->commandargs[0], '=');
		if (!node)
			return (0);
		free(info->commandargs[0]);
		pthr = string_chr(node->strn, '=');
		if (!pthr)
			return (0);
		pthr = string_dup(pthr + 1);
		if (!pthr)
			return (0);
		info->commandargs[0] = pthr;
	}
	return (1);
}

/**
 * var_rep - replaces variables
 * @info: a pointer
 * Return: 1  otherwise 0
 */
int var_rep(inform_t *info)
{
	int ihr = 0;
	list_string *node;

	for (ihr = 0; info->commandargs[ihr]; ihr++)
	{
		if (info->commandargs[ihr][0] != '$' || !info->commandargs[ihr][1])
			continue;

		if (!str_cmp(info->commandargs[ihr], "$?"))
		{
			str_rep(&(info->commandargs[ihr]),
					string_dup(con_num(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->commandargs[ihr], "$$"))
		{
			str_rep(&(info->commandargs[ihr]),
					string_dup(con_num(getpid(), 10, 0)));
			continue;
		}
		node = node_start(info->env, &info->commandargs[ihr][1], '=');
		if (node)
		{
			str_rep(&(info->commandargs[ihr]),
					string_dup(string_chr(node->strn, '=') + 1));
			continue;
		}
		str_rep(&info->commandargs[ihr], string_dup(""));

	}
	return (0);
}

/**
 * str_rep - replaces a given string
 * @old: memory location
 * @new: memory location
 * Return: 1 otherwise 0
 */
int str_rep(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

