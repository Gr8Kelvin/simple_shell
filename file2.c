#include "shell.h"

/**
 * len_str - returns the length
 * @s: string to check
 * Return: length of string
 */
int len_str(char *s)
{
	int ias = 0;

	if (!s)
		return (0);

	while (*s++)
		ias++;
	return (ias);
}

/**
 * str_cmp - lexi comparison.
 * @s1: first str
 * @s2: second str
 * Return: - if s1 < s2, + if s1 > s2, 0 if s1 == s2
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * sts_wt - checks needle
 * @hays: string to search
 * @need: substring
 * Return: address of next char or NULL
 */
char *sts_wt(const char *hays, const char *need)
{
	while (*need)
		if (*need++ != *hays++)
			return (NULL);
	return ((char *)hays);
}

/**
 * str_cat - concatenation of two strings
 * @dest: destination buff
 * @src: source buff
 * Return: pointer
 */
char *str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

