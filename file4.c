#include "shell.h"

/**
 *strt_ow - splits a string
 * @str: input str
 * @d: delimeter string
 * Return: pointer of strings, or NULL
 */

char **strt_ow(char *str, char *d)
{
	int ias, jas, kas, mas, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (ias = 0; str[ias] != '\0'; ias++)
		if (!deli(str[ias], d) && (deli(str[ias + 1], d) || !str[ias + 1]))
			numw++;

	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ias = 0, jas = 0; jas < numw; jas++)
	{
		while (deli(str[ias], d))
			ias++;
		kas = 0;
		while (!deli(str[ias + kas], d) && str[ias + kas])
			kas++;
		s[jas] = malloc((kas + 1) * sizeof(char));
		if (!s[jas])
		{
			for (kas = 0; kas < jas; kas++)
				free(s[kas]);
			free(s);
			return (NULL);
		}
		for (mas = 0; mas < kas; mas++)
			s[jas][mas] = str[ias++];
		s[jas][mas] = 0;
	}
	s[jas] = NULL;
	return (s);
}

/**
 *strt_ow2 - splits string
 * @str: input str
 * @d:  delimeter
 * Return: a pointer to strings, or NULL
 */
char **strt_ow2(char *str, char d)
{
	int ias, jas, kas, mas, numw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (ias = 0; str[ias] != '\0'; ias++)
		if ((str[ias] != d && str[ias + 1] == d) ||
				(str[ias] != d && !str[ias + 1]) || str[ias + 1] == d)
			numw++;
	if (numw == 0)
		return (NULL);
	s = malloc((1 + numw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (ias = 0, jas = 0; jas < numw; jas++)
	{
		while (str[ias] == d && str[ias] != d)
			ias++;
		kas = 0;
		while (str[ias + kas] != d && str[ias + kas] && str[ias + kas] != d)
			kas++;
		s[jas] = malloc((kas + 1) * sizeof(char));
		if (!s[jas])
		{
			for (kas = 0; kas < jas; kas++)
				free(s[kas]);
			free(s);
			return (NULL);
		}
		for (mas = 0; mas < kas; mas++)
			s[jas][mas] = str[ias++];
		s[jas][mas] = 0;
	}
	s[jas] = NULL;
	return (s);
}


