#include "shell.h"

/**
 * free_b - frees a pointer
 * @ptrhr: address of the pointer
 * Return: 1, otherwise 0
 */
int free_b(void **ptrhr)
{
	if (ptrhr && *ptrhr)
	{
		free(*ptrhr);
		*ptrhr = NULL;
		return (1);
	}
	return (0);
}

