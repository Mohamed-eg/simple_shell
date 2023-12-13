#include "header.h"

/**
 * shellLoob - Main loop for the shell.
 * @infolist: Pointer to the infolist structure.
 * @argument_v: Array of strings representing command-line arguments.
 *
 * This function serves as the main loop for the shell, continuously accepting
 * input, processing it, and executing commands until a termination condition
 * is met.
 *
 * Return: The result code indicating the termination condition.
 */
int shellLoob(infolist_t *infolist, char **argument_v)
{
	ssize_t x = 0;/* Input read result */
	int result = 0;/* Result code */

	while (x != -1 && result != -2)
	{
		/* Clear information for the next iteration */
		clearInformation(infolist);
		/* Display shell prompt if in interactive mode */
		if (IsInteractive(infolist))
			Puts("$ ");/* Print any buffered error characters */
		errPrintChar(bufferFlush);
		x = getInput(infolist); /* Get input from the user */
		if (x != -1)
		{/* Set information based on the input */
			setInformation(infolist, argument_v);
			/* Find and execute built-in commands */
			result = findBuiltinCom(infolist);
			/* If not a built-in command, check for external processes */
			if (result == -1)
				cheackPasses(infolist);
		}
		else if (IsInteractive(infolist))
		/* Print a newline if in interactive mode and input is -1 (EOF) */
			PutCharacter('\n');
		 /* Free allocated information for the current iteration */
		freeInformation(infolist, 0);
	} /* Write command history to file */
	w_history(infolist);/* Free all allocated information before exiting */
	freeInformation(infolist, 1);
	if (!IsInteractive(infolist) && infolist->my_status)
		exit(infolist->my_status);
	if (result == -2)/* Handle special exit conditions */
	{
		if (infolist->err_code == -1)
			exit(infolist->my_status);
		exit(infolist->err_code);
	} /* Return the final result code */
	return (result);
}

/**
 * findBuiltinCom -  Finds and executes a built-in command if it exists.
 * @infolist: Pointer to the infolist structure.
 * This function searches for a built-in command in the provided command
 * arguments and executes the corresponding function if a match is found.
 *
 * Return: -1 if Builtin_Comands not found,
 *			0 if Builtin_Comands executed successfully,
 *			1 if Builtin_Comands found but not successful,
 *			-2 if Builtin_Comands signals exit()
 */
int findBuiltinCom(infolist_t *infolist)
{
	int x, builtInRet = -1;
/* Structure to map built-in command names to their corresponding functions */
	stracOfBuildIn builtInTabl[] = {
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
	/* Iterate through the built-in command table */
	for (x = 0; builtInTabl[x].flag; x++)
		/* Check if the current command matches a built-in command */
		if (compareStrings(infolist->argument_v[0], builtInTabl[x].flag) == 0)
		{
			infolist->err_line_num++;
/* Execute the function corresponding to the matched built-in command */
			builtInRet = builtInTabl[x].function(infolist);
			break;
		}
/* Return the result of the executed built-in function or -1 if no match */
	return (builtInRet);
}

/**
 * cheackPasses - Checks and executes commands based on the provided arguments.
 * @infolist: Pointer to the infolist structure.
 *
 * This function checks the provided command arguments, finds the executable
 * path, and forks a new process to execute the command.
 *
 * Return: void
 */
void cheackPasses(infolist_t *infolist)
{
	char *str_path = NULL;
	int x, y;

	/* Set the initial str_path to the first argument */
	infolist->str_path = infolist->argument_v[0];
	/* Check if line number flag is set, increment the error line number*/
	/* and reset the flag */
	if (infolist->linenumflag == 1)
	{
		infolist->err_line_num++;
		infolist->linenumflag = 0;
	} /* Count the number of non-delimiter arguments */
	for (x = 0, y = 0; infolist->argument[x]; x++)
		if (!IsDelimeter(infolist->argument[x], " \t\n"))
			y++;/* If there are no non-delimiter arguments, return */
	if (!y)
		return;
	/* Find the executable path for the command */
	str_path = findPath(infolist, getEnv(infolist, "PATH="),
	infolist->argument_v[0]);
	if (str_path)
	{
		infolist->str_path = str_path;
		forkThread(infolist);
	}
	else
	{
		if ((IsInteractive(infolist) || getEnv(infolist, "PATH=")
			|| infolist->argument_v[0][0] == '/') &&
			isCMD(infolist, infolist->argument_v[0]))
			forkThread(infolist);
		else if (*(infolist->argument) != '\n')
		{
			infolist->my_status = 127;
			PrintError(infolist, " it is not found\n");
		}
	}
}

/**
 * forkThread - Fork a new process and execute a program using execve.
 * @infolist: Pointer to the infolist_t structure containing information
 *            about the program to be executed.
 * Return : void
 */
void forkThread(infolist_t *infolist)
{
	pid_t child_pid;

	/* Fork a new process */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)/* Child process */
	{/* Execute the program in the child process */
		if (execve(infolist->str_path, infolist->argument_v,
		our_environ(infolist)) == -1)
		{/* Handle execution failure in the child process */
			freeInformation(infolist, 1);
			if (errno == EACCES)
				exit(126);/* Exit with code 126 for "Permission denied" */
			exit(1);/* Exit with code 1 for other execution failures */
		}
	}
	else/* Parent process */
	{/* Wait for the child process to finish */
		wait(&(infolist->my_status));
		/* Check if the child process exited successfully */
		if (WIFEXITED(infolist->my_status))
		{/* Extract the exit code of the child process */
			infolist->my_status = WEXITSTATUS(infolist->my_status);
			/* Handle specific exit code (e.g., permission denied) */
			if (infolist->my_status == 126)
				PrintError(infolist, "Permission denied\n");
		}
	}
}
