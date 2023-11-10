#include "shell.h"

/**
 * del_info - initializes inform_t struct
 * @info: struct address
 */
void del_info(inform_t *info)
{
	info->commandname = NULL;
	info->commandargs = NULL;
	info->commandpath = NULL;
	info->numargs = 0;
}

/**
 * put_info - initializes inform_t struct
 * @info: struct address
 * @av: argument vector
 */
void put_info(inform_t *info, char **av)
{
	int ias = 0;

	info->fnanme = av[0];
	if (info->commandname)
	{
		info->commandargs = strt_ow(info->commandname, " \t");
		if (!info->commandargs)
		{
			info->commandargs = malloc(sizeof(char *) * 2);
			if (info->commandargs)
			{
				info->commandargs[0] = string_dup(info->commandname);
				info->commandargs[1] = NULL;
			}
		}
		for (ias = 0; info->commandargs && info->commandargs[ias]; ias++)
			;
		info->numargs = ias;

		als_rep(info);
		var_rep(info);
	}
}

/**
 * release_info - frees inform_t struct fields
 * @info: struct address
 * @all: true ifree_fing all fields
 */
void release_info(inform_t *info, int all)
{
	free_f(info->commandargs);
	info->commandargs = NULL;
	info->commandpath = NULL;
	if (all)
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
		print_ch(BUF_FLUSH);
	}
}


