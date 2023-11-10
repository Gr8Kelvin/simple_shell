#include "shell.h"

/**
 * get_hist - gets the history file
 * @info: parameter struc
 * Return: allocated string
 */

char *get_hist(inform_t *info)
{
	char *bufd, *dird;

	dird = disp_env(info, "HOME=");
	if (!dird)
		return (NULL);
	bufd = malloc(sizeof(char) * (len_str(dird) + len_str(HISTORY_FILE) + 2));
	if (!bufd)
		return (NULL);
	bufd[0] = 0;
	string_copy(bufd, dird);
	str_cat(bufd, "/");
	str_cat(bufd, HISTORY_FILE);
	return (bufd);
}

/**
 * write_hist - creates a file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_hist(inform_t *info)
{
	ssize_t fdd;
	char *filename = get_hist(info);
	list_string *node = NULL;

	if (!filename)
		return (-1);

	fdd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		print_sfd(node->string, fdd);
		print_fd('\n', fdd);
	}
	print_fd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_hist - reads history from file
 * @info: the parameter struct
 * Return: historycount on success otherwise 0
 */
int read_hist(inform_t *info)
{
	int ias, last = 0, linecnt = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist(info);

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
			build_hist(info, buf + last, linecnt++);
			last = ias + 1;
		}
	if (last != ias)
		build_hist(info, buf + last, linecnt++);
	free(buf);
	info->historycount = linecnt;
	while (info->historycount-- >= HISTORY_MAX)
		rmv_node(&(info->history), 0);
	order_hist(info);
	return (info->historycount);
}

/**
 * build_hist - it adds data to history  list
 * @info: contains  arguments
 * @buf: buffer
 * @linecount: the history linecount, historycount
 * Return: Always 0
 */
int build_hist(inform_t *info, char *buf, int linecount)
{
	list_string *node = NULL;

	if (info->history)
		node = info->history;
	nodeend_add(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * order_hist - orders the history list
 * @info:  contains arguments.
 * Return: the new historycount
 */
int order_hist(inform_t *info)
{
	list_string *node = info->history;
	int ias = 0;

	while (node)
	{
		node->number = ias++;
		node = node->next;
	}
	return (info->historycount = ias);
}


