#include "header.h"

/**
 * shellLoob - main shell loop
 * @infolist: the parameter & return infolist struct
 * @argument_v: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shellLoob(infolist_t *infolist, char **argument_v)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearInformation(infolist);
		if (IsInteractive(infolist))
			Puts("$ ");
		errPrintChar(bufferFlush);
		r = getInput(infolist);
		if (r != -1)
		{
			setInformation(infolist, argument_v);
			builtin_ret = findBuiltinCom(infolist);
			if (builtin_ret == -1)
				cheackPasses(infolist);
		}
		else if (IsInteractive(infolist))
			PutCharacter('\n');
		freeInformation(infolist, 0);
	}
	w_history(infolist);
	freeInformation(infolist, 1);
	if (!IsInteractive(infolist) && infolist->status)
		exit(infolist->status);
	if (builtin_ret == -2)
	{
		if (infolist->err_code == -1)
			exit(infolist->status);
		exit(infolist->err_code);
	}
	return (builtin_ret);
}

/**
 * findBuiltinCom - finds a Builtin_Comands command
 * @infolist: the parameter & return infolist struct
 *
 * Return: -1 if Builtin_Comands not found,
 *			0 if Builtin_Comands executed successfully,
 *			1 if Builtin_Comands found but not successful,
 *			-2 if Builtin_Comands signals exit()
 */
int findBuiltinCom(infolist_t *infolist)
{
	int i, built_in_ret = -1;
	stracOfBuildIn builtintbl[] = {
		{"exit", exitEmulator},
		{"env", my_env},
		{"help", helpEmulator},
		{"history", historyEmulator},
		{"setenv", mySetEnv},
		{"unsetenv", unSetEnv},
		{"cd", cdEmulator},
		{"alias", aliasEmulator},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].flag; i++)
		if (compareStrings(infolist->argument_v[0] , builtintbl[i].flag) == 0)
/*or you can use (compareString(infolist->argument_v[0] , builtintbl[i].flag)==0)
* and it will retarn zero if s1 == s2*/
		{
			infolist->err_line_num++;
			built_in_ret = builtintbl[i].function(infolist);
			break;
		}
	return (built_in_ret);
}

/**
 * cheackPasses - finds a command in PATH
 * @infolist: the parameter & return infolist struct
 *
 * Return: void
 */
void cheackPasses(infolist_t *infolist)
{
	char *str_path = NULL;
	int i, k;

	infolist->str_path = infolist->argument_v[0];
	if (infolist->linenumflag == 1)
	{
		infolist->err_line_num++;
		infolist->linenumflag = 0;
	}
	for (i = 0, k = 0; infolist->argument[i]; i++)
		if (!IsDelimeter(infolist->argument[i], " \t\n"))
			k++;
	if (!k)
		return;

	str_path = findPath(infolist, getEnv(infolist, "PATH="), infolist->argument_v[0]);
	if (str_path)
	{
		infolist->str_path = str_path;
		forkThread(infolist);
	}
	else
	{
		if ((IsInteractive(infolist) || getEnv(infolist, "PATH=")
			|| infolist->argument_v[0][0] == '/') && isCMD(infolist, infolist->argument_v[0]))
			forkThread(infolist);
		else if (*(infolist->argument) != '\n')
		{
			infolist->status = 127;
			PrintError(infolist, "not found\n");
		}
	}
}

/**
 * forkThread - forks a an exec thread to run CMD
 * @infolist: the parameter & return infolist struct
 *
 * Return: void
 */
void forkThread(infolist_t *infolist)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infolist->str_path, infolist->argument_v, our_environ(infolist)) == -1)
		{
			freeInformation(infolist, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(infolist->status));
		if (WIFEXITED(infolist->status))
		{
			infolist->status = WEXITSTATUS(infolist->status);
			if (infolist->status == 126)
				PrintError(infolist, "Permission denied\n");
		}
	}
}
