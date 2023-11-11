#include "shell.h"

/**
 * get_hist - gets history file
 * @info: a pointer
 * Return: a string
 */

char *get_hist(inform_t *info)
{
	char *buff, *dird;

	dird = disp_env(info, "HOME=");
	if (!dird)
		return (NULL);
	buff = malloc(sizeof(char) * (len_str(dird) + len_str(history_file) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	string_copy(buff, dird);
	str_cat(buff, "/");
	str_cat(buff, history_file);
	return (buff);
}

/**
 * write_hist - creates a new file
 * @info: a pointer
 * Return: 1 on success, otherwise -1
 */
int write_hist(inform_t *info)
{
	ssize_t fdhr;
	char *le_name = get_hist(info);
	list_string *node = NULL;

	if (!le_name)
		return (-1);

	fdhr = open(le_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(le_name);
	if (fdhr == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		print_sfd(node->strn, fdhr);
		print_fd('\n', fdhr);
	}
	print_fd(BUFF_FLUSH, fdhr);
	close(fdhr);
	return (1);
}

/**
 * read_hist - reads history
 * @info: pointer
 * Return: historycount otherwise 0
 */
int read_hist(inform_t *info)
{
	int ihr, hast = 0, linecount = 0;
	ssize_t fdhr, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *file_name = get_hist(info);

	if (!file_name)
		return (0);

	fdhr = open(file_name, O_RDONLY);
	free(file_name);
	if (fdhr == -1)
		return (0);
	if (!fstat(fdhr, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fdhr, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fdhr);
	for (ihr = 0; ihr < fsize; ihr++)
		if (buff[ihr] == '\n')
		{
			buff[ihr] = 0;
			build_hist(info, buff + hast, linecount++);
			hast = ihr + 1;
		}
	if (hast != ihr)
		build_hist(info, buff + hast, linecount++);
	free(buff);
	info->historycount = linecount;
	while (info->historycount-- >= history_max)
		rmv_node(&(info->history), 0);
	order_hist(info);
	return (info->historycount);
}

/**
 * build_hist - adds new entry to a history
 * @info: a pointer
 * @buff: buffer
 * @linecount: the history linecount
 * Return: always 0
 */
int build_hist(inform_t *info, char *buff, int linecount)
{
	list_string *node = NULL;

	if (info->history)
		node = info->history;
	nodeend_add(&node, buff, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * order_hist - orders the history
 * @info: a pointer
 * Return: the new historycount
 */
int order_hist(inform_t *info)
{
	list_string *node = info->history;
	int ihr = 0;

	while (node)
	{
		node->number = ihr++;
		node = node->next;
	}
	return (info->historycount = ihr);
}

