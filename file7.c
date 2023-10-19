#include "shell.h"

/**
 * customexit - exits shell
 * @info: to maintain constant function prototype.
 * Return:  status (0) if info.argv[0] != "exit"
 */
int customexit(inform_t *info)
{
	int echk;

	if (info->commandargs[1])
	{
		echk = err_at(info->commandargs[1]);
		if (echk == -1)
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
	info->errcode = -1;
	return (-2);
}

/**
 * customcd - changes the current directory
 * @info:  constant function prototype.
 * Return: Always 0
 */
int customcd(inform_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		print_s("TODO: >>getcwd failure emsg here<<\n");
	if (!info->commandargs[1])
	{
		dir = disp_env(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = disp_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->commandargs[1], "-") == 0)
	{
		if (!disp_env(info, "OLDPWD="))
		{
			print_s(s);
			print_ch('\n');
			return (1);
		}
		print_s(disp_env(info, "OLDPWD=")), print_ch('\n');
		chdir_ret =
			chdir((dir = disp_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		prt_err(info, "can't cd to ");
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
 * @info: to maintain constant function prototype.
 * Return: Always 0
 */
int customhelp(inform_t *info)
{
	char **arg_array;

	arg_array = info->commandargs;
	print_s("help call works. Function not yet implemented \n");
	if (0)
		print_s(*arg_array); /* temp att_unused workaround */
	return (0);
}

