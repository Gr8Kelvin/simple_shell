#include "shell.h"

/**
 **string_cpy - copy of a string
 *@dest: string to copy to
 *@src:  string
 *@nhr: characters to be copied
 *Return: the concatenated string
 */
char *string_cpy(char *dest, char *src, int nhr)
{
	int ihr, jhr;
	char *shr = dest;

	ihr = 0;
	while (src[ihr] != '\0' && ihr < nhr - 1)
	{
		dest[ihr] = src[ihr];
		ihr++;
	}
	if (ihr < nhr)
	{
		jhr = ihr;
		while (jhr < nhr)
		{
			dest[jhr] = '\0';
			jhr++;
		}
	}
	return (shr);
}

/**
 **string_cat - concatenates strings
 *@dest: first string
 *@src: second string
 *@nhr: bytes to be used
 *Return: the concatenated string
 */
char *string_cat(char *dest, char *src, int nhr)
{
	int ihr, jhr;
	char *shr = dest;

	ihr = 0;
	jhr = 0;
	while (dest[ihr] != '\0')
		ihr++;
	while (src[jhr] != '\0' && jhr < nhr)
	{
		dest[ihr] = src[jhr];
		ihr++;
		jhr++;
	}
	if (jhr < nhr)
		dest[ihr] = '\0';
	return (shr);
}

/**
 **string_chr - character in a string
 *@strn: string
 *@c: character
 *Return: pointer
 */
char *string_chr(char *strn, char c)
{
	do {
		if (*strn == c)
			return (strn);
	} while (*strn++ != '\0');

	return (NULL);
}

