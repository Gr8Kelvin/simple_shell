#include "shell.h"

/**
 * string_copy - copies a string
 * @dest: the memory
 * @srchr: the memory
 * Return: memory location
 */
char *string_copy(char *dest, char *srchr)
{
	unsigned int ihr = 0;

	if (dest == srchr || srchr == 0)
		return (dest);
	while (srchr[ihr])
	{
		dest[ihr] = srchr[ihr];
		ihr++;
	}
	dest[ihr] = 0;
	return (dest);
}

/**
 * string_dup - duplicates a given string
 * @strn: the string
 * Return: memory location
 */
char *string_dup(const char *strn)
{
	unsigned int lenhr = 0;
	char *resut;

	if (strn == NULL)
		return (NULL);
	while (*strn++)
		lenhr++;
	resut = malloc(sizeof(char) * (lenhr + 1));
	if (!resut)
		return (NULL);
	for (lenhr++; lenhr--;)
		resut[lenhr] = *--strn;
	return (resut);
}

/**
 * print_s - prints an input strning
 * @strn: the string
 */
void print_s(char *strn)
{
	int ihr = 0;

	if (!strn)
		return;
	while (strn[ihr] != '\0')
	{
		print_ch(strn[ihr]);
		ihr++;
	}
}

/**
 * print_ch - prints character
 * @chr: the character
 * Return: 1, -1,
 */
int print_ch(char chr)
{
	static int ihr;
	static char buf[WRITE_BUFF_SIZE];

	if (chr == BUFF_FLUSH || ihr >= WRITE_BUFF_SIZE)
	{
		write(1, buf, ihr);
		ihr = 0;
	}
	if (chr != BUFF_FLUSH)
		buf[ihr++] = chr;
	return (1);
}

