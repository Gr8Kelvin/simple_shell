#include "shell.h"

/**
 * err_at - converts a string
 * @sd: the string
 * Return: 0 , otherwise -1
 */
int err_at(char *sd)
{
	int ias = 0;
	unsigned long int res = 0;

	if (*sd == '+')
		sd++;
	for (ias = 0;  sd[ias] != '\0'; ias++)
	{
		if (sd[ias] >= '0' && sd[ias] <= '9')
		{
			res *= 10;
			res += (sd[ias] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * prt_err - prints error
 * @info: parameter & info struct
 * @estrg: string
 * Return: 0 , -1 error
 */
void prt_err(inform_t *info, char *estrg)
{
	print_str(info->fnanme);
	print_str(": ");
	prt_d(info->line_count, STDERR_FILENO);
	print_str(": ");
	print_str(info->commandargs[0]);
	print_str(": ");
	print_str(estrg);
}

/**
 * prt_d - function prints a decimal
 * @input: the input
 * @fds: file descriptor
 * Return: characters printed
 */
int prt_d(int input, int fds)
{
	int (*_print_ch)(char) = print_ch;
	int ias, cnt = 0;
	unsigned int _abs_, current;

	if (fds == STDERR_FILENO)
		_print_ch = print_char;
	if (input < 0)
	{
		_abs_ = -input;
		_print_ch('-');
		cnt++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (ias = 1000000000; ias > 1; ias /= 10)
	{
		if (_abs_ / ias)
		{
			_print_ch('0' + current / ias);
			cnt++;
		}
		current %= ias;
	}
	_print_ch('0' + current);
	cnt++;

	return (cnt);
}

/**
 * con_num - converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *con_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sg = 0;
	char *ptr;
	unsigned long nas = num;

	if (!(flags & CON_UNSIGNED) && num < 0)
	{
		nas = -num;
		sg = '-';

	}
	array = flags & CON_LOWERCASE ? "0123456789abcdef" :
		"0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[nas % base];
		nas /= base;
	} while (nas != 0);

	if (sg)
		*--ptr = sg;
	return (ptr);
}

/**
 * rmv_com - replaces first instance of '#' with '\0'
 * @buf: address of the string
 * Return: Always 0;
 */
void rmv_com(char *buf)
{
	int ias;

	for (ias = 0; buf[ias] != '\0'; ias++)
		if (buf[ias] == '#' && (!ias || buf[ias - 1] == ' '))
		{
			buf[ias] = '\0';
			break;
		}
}

