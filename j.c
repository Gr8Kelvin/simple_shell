#include "shell.h"

/**
 * input_buf - buffer
 * @info: pointer
 * @buff: memory location
 * @len: memory location
 * Return: the bytes read
 */
ssize_t input_buf(inform_t *info, char **buff, size_t *len)
{
	ssize_t resut = 0;
	size_t len_phr = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, inthand);
#if USEget_line
		resut = getline(buff, &len_phr, stdin);
#else
		resut = get_line(info, buff, &len_phr);
#endif
		if (resut > 0)
		{
			if ((*buff)[resut - 1] == '\n')
			{
				(*buff)[resut - 1] = '\0';
				resut--;
			}
			info->linecount_error = 1;
			rmv_comments(*buff);
			build_hist(info, *buff, info->historycount++);
			{
				*len = resut;
				info->commandbuffer = buff;
			}
		}
	}
	return (resut);
}

/**
 * get_inp - gets a line of string
 * @info: pointer
 * Return: the bytes
 */
ssize_t get_inp(inform_t *info)
{
	static char *buff;
	static size_t ihr, jhr, len;
	ssize_t resut = 0;
	char **buff_ptr = &(info->commandname), *ptr;

	print_ch(BUFF_FLUSH);
	resut = input_buf(info, &buff, &len);
	if (resut == -1)
		return (-1);
	if (len)
	{
		jhr = ihr;
		ptr = buff + ihr;

		ck_chn(info, buff, &jhr, ihr, len);
		while (jhr < len)
		{
			if (is_chn(info, buff, &jhr))
				break;
			jhr++;
		}

		ihr = jhr + 1;
		if (ihr >= len)
		{
			ihr = len = 0;
			info->commandtype = CMD_NORM;
		}

		*buff_ptr = ptr;
		return (len_str(ptr));
	}

	*buff_ptr = buff;
	return (resut);
}

/**
 * read_buf - reads the content
 * @info: pointer
 * @buff: memory location
 * @ihr: size of buffer
 * Return: r
 */
ssize_t read_buf(inform_t *info, char *buff, size_t *ihr)
{
	ssize_t resut = 0;

	if (*ihr)
		return (0);
	resut = read(info->readfd, buff, READ_BUFF_SIZE);
	if (resut >= 0)
		*ihr = resut;
	return (resut);
}

/**
 * get_line - next line of string
 * @info: pointer
 * @ptrh: memory location
 * @leng: the size
 * Return: the string
 */
int get_line(inform_t *info, char **ptrh, size_t *leng)
{
	static char buff[READ_BUFF_SIZE];
	static size_t ihr, len;
	size_t khr;
	ssize_t result = 0, shr = 0;
	char *old_ptr = NULL, *new_ptr = NULL, *chr;

	old_ptr = *ptrh;
	if (old_ptr && leng)
		shr = *leng;
	if (ihr == len)
		ihr = len = 0;

	result = read_buf(info, buff, &len);
	if (result == -1 || (result == 0 && len == 0))
		return (-1);

	chr = string_chr(buff + ihr, '\n');
	khr = chr ? 1 + (unsigned int)(chr - buff) : len;
	new_ptr = real(old_ptr, shr, shr ? shr + khr : khr + 1);
	if (!new_ptr)
		return (old_ptr ? free(old_ptr), -1 : -1);

	if (shr)
		string_cat(new_ptr, buff + ihr, khr - ihr);
	else
		string_cpy(new_ptr, buff + ihr, khr - ihr + 1);

	shr += khr - ihr;
	ihr = khr;
	old_ptr = new_ptr;

	if (leng)
		*leng = shr;
	*ptrh = old_ptr;
	return (shr);
}

/**
 * inthand - stops operation
 * @sig_num: the signal
 * Return: void
 */
void inthand(__attribute__((unused))int sig_num)
{
	print_s("\n");
	print_s("$ ");
	print_ch(BUFF_FLUSH);
}

