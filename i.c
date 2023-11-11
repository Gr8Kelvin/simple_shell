#include "shell.h"

/**
 * del_info - delete
 * @info: pointer
 */
void del_info(inform_t *info)
{
	info->commandname = NULL;
	info->commandargs = NULL;
	info->commandpath = NULL;
	info->numargs = 0;
}

/**
 * put_info - initialize
 * @info: pointer
 * @av: pointer of arg vector
 */
void put_info(inform_t *info, char **av)
{
	unsigned int ihr = 0;

	info->fname = av[0];
	if (info->commandname)
	{
		info->commandargs = str_tow(info->commandname, " \t");
		if (!info->commandargs)
		{
			info->commandargs = malloc(sizeof(char *) * 2);
			if (info->commandargs)
			{
				info->commandargs[0] = string_dup(info->commandname);
				info->commandargs[1] = NULL;
			}
		}
		for (ihr = 0; info->commandargs && info->commandargs[ihr]; ihr++)
			;
		info->numargs = ihr;

		als_rep(info);
		var_rep(info);
	}
}

/**
 * release_info - clears
 * @info: pointer
 * @l_fields: tru
 */
void release_info(inform_t *info, int l_fields)
{
	free_f(info->commandargs);
	info->commandargs = NULL;
	info->commandpath = NULL;
	if (l_fields)
	{
		if (!info->commandbuffer)
			free(info->commandname);
		if (info->env)
			avail_list(&(info->env));
		if (info->history)
			avail_list(&(info->history));
		if (info->alias)
			avail_list(&(info->alias));
		free_f(info->envir);
		info->envir = NULL;
		free_b((void **)info->commandbuffer);
		if (info->readfd > 2)
			close(info->readfd);
		print_ch(BUFF_FLUSH);
	}
}

