#include "header.h"

/**
 * exitEmulator - exits the shell
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if infolist.argument_v[0] != "exit"
 */
int exitEmulator(infolist_t *infolist)
{
	int exitcheck;

	if (infolist->argument_v[1])  /* If there is an exit arguement */
	{
		exitcheck = StringToInteger(infolist->argument_v[1]);
		if (exitcheck == -1)
		{
			infolist->my_status = 2;
			PrintError(infolist, "Illegal number: ");
			errPrintStr(infolist->argument_v[1]);
			errPrintChar('\n');
			return (1);
		}
		infolist->err_code = StringToInteger(infolist->argument_v[1]);
		return (-2);
	}
	infolist->err_code = -1;
	return (-2);
}

/**
 * cdEmulator - changes the current directory of the process
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int cdEmulator(infolist_t *infolist)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		Puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infolist->argument_v[1])
	{
		dir = getEnv(infolist, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = getEnv(infolist, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compareStrings(infolist->argument_v[1], "-") == 0)
	{
		if (!getEnv(infolist, "OLDPWD="))
		{
			Puts(s);
			PutCharacter('\n');
			return (1);
		}
		Puts(getEnv(infolist, "OLDPWD=")), PutCharacter('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = getEnv(infolist, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(infolist->argument_v[1]);
	if (chdir_ret == -1)
	{
		PrintError(infolist, "can't cd to ");
		errPrintStr(infolist->argument_v[1]), errPrintChar('\n');
	}
	else
	{
		init_env_var(infolist, "OLDPWD", getEnv(infolist, "PWD="));
		init_env_var(infolist, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpEmulator - changes the current directory of the process
 * @infolist: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int helpEmulator(infolist_t *infolist)
{
	char **arg_array;

	arg_array = infolist->argument_v;
	Puts("help emulater works. but function not yet iplemnt \n");
	if (0)
		Puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
