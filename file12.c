#include "shell.h"

/**
 **string_cpy - copies string
 *@dest: destination string
 *@src: the source string
 *@nds: number of characters
 *Return: the concatenated string
 */
char *string_cpy(char *dest, char *src, int nds)
{
	int ias, jas;
	char *sd = dest;

	ias = 0;
	while (src[ias] != '\0' && ias < nds - 1)
	{
		dest[ias] = src[ias];
		ias++;
	}
	if (ias < nds)
	{
		jas = ias;
		while (jas < nds)
		{
			dest[jas] = '\0';
			jas++;
		}
	}
	return (sd);
}

/**
 **string_cat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@nds:  bytes to be maximally used
 *Return: the concatenated string
 */
char *string_cat(char *dest, char *src, int nds)
{
	int ias, jas;
	char *sd = dest;

	ias = 0;
	jas = 0;
	while (dest[ias] != '\0')
		ias++;
	while (src[jas] != '\0' && jas < nds)
	{
		dest[ias] = src[jas];
		ias++;
		jas++;
	}
	if (jas < nds)
		dest[ias] = '\0';
	return (sd);
}

/**
 **string_chr - locates a character
 *@sd: string to be parsed
 *@cd: the character
 *Return: (s) a pointer
 */
char *string_chr(char *sd, char cd)
{
	do {
		if (*sd == cd)
			return (sd);
	} while (*sd++ != '\0');

	return (NULL);
}

