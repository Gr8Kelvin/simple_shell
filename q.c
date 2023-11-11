#include "shell.h"

/**
 * id_command - checks if executable
 * @info: a pointer
 * @commandpath: commandpath to the file
 * Return: 1, 0
 */
int id_command(inform_t *info, char *commandpath)
{
	struct stat st;

	(void)info;
	if (!commandpath || stat(commandpath, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * d_char - duplicates characters
 * @pathstr: path to the string
 * @start: starting ind
 * @stop: stopping inde
 * Return: pointer
 */
char *d_char(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int ihr = 0, jhr = 0;

	for (jhr = 0, ihr = start; ihr < stop; ihr++)
		if (pathstr[ihr] != ':')
			buff[jhr++] = pathstr[ihr];
	buff[jhr] = 0;
	return (buff);
}

/**
 * fd_path - finds the path
 * @info: pointer
 * @pathstr: the string
 * @cmd: the command to find
 * Return: full path of cmd if found or NULL
 */
char *fd_path(inform_t *info, char *pathstr, char *cmd)
{
	unsigned int ihr = 0, cuhrr_pos = 0;
	char *commandpath;

	if (!pathstr)
		return (NULL);
	if ((len_str(cmd) > 2) && sts_wt(cmd, "./"))
	{
		if (id_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[ihr] || pathstr[ihr] == ':')
		{
			commandpath = d_char(pathstr, cuhrr_pos, ihr);
			if (!*commandpath)
				str_cat(commandpath, cmd);
			else
			{
				str_cat(commandpath, "/");
				str_cat(commandpath, cmd);
			}
			if (id_command(info, commandpath))
				return (commandpath);
			if (!pathstr[ihr])
				break;
			cuhrr_pos = ihr;
		}
		ihr++;
	}
	return (NULL);
}

