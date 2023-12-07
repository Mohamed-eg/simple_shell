#include "header.h"

/**
 * main - entry point
 * @argument_coun: argument count
 * @argument_v: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argument_coun, char **argument_v)
{
	infolist_t infolist[] = { initialInformatio };
	int fileDes = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDes)
		: "r" (fileDes));

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
				errPrintStr(argument_v[0]);
				errPrintStr(": 0: Can't open ");
				errPrintStr(argument_v[1]);
				errPrintChar('\n');
				errPrintChar(bufferFlush);/*-1*/
				exit(127);
			}
			return (EXIT_FAILURE);/*Used by the atexit() function. from stdlib.h*/
		}
		infolist->readfd = fileDes;
	}
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