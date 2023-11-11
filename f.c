#include "shell.h"

/**
 * err_at - converts string
 * @strn: the strning
 * Return: number, 0 , else -1 on error
 */
int err_at(char *strn)
{
	int ihr = 0;
	unsigned long int result = 0;

	if (*strn == '+')
		strn++;
	for (ihr = 0;  strn[ihr] != '\0'; ihr++)
	{
		if (strn[ihr] >= '0' && strn[ihr] <= '9')
		{
			result *= 10;
			result += (strn[ihr] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * prt_err - error message
 * @info: pointer
 * @estrn: a string
 */
void prt_err(inform_t *info, char *estrn)
{
	print_str(info->fname);
	print_str(": ");
	prt_d(info->linecount, STDERR_FILENO);
	print_str(": ");
	print_str(info->commandargs[0]);
	print_str(": ");
	print_str(estrn);
}

/**
 * prt_d - prints an integer
 * @input: int
 * @fd: the file
 * Return: the number
 */
int prt_d(int input, int fdhr)
{
	int (*_print_ch)(char) = print_ch;
	unsigned int ihr;
	int counter = 0;
	unsigned int abs_val, curt;

	if (fdhr == STDERR_FILENO)
		_print_ch = print_char;
	if (input < 0)
	{
		abs_val = -input;
		_print_ch('-');
		counter++;
	}
	else
		abs_val = input;
	curt = abs_val;
	for (ihr = 1000000000; ihr > 1; ihr /= 10)
	{
		if (abs_val / ihr)
		{
			_print_ch('0' + curt / ihr);
			counter++;
		}
		curt %= ihr;
	}
	_print_ch('0' + curt);
	counter++;

	return (counter);
}

/**
 * con_num - converts
 * @number: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *con_num(long int number, int base, int flags)
{
	static char *array;
	static char buff[50];
	char sgn = 0;
	char *ptr;
	unsigned long nhr = number;

	if (!(flags & CON_UNSIGNED) && number < 0)
	{
		nhr = -number;
		sgn = '-';

	}
	array = flags & CON_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = array[nhr % base];
		nhr /= base;
	} while (nhr != 0);

	if (sgn)
		*--ptr = sgn;
	return (ptr);
}

/**
 * rmv_comments - replaces `#` with `\0`
 * @buff: a pointer
 * Return: Always 0;
 */
void rmv_comments(char *buff)
{
	unsigned int ihr;

	for (ihr = 0; buff[ihr] != '\0'; ihr++)
		if (buff[ihr] == '#' && (!ihr || buff[ihr - 1] == ' '))
		{
			buff[ihr] = '\0';
			break;
		}
}

