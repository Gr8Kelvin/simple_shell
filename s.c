#include "shell.h"

/**
 * len_str - length of a string
 * @strn: the string
 * Return: the length
 */
int len_str(char *strn)
{
	unsigned int ihr = 0;

	if (!strn)
		return (0);

	while (*strn++)
		ihr++;
	return (ihr);
}

/**
 * str_cmp - compares two strings
 * @strn1: first string
 * @strn2: second string
 * Return: -, +, 0
 */
int str_cmp(char *strn1, char *strn2)
{
	while (*strn1 && *strn2)
	{
		if (*strn1 != *strn2)
			return (*strn1 - *strn2);
		strn1++;
		strn2++;
	}
	if (*strn1 == *strn2)
		return (0);
	else
		return (*strn1 < *strn2 ? -1 : 1);
}

/**
 * sts_wt - checks if needle haystack
 * @haystack: string
 * @needle: the substring
 * Return: memory location
 */
char *sts_wt(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str_cat - concatenates two strings
 * @dest: the memory location
 * @srchr: the memory location
 * Return: memory location to
 */
char *str_cat(char *dest, char *srchr)
{
	char *resut = dest;

	while (*dest)
		dest++;
	while (*srchr)
		*dest++ = *srchr++;
	*dest = *srchr;
	return (resut);
}

