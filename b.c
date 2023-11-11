#include "shell.h"

/**
 * customexit - quits shell
 * @info: a pointer of type inform_t
 * Return: quits, (0) if info.commandargs[0] != "exit"
 */
int customexit(inform_t *info)
{
	int exitchk;

	if (info->commandargs[1])
	{
		exitchk = err_at(info->commandargs[1]);
		if (exitchk == -1)
		{
			info->status = 2;
			prt_err(info, "Illegal number: ");
			print_str(info->commandargs[1]);
			print_char('\n');
			return (1);
		}
		info->errorcode = err_at(info->commandargs[1]);
		return (-2);
	}
	info->errorcode = -1;
	return (-2);
}

/**
 * customcd - changes the current directory
 * @info: pointer of type inform_t
 * Return: always 0
 */
int customcd(inform_t *info)
{
	char *strn, *dirrd, buffer[1024];
	int dest_dir;

	strn = getcwd(buffer, 1024);
	if (!strn)
		print_s("Location does not exist\n");
	if (!info->commandargs[1])
	{
		dirrd = disp_env(info, "HOME=");
		if (!dirrd)
			dest_dir =
				chdir((dirrd = disp_env(info, "PWD=")) ? dirrd : "/");
		else
			dest_dir = chdir(dirrd);
	}
	else if (str_cmp(info->commandargs[1], "-") == 0)
	{
		if (!disp_env(info, "OLDPWD="))
		{
			print_s(strn);
			print_ch('\n');
			return (1);
		}
		print_s(disp_env(info, "OLDPWD=")), print_ch('\n');
		dest_dir =
			chdir((dirrd = disp_env(info, "OLDPWD=")) ? dirrd : "/");
	}
	else
		dest_dir = chdir(info->commandargs[1]);
	if (dest_dir == -1)
	{
		prt_err(info, "Can't change directory to ");
		print_str(info->commandargs[1]), print_char('\n');
	}
	else
	{
		set_info(info, "OLDPWD", disp_env(info, "PWD="));
		set_info(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * customhelp - changes the current directory
 * @info: a pointer of type inform_t,
 * Return: always 0
 */
int customhelp(inform_t *info)
{
	char **arg_array;

	arg_array = info->commandargs;
	print_s("\n");
	if (0)
		print_s(*arg_array);
	return (0);
}

