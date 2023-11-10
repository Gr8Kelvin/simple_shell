#include "shell.h"

/**
 * inte - returns true
 * @info: struct address
 * Return: 1 if inte mode otherwise 0
 */
int inte(inform_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * deli - checks character
 * @c: the character to check
 * @delim: deli string
 * Return: 1 if true, 0 if false
 */
int deli(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * alphabet - checks alphabetic character
 * @c: input character
 * Return: 1 if  alphabetic  otherwise 0
 */

int alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * at - converts a string
 * @s: the string
 * Return: 0 otherwise
 */

int at(char *s)
{
	int ias, sg = 1, fg = 0, out;
	unsigned int res = 0;

	for (ias = 0; s[ias] != '\0' && fg != 2; ias++)
	{
		if (s[ias] == '-')
			sg *= -1;

		if (s[ias] >= '0' && s[ias] <= '9')
		{
			fg = 1;
			res *= 10;
			res += (s[ias] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sg == -1)
		out = -res;
	else
		out = res;

	return (out);
}


