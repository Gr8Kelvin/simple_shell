#include "shell.h"

/**
 * print_str - prints an input string
 * @str: the string
 * Return: Nothing
 */
void print_str(char *str)
{
	int ias = 0;

	if (!str)
		return;
	while (str[ias] != '\0')
	{
		print_char(str[ias]);
		ias++;
	}
}

/**
 * print_char - writes the character c to stderr
 * @ch: The character
 * Return: success 1. error -1 , and errno is set appropriately.
 */
int print_char(char ch)
{
	static int ias;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || ias >= WRITE_BUF_SIZE)
	{
		write(2, buf, ias);
		ias = 0;
	}
	if (ch != BUF_FLUSH)
		buf[ias++] = ch;
	return (1);
}

/**
 * print_fd - writes the character
 * @ch: The character
 * @fds: file descriptor
 * Return: success 1 error -1
 */
int print_fd(char ch, int fds)
{
	static int ias;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || ias >= WRITE_BUF_SIZE)
	{
		write(fds, buf, ias);
		ias = 0;
	}
	if (ch != BUF_FLUSH)
		buf[ias++] = ch;
	return (1);
}

/**
 * print_sfd - prints input string
 * @str: string
 * @fds: file descriptor
 * Return: number of chars
 */
int print_sfd(char *str, int fds)
{
	int ias = 0;

	if (!str)
		return (0);
	while (*str)
	{
		ias += print_fd(*str++, fds);
	}
	return (ias);
}

