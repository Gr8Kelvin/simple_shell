#include "shell.h"

/**
 * mem_set - fills memory with a constant byte
 * @sd: pointer to
 * @bd: byte to fill
 * @nd: bytes to be filled
 * Return: pointer to the memory
 */
char *mem_set(char *sd, char bd, unsigned int nd)
{
	unsigned int ias;

	for (ias = 0; ias < nd; ias++)
		sd[ias] = bd;
	return (sd);
}

/**
 * free_f - frees a string
 * @pp: string of strings
 */
void free_f(char **pp)
{
	char **as = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(as);
}

/**
 * real - reallocates memory
 * @ptr: pointer to previous block
 * @old_size:size  previous block
 * @new_size: size new block
 * Return: pointer to da ol'block nameen.
 */
void *real(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pd;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pd = malloc(new_size);
	if (!pd)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pd[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pd);
}

