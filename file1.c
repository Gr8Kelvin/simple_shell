#include "shell.h"

/**
 * hash - main shell
 * @info: parameter & info struct
 * @avs: argument vector mai
 * Return: 0 success, 1 error,
 */
int hash(inform_t *info, char **avs)
{
	ssize_t res = 0;
	int build_ret = 0;

	while (res != -1 && build_ret != -2)
	{
		del_info(info);
		if (inte(info))
			print_s("$ ");
		print_char(BUF_FLUSH);
		res = get_inp(info);
		if (res != -1)
		{
			put_info(info, avs);
			build_ret = fd_build(info);
			if (build_ret == -1)
				fd_command(info);
		}
		else if (inte(info))
			print_ch('\n');
		release_info(info, 0);
	}
	write_hist(info);
	release_info(info, 1);
	if (!inte(info) && info->status)
		exit(info->status);
	if (build_ret == -2)
	{
		if (info->errorcode == -1)
			exit(info->status);
		exit(info->errorcode);
	}
	return (build_ret);
}

/**
 * fd_build - find build command
 * @info: parameter & return struct
 * Return: -1, 0, 1 if not successful, 2 if exit()
 */
int fd_build(inform_t *info)
{
	int ias, build_ret = -1;
	build_table buildtbl[] = {
		{"exit", customexit},
		{"env", get_env},
		{"help", customhelp},
		{"history", dis_hist},
		{"setenv", set_env},
		{"unsetenv", rmv_env},
		{"cd", customcd},
		{"alias", dis_alias},
		{NULL, NULL}
	};

	for (ias = 0; buildtbl[ias].type; ias++)
		if (str_cmp(info->commandargs[0], buildtbl[ias].type) == 0)
		{
			info->line_count++;
			build_ret = buildtbl[ias].func(info);
			break;
		}
	return (build_ret);
}

/**
 * fd_command - find command PATH
 * @info: parameter & return struct
 * Return: void
 */
void fd_command(inform_t *info)
{
	char *commandpath = NULL;
	int ias, kew;

	info->commandpath = info->commandargs[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (ias = 0, kew = 0; info->commandname[ias]; ias++)
		if (!deli(info->commandname[ias], " \t\n"))
			kew++;
	if (!kew)
		return;

	commandpath = fd_path(info, disp_env(info, "PATH="), info->commandargs[0]);
	if (commandpath)
	{
		info->commandpath = commandpath;
		fk_command(info);
	}
	else
	{
		if ((inte(info) || disp_env(info, "PATH=")
					|| info->commandargs[0][0] == '/')
				&& id_command(info, info->commandargs[0]))
			fk_command(info);
		else if (*(info->commandname) != '\n')
		{
			info->status = 127;
			prt_err(info, "not found\n");
		}
	}
}

/**
 * fk_command - forks exec thread
 * @info: parameter & return struct
 * Return: void
 */
void fk_command(inform_t *info)
{
	pid_t kid_pid;

	kid_pid = fork();
	if (kid_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (kid_pid == 0)
	{
		if (execve(info->commandpath, info->commandargs, get_envir(info)) == -1)
		{
			release_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				prt_err(info, "Permission denied\n");
		}
	}
}


