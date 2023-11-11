#include "shell.h"

/**
 * inte - if shell is in inte mode
 * @info: pointer
 * Return: 1, if in inte mode, 0 if otherwise
 */
int inte(inform_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * deli -  if c is a delimeter
 * @chr: character
 * @denlim: a pointer
 * Return: 1 if true, 0 if false
 */
int deli(char chr, char *denlim)
{
	while (*denlim)
		if (*denlim++ == chr)
			return (1);
	return (0);
}

/**
 * alphabet - if a character is an alphabet
 * @chr: the input character
 * Return: 1 , 0 if otherwise
 */
int alphabet(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * toi - converts string to integer
 * @strn: the string
 * Return: 0 if no numbers in string
 */
int toi(char *strn)
{
	int ias, signd = 1, fulag = 0, output;
	unsigned int res = 0;

	for (ias = 0; strn[ias] != '\0' && fulag != 2; ias++)
	{
		if (strn[ias] == '-')
			signd *= -1;

		if (strn[ias] >= '0' && strn[ias] <= '9')
		{
			fulag = 1;
			res *= 10;
			res += (strn[ias] - '0');
		}
		else if (fulag == 1)
			fulag = 2;
		else
			break;
	}

	if (signd == -1)
		output = -res;
	else
		output = res;

	return (output);
}

