#include "shell.h"

/**
 * input_buf - buffers
 * @info: parameter struct
 * @buf: address
 * @lenn: address
 * Return: bytes read
 */
ssize_t input_buf(inform_t *info, char **buf, size_t *lenn)
{
	ssize_t rn = 0;
	size_t lenn_pn = 0;

	if (!*lenn)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, inthand);
#if USEget_line
		rn = getline(buf, &lenn_pn, stdin);
#else
		rn = get_line(info, buf, &lenn_pn);
#endif
		if (rn > 0)
		{
			if ((*buf)[rn - 1] == '\n')
			{
				(*buf)[rn - 1] = '\0';
				rn--;
			}
			info->linecount_flag = 1;
			rmv_com(*buf);
			build_history_list(info, *buf, info->historycount++);
			{
				*lenn = rn;
				info->commandbuffer = buf;
			}
		}
	}
	return (rn);
}

/**
 * get_inp - gets a line
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_inp(inform_t *info)
{
	static char *buf;
	static size_t ias, jas, len;
	ssize_t rn = 0;
	char **buf_p = &(info->commandname), *p;

	print_ch(BUF_FLUSH);
	rn = input_buf(info, &buf, &len);
	if (rn == -1)
		return (-1);
	if (len)
	{
		jas = ias;
		p = buf + ias;

		chk_chn(info, buf, &jas, ias, len);
		while (jas < len)
		{
			if (chown(info, buf, &jas))
				break;
			jas++;
		}

		ias = jas + 1;
		if (ias >= len)
		{
			ias = len = 0;
			info->commandtype = CMD_NORM;
		}

		*buf_p = p;
		return (len_str(p));
	}

	*buf_p = buf;
	return (rn);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @in: size
 * Return: rn
 */
ssize_t read_buf(inform_t *info, char *buf, size_t *in)
{
	ssize_t rn = 0;

	if (*in)
		return (0);
	rn = read(info->readfd, buf, READ_BUF_SIZE);
	if (rn >= 0)
		*in = rn;
	return (rn);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter
 * @ptr: pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer
 * Return: sn
 */
int get_line(inform_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t ias, len;
	size_t kas;
	ssize_t rn = 0, sn = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		sn = *length;
	if (ias == len)
		ias = len = 0;

	rn = read_buf(info, buf, &len);
	if (rn == -1 || (rn == 0 && len == 0))
		return (-1);

	c = str_chr(buf + ias, '\n');
	kas = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = real(p, sn, sn ? sn + kas : kas + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (sn)
		strn_cat(new_p, buf + ias, kas - ias);
	else
		strn_cpy(new_p, buf + ias, kas - ias + 1);

	sn += kas - ias;
	ias = kas;
	p = new_p;

	if (length)
		*length = sn;
	*ptr = p;
	return (sn);
}

/**
 * int_hand - blocks ctrl-C
 * @sig_num: signal number
 * Return: void
 */
void int_hand(__attribute__((unused))int sig_num)
{
	print_s("\n");
	print_s("$ ");
	print_ch(BUF_FLUSH);
}

