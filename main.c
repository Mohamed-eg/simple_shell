#include "header.h"

/**
 * @brief The main function for the shell-like program.
 *
 * This function initializes an array of `infolist_t` structures, opens a file if
 * a command-line argument is provided, and then enters a shell loop.
 *
 * @param argument_coun The number of command-line arguments.
 * @param argument_v The array of command-line arguments.
 *
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE otherwise.
 *         Additionally, it may exit with status codes 126 or 127 in case of
 *         specific error conditions related to file opening.
 */
int main(int argument_coun, char **argument_v)
{
	infolist_t infolist[] = { initialInformatio };
	int fileDes = 2;

	/*Modify fileDes using inline assembly*/
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDes)
		: "r" (fileDes));

	/*Check if a command-line argument is provided*/
	if (argument_coun == 2)
	{
		/*open() is a built in fun in fcntl.h*/
		fileDes = open(argument_v[1], O_RDONLY)/*Open a file in read-only mode*/;
		if (fileDes == -1)
		{
			if (errno == EACCES)/*permision denied*/
				exit(126);
			if (errno == ENOENT)/*No such file or directory*/
			{
				/*Print error message for non-existent file*/
				errPrintStr(argument_v[0]);
				errPrintStr(": 0: Can't open that file ");
				errPrintStr(argument_v[1]);
				errPrintChar('\n');
				errPrintChar(bufferFlush);/*-1*/
				exit(127);/*No such file or directory*/
			}
			return (EXIT_FAILURE);/*Used by the atexit() function. from stdlib.h*/
		}
		infolist->readfd = fileDes;
	}
	/*Populate environment list, read history, and enter the shell loop*/
	populateEnvList(infolist);
	r_history(infolist);
	shellLoob(infolist, argument_v);
	return (EXIT_SUCCESS);
}
/*
* macros used here is [EXIT_FAILURE,EACCES,ENOENT,O_RDONLY]
* O_RDONLY ->  fcntl.h
* EXIT_FAILURE -> stdlib.h
* EACCES,ENOENT -> errno.h 
*/