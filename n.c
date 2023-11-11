#include "shell.h"

/**
 * main - the main
 * @achr: commandname count
 * @avhr: commandname vector
 * Return: 0 , otherwise 1 on failure
 */
int main(int achr, char **avhr)
{
	inform_t info[] = { INFO_INIT };
	int fdhr = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fdhr)
			: "r" (fdhr));

	if (achr == 2)
	{
		fdhr = open(avhr[1], O_RDONLY);
		if (fdhr == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_str(avhr[0]);
				print_str(": 0: Can't open ");
				print_str(avhr[1]);
				print_char('\n');
				print_char(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdhr;
	}
	pop_env(info);
	read_hist(info);
	shs(info, avhr);
	return (EXIT_SUCCESS);
}

