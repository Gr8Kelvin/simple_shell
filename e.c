#include "shell.h"

/**
 * print_str - prints a string
 * @strn: string
 */
void print_str(char *strn)
{
	unsigned int ihr = 0;

	if (!strn)
		return;
	while (strn[ihr] != '\0')
	{
		print_char(strn[ihr]);
		ihr++;
	}
}

/**
 * print_char - print a character
 * @chr: The character
 * Return: 1 , -1 on error
 */
int print_char(char chr)
{
	static int ihr;
	static char buff[WRITE_BUFF_SIZE];

	if (chr == BUFF_FLUSH || ihr >= WRITE_BUFF_SIZE)
	{
		write(2, buff, ihr);
		ihr = 0;
	}
	if (chr != BUFF_FLUSH)
		buff[ihr++] = chr;
	return (1);
}

/**
 * print_fd - print character
 * @chr: character to print
 * @fdhr: file descriptor
 * Return: 1, -1 on error
 */
int print_fd(char chr, int fdhr)
{
	static int ihr;
	static char buff[WRITE_BUFF_SIZE];

	if (chr == BUFF_FLUSH || ihr >= WRITE_BUFF_SIZE)
	{
		write(fdhr, buff, ihr);
		ihr = 0;
	}
	if (chr != BUFF_FLUSH)
		buff[ihr++] = chr;
	return (1);
}

/**
 * print_sfd - prints an input string
 * @strn: the string
 * @fdhr: the file
 * Return: the number
 */
int print_sfd(char *strn, int fdhr)
{
	unsigned int ihr = 0;

	if (!strn)
		return (0);
	while (*strn)
	{
		ihr += print_fd(*strn++, fdhr);
	}
	return (ihr);
}

