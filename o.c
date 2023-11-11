#include "shell.h"

/**
 * shs - starts the main shell
 * @info: a pointer
 * @avhr: the argument vector
 * Return: 0, 1, error code
 */
int shs(inform_t *info, char **avhr)
{
	ssize_t rhr = 0;
	int builtin_ret = 0;

	while (rhr != -1 && builtin_ret != -2)
	{
		del_info(info);
		if (inte(info))
			print_s("$ ");
		print_char(BUFF_FLUSH);
		rhr = get_inp(info);
		if (rhr != -1)
		{
			put_info(info, avhr);
			builtin_ret = fd_build(info);
			if (builtin_ret == -1)
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
	if (builtin_ret == -2)
	{
		if (info->errorcode == -1)
			exit(info->status);
		exit(info->errorcode);
	}
	return (builtin_ret);
}

/**
 * fd_build - build command
 * @info: a pointer
 * Return: -1, 0, 1, 2
 */
int fd_build(inform_t *info)
{
	int ihr, built_in_ret = -1;
	build_table builtintbl[] = {
		{"cd", customcd},
		{"alias", dis_als},
		{"help", customhelp},
		{"history", dis_hist},
		{"env", get_env},
		{"setenv", set_env},
		{"unsetenv", rmv_env},
		{"exit", customexit},
		{NULL, NULL}
	};

	for (ihr = 0; builtintbl[ihr].type; ihr++)
		if (str_cmp(info->commandargs[0], builtintbl[ihr].type) == 0)
		{
			info->linecount++;
			built_in_ret = builtintbl[ihr].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * fd_command - finds command
 * @info: the parameter
 * Return: void
 */
void fd_command(inform_t *info)
{
	char *commandpath = NULL;
	int ihr, khr;

	info->commandpath = info->commandargs[0];
	if (info->linecount_error == 1)
	{
		info->linecount++;
		info->linecount_error = 0;
	}
	for (ihr = 0, khr = 0; info->commandname[ihr]; ihr++)
		if (!deli(info->commandname[ihr], " \t\n"))
			khr++;
	if (!khr)
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
					|| info->commandargs[0][0] == '/') && id_command(info, info->commandargs[0]))
			fk_command(info);
		else if (*(info->commandname) != '\n')
		{
			info->status = 127;
			prt_err(info, "not found\n");
		}
	}
}

/**
 * fk_command - forks an execution
 * @info: a pointer
 */
void fk_command(inform_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
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
				prt_err(info, "You are not authorized!\n");
		}
	}
}

