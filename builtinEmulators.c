#include "header.h"

/**
 * exitEmulator - Emulates the 'exit' command functionality.
 * @infolist: Pointer to the infolist structure.
 *
 * This function emulates the behavior of the 'exit' command.If called without
 * arguments, it sets the error code to -1 and returns -2, indicating an exit.
 * If called with a numeric argument, it sets error code to the provided value
 * and returns -2. If the numeric argument is invalid, it sets error code to 2
 * and prints an error message.
 *
 * Return: -2 to indicate exit, 1 if an illegal numeric argument is provided.
 */
int exitEmulator(infolist_t *infolist)
{
	int checkExit;

	/* Check if an argument is provided */
	if (infolist->argument_v[1])
	{
		/* Convert the argument to an integer */
		checkExit = StringToInteger(infolist->argument_v[1]);
		/* Check if the conversion was successful */
		if (checkExit == -1)
		{
			/* Set error code to 2 and print an error message */
			infolist->my_status = 2;
			PrintError(infolist, "That is numper is illegal: ");
			errPrintStr(infolist->argument_v[1]);
			errPrintChar('\n');
			return (1);/* Return 1 to indicate an illegal numeric argument */
		}
		/* Set the error code to the converted value */
		infolist->err_code = StringToInteger(infolist->argument_v[1]);
		/* Return -2 to indicate exit */
		return (-2);
	}
	/* Set the error code to -1 and return -2 to indicate exit */
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
char *str, *directory, myBuff[1024];
int ret_dir;

str = getcwd(myBuff, 1024);/*get current working directory.*/
if (!str)
	Puts("TODO: >>getcwd failure emsg here<<\n");
if (!infolist->argument_v[1])/* Check if no directory argument is provided */
{/*Change to user's home directory if available,otherwise root directory*/
	directory = getEnv(infolist, "HOME=");
	if (!directory)
		ret_dir =
		chdir((directory = getEnv(infolist, "PWD=")) ? directory : "/");
	else
	ret_dir = chdir(directory);/*change the current working directory.*/
} /* Check if the directory argument is "-" */
else if (compareStrings(infolist->argument_v[1], "-") == 0)
{/* Print and change to the previous directory stored in "OLDPWD" */
	if (!getEnv(infolist, "OLDPWD="))
	{
		Puts(str);
		PutCharacter('\n');
		return (1);
	}
	Puts(getEnv(infolist, "OLDPWD=")), PutCharacter('\n');
	ret_dir =
		chdir((directory = getEnv(infolist, "OLDPWD=")) ? directory : "/");
} /* Change to the specified directory */
else
	ret_dir = chdir(infolist->argument_v[1]);
if (ret_dir == -1)/* Check if an error occurred during directory change */
{
	PrintError(infolist, "can't cd to ");
	errPrintStr(infolist->argument_v[1]), errPrintChar('\n');
}
else
{/* Update the "OLDPWD" and "PWD" environment variables */
	init_env_var(infolist, "OLDPWD", getEnv(infolist, "PWD="));
	init_env_var(infolist, "PWD", getcwd(myBuff, 1024));
} /* Return 0 on success, 1 if an error occurs */
return (0);
}

/**
 * helpEmulator - Placeholder for the 'help' command emulator.
 * @infolist: Pointer to the infolist structure.
 *
 * This function is a placeholder for the 'help' command emulator. It currently
 * prints a message indicating that the help emulator works but the function
 * is not yet implemented.
 *
 * Return: Always returns 0.
 */
int helpEmulator(infolist_t *infolist)
{
	char **arrayArgument;

	/* Temporary placeholder for future implementation */
	arrayArgument = infolist->argument_v;
Puts("This is for the help command.but Functionality not implemented yet.\n");
	/* Workaround to avoid 'unused variable' warning */
	if (0)
		Puts(*arrayArgument);
	return (0);
}
