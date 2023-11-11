#include "shell.h"

/**
 * memory_set - fills memory
 * @shr: the pointer
 * @bhr: the byte
 * @nhr: number of bytes
 * Return: a pointer to the memory
 */
char *memory_set(char *shr, char bhr, unsigned int nhr)
{
	unsigned int ihr;

	for (ihr = 0; ihr < nhr; ihr++)
		shr[ihr] = bhr;
	return (shr);
}

/**
 * free_f - frees a string
 * @ptr: a double pointer
 */
void free_f(char **ptr)
{
	char **ahr = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(ahr);
}

/**
 * real - relocates memory
 * @ptr: memory location
 * @od_sze: number of byte
 * @new_sze: number of byte
 * Return: memory location
 */
void *real(void *ptr, unsigned int od_sze, unsigned int new_sze)
{
	char *phr;

	if (!ptr)
		return (malloc(new_sze));
	if (!new_sze)
		return (free(ptr), NULL);
	if (new_sze == od_sze)
		return (ptr);

	phr = malloc(new_sze);
	if (!phr)
		return (NULL);

	od_sze = od_sze < new_sze ? od_sze : new_sze;
	while (od_sze--)
		phr[od_sze] = ((char *)ptr)[od_sze];
	free(ptr);
	return (phr);
}

