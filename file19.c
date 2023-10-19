#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 success, 1 error
 */
int main(int ac, char **av)
{
	inform_t info[] = { INFO_INIT };
	int fdew = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdew)
			: "r" (fdew));

	if (ac == 2)
	{
		fdew = open(av[1], O_RDONLY);
		if (fdew == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_str(av[0]);
				print_str(": 0: Can't open ");
				print_str(av[1]);
				print_char('\n');
				print_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdew;
	}
	pop_env(info);
	read_history(info);
	hash(info, av);
	return (EXIT_SUCCESS);
}


/**
 * free_b - frees a pointer and NULLs the address
 * @ptrds: pointer to free
 * Return: 1 ifree_fd, otherwise 0.
 */
int free_b(void **ptrds)
{
	if (ptrds && *ptrds)
	{
		free(*ptrds);
		*ptrds = NULL;
		return (1);
	}
	return (0);
}

/**
 * id_cmd - determines if a file is an executable command
 * @info: the info struct
 * @commandpath: path to the file
 * Return: 1 if true, 0 otherwise
 */
int id_cmd(inform_t *info, char *commandpath)
{
	struct stat stdd;

	(void)info;
	if (!commandpath || stat(commandpath, &stdd))
		return (0);

	if (stdd.stdd_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * d_char - duplication of characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *d_char(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int ias = 0, kas = 0;

	for (kas = 0, ias = start; ias < stop; ias++)
		if (pathstr[ias] != ':')
			buf[kas++] = pathstr[ias];
	buf[kas] = 0;
	return (buf);
}

/**
 * fd_pth - finds this cmd
 * @info: info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd or NULL
 */
char *fd_pth(inform_t *info, char *pathstr, char *cmd)
{
	int ias = 0, curr_pos = 0;
	char *commandpath;

	if (!pathstr)
		return (NULL);
	if ((len_str(cmd) > 2) && sts_wt(cmd, "./"))
	{
		if (id_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[ias] || pathstr[ias] == ':')
		{
			commandpath = d_char(pathstr, curr_pos, ias);
			if (!*commandpath)
				str_cat(commandpath, cmd);
			else
			{
				str_cat(commandpath, "/");
				str_cat(commandpath, cmd);
			}
			if (id_cmd(info, commandpath))
				return (path);
			if (!pathstr[ias])
				break;
			curr_pos = ias;
		}
		ias++;
	}
	return (NULL);
}

