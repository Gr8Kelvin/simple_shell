#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struc
 * Return: allocated string
 */

char *get_history_file(inform_t *info)
{
	char *bufd, *dird;

	dir = disp_env(info, "HOME=");
	if (!dird)
		return (NULL);
	bufd = malloc(sizeof(char) * (len_str(dird) + len_str(HIST_FILE) + 2));
	if (!bufd)
		return (NULL);
	bufd[0] = 0;
	str_cpy(bufd, dird);
	str_cat(bufd, "/");
	str_cat(bufd, HIST_FILE);
	return (bufd);
}

/**
 * write_history - creates a file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(inform_t *info)
{
	ssize_t fdd;
	char *filename = get_history_file(info);
	list_string *node = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		print_sfd(node->str, fdd);
		print_fd('\n', fdd);
	}
	print_fd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 * Return: historycount on success otherwise 0
 */
int read_history(inform_t *info)
{
	int ias, last = 0, linecnt = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (ias = 0; ias < fsize; ias++)
		if (buf[ias] == '\n')
		{
			buf[ias] = 0;
			build_history_list(info, buf + last, linecnt++);
			last = ias + 1;
		}
	if (last != ias)
		build_history_list(info, buf + last, linecnt++);
	free(buf);
	info->historycount = linecnt;
	while (info->historycount-- >= HIST_MAX)
		rmv_node(&(info->history), 0);
	renumber_history(info);
	return (info->historycount);
}

/**
 * build_history_list - it adds entry to history linked list
 * @info: Structure containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, historycount
 * Return: Always 0
 */
int build_history_list(inform_t *info, char *buf, int linecount)
{
	list_string *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments.
 * Return: the new historycount
 */
int renumber_history(inform_t *info)
{
	list_string *node = info->history;
	int ias = 0;

	while (node)
	{
		node->num = ias++;
		node = node->next;
	}
	return (info->historycount = ias);
}

