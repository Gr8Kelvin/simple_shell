#include "shell.h"

/**
 * string_cpy - copies string
 * @dest: destination
 * @src: source
 * Return: pointer
 */
char *string_copy(char *dest, char *src)
{
	int ias = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[ias])
	{
		dest[ias] = src[ias];
		ias++;
	}
	dest[ias] = 0;
	return (dest);
}

/**
 * string_dup - duplicates str
 * @str: str to duplicate
 * Return: pointer to duplicated str
 */
char *string_dup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 * print_s - prints input str
 * @str: str to print
 * Return: Nothing
 */
void print_s(char *str)
{
	int ias = 0;

	if (!str)
		return;
	while (str[ias] != '\0')
	{
		print_ch(str[ias]);
		ias++;
	}
}

/**
 * print_ch - writes character to stdout
 * @c: character to print
 * Return: success 1, on error -1
 */
int print_ch(char c)
{
	static int ias;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ias >= WRITE_BUF_SIZE)
	{
		write(1, buf, ias);
		ias = 0;
	}
	if (c != BUF_FLUSH)
		buf[ias++] = c;
	return (1);
}


