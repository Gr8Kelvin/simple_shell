#include "shell.h"

/**
 * **str_tow - splits string into words
 * @strn: the input string
 * @d: the delimeter string
 * Return: memory location
 */

char **str_tow(char *strn, char *d)
{
	int ihr, jhr, khr, mhr, num_of_words = 0;
	char **shr;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (ihr = 0; strn[ihr] != '\0'; ihr++)
		if (!deli(strn[ihr], d) && (deli(strn[ihr + 1], d) || !strn[ihr + 1]))
			num_of_words++;

	if (num_of_words == 0)
		return (NULL);
	shr = malloc((1 + num_of_words) * sizeof(char *));
	if (!shr)
		return (NULL);
	for (ihr = 0, jhr = 0; jhr < num_of_words; jhr++)
	{
		while (deli(strn[ihr], d))
			ihr++;
		khr = 0;
		while (!deli(strn[ihr + khr], d) && strn[ihr + khr])
			khr++;
		shr[jhr] = malloc((khr + 1) * sizeof(char));
		if (!shr[jhr])
		{
			for (khr = 0; khr < jhr; khr++)
				free(shr[khr]);
			free(shr);
			return (NULL);
		}
		for (mhr = 0; mhr < khr; mhr++)
			shr[jhr][mhr] = strn[ihr++];
		shr[jhr][mhr] = 0;
	}
	shr[jhr] = NULL;

	free_mem(shr);
	return (shr);
}

/**
 * **str_tow2 - splits a given string into words
 * @strn: the input string
 * @d: the delimeter
 * Return: memory location
 */
char **str_tow2(char *strn, char d)
{
	int ihr, jhr, khr, mhr, num_of_words = 0;
	char **shr;

	if (strn == NULL || strn[0] == 0)
		return (NULL);
	for (ihr = 0; strn[ihr] != '\0'; ihr++)
		if ((strn[ihr] != d && strn[ihr + 1] == d) ||
				(strn[ihr] != d && !strn[ihr + 1]) || strn[ihr + 1] == d)
			num_of_words++;
	if (num_of_words == 0)
		return (NULL);
	shr = malloc((1 + num_of_words) * sizeof(char *));
	if (!shr)
		return (NULL);
	for (ihr = 0, jhr = 0; jhr < num_of_words; jhr++)
	{
		while (strn[ihr] == d && strn[ihr] != d)
			ihr++;
		khr = 0;
		while (strn[ihr + khr] != d && strn[ihr + khr] && strn[ihr + khr] != d)
			khr++;
		shr[jhr] = malloc((khr + 1) * sizeof(char));
		if (!shr[jhr])
		{
			for (khr = 0; khr < jhr; khr++)
				free(shr[khr]);
			free(shr);
			return (NULL);
		}
		for (mhr = 0; mhr < khr; mhr++)
			shr[jhr][mhr] = strn[ihr++];
		shr[jhr][mhr] = 0;
	}
	shr[jhr] = NULL;

	free_mem(shr);
	return (shr);
}

