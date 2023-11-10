#include "shell.h"

/**
 * is_chn - test char in buffer as chain delimeter
 * @info: parameter struct
 * @buf: char buffer
 * @p: position in buf
 * Return: 1 if delimeter otherwise 0
 */
int is_chn(inform_t *info, char *buf, size_t *p)
{
	size_t jas = *p;

	if (buf[jas] == '|' && buf[jas + 1] == '|')
	{
		buf[jas] = 0;
		jas++;
		info->commandtype = CMD_OR;
	}
	else if (buf[jas] == '&' && buf[jas + 1] == '&')
	{
		buf[jas] = 0;
		jas++;
		info->commandtype = CMD_AND;
	}
	else if (buf[jas] == ';') /* found end of this command */
	{
		buf[jas] = 0; /* replace semicolon with null */
		info->commandtype = CMD_CHAIN;
	}
	else
		return (0);
	*p = jas;
	return (1);
}

/**
 * chk_chn - checks chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of position in buf
 * @i: starting position in buf
 * @len: length
 * Return: Void
 */
void chk_chn(inform_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jas = *p;

	if (info->commandtype == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			jas = len;
		}
	}
	if (info->commandtype == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			jas = len;
		}
	}

	*p = jas;
}

/**
 * als_rep - replaces an aliase
 * @info: parameter struct
 * Return: 1 otherwise 0
 */
int als_rep(inform_t *info)
{
	int ias;
	list_string *node;
	char *p;

	for (ias = 0; ias < 10; ias++)
	{
		node = node_start(info->alias, info->commandargs[0], '=');
		if (!node)
			return (0);
		free(info->commandargs[0]);
		p = string_chr(node->string, '=');
		if (!p)
			return (0);
		p = string_dup(p + 1);
		if (!p)
			return (0);
		info->commandargs[0] = p;
	}
	return (1);
}

/**
 * var_rep - replaces vars
 * @info: parameter struct
 * Return: 1 otherwise 0
 */
int var_rep(inform_t *info)
{
	int ias = 0;
	list_string *node;

	for (ias = 0; info->commandargs[ias]; ias++)
	{
		if (info->commandargs[ias][0] != '$' || !info->commandargs[ias][1])
			continue;

		if (!str_cmp(info->commandargs[ias], "$?"))
		{
			str_rep(&(info->commandargs[ias]),
					string_dup(con_num(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->commandargs[ias], "$$"))
		{
			str_rep(&(info->commandargs[ias]),
					string_dup(con_num(getpid(), 10, 0)));
			continue;
		}
		node = node_start(info->env, &info->commandargs[ias][1], '=');
		if (node)
		{
			str_rep(&(info->commandargs[ias]),
					string_dup(string_chr(node->string, '=') + 1));
			continue;
		}
		str_rep(&info->commandargs[ias], string_dup(""));

	}
	return (0);
}

/**
 * str_rep - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int str_rep(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}


