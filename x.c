#include "shell.h"

void free_mem(char **shr)
{

	int i;

    if (!shr)
        return;

    for (i = 0; shr[i] != NULL; i++)
    {
        free(shr[i]);
    }

    free(shr);
}
