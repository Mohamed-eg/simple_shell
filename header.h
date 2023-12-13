#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>/* for standard input/output functions(printf, scanf) */
#include <stdlib.h>/*for dynamic memory allocation (e.g., malloc, free)*/
#include <unistd.h>
#include <string.h>/*for string manipulation functions (e.g., strcpy, strlen)*/
#include <sys/types.h>
/*
* This header file contains definitions for various data types
* used by system calls. It includes typedefs for data types such as
* https://www.ibm.com/docs/en/zos/2.1.0?topic=files-systypesh
*/
#include <sys/wait.h>
#include <sys/stat.h>/*for stat() or struct stat*/
#include <limits.h>
/*
*This header file contains various constants that represent
* the limits of various properties of the implementation,
* such as the maximum and minimum values that can be held
* by different data types.
*/
#include <fcntl.h>
/*
* file control operations. It provides constants used with
* the fcntl function, which can be used to perform various
* operations on open files.
*/
#include <errno.h>
#include <stddef.h> /*for size_t data type*/

/* 1 if using system getline() */
#define useGetLine 0
/*#define useStrtok 0*/

/* for chaining command*/
#define cmdNormal	0
#define orChain		1
#define andChain		2
#define cmdChain	3

/* for convert_number() */
#define lowerCaseConverter	1
#define unsignedConverter	2

/* for buffers read or write */
#define readBufferSize 1024
#define writeBufferSize 1024
#define bufferFlush -1


#define fileHistory	".simple_shell_history"
#define maxHistory	4096

extern char **environ/*environmental var from stdlib.h*/;


/**
 * struct stringList -> list of singly links
 * @number: the number of fields
 * @string: a string
 * @next_node: pointer to the next node
 */
typedef struct stringList
{
	int number;
	char *string;
	struct stringList *next_node;
} stringlist_t;/*creates a typedef alias named stringlist_t*/

/**
 *struct PassedInformation - contains pseudo-arguements to pass into
 *a function,	allowing uniform prototype for function pointer struct
 *@argument: a string generated from getline containing arguements
 *@argument_v: an array of strings generated from argument
 *@str_path: a string str_path for the current command
 *@argument_c: the argument count
 *@err_line_num: the error count
 *@err_code: the error code it can be 2 & it is always a number
 *@linenumflag: if on count this line of input
 *@filename: the program filename
 *@envir: linked list local copy of environ
 *@environ: custom modified copy of environ from LL envir
 *@my_history: the history node
 *@my_alias: the alias node
 *@isenvchange: on if environ was changed
 *@my_status: the return status of the last exec'd command
 *@cmdBuffer: address of pointer to cmdBuffer, on if chaining
 *@cmdBufferTybe: CMD_type ||, &&, ;
 *@rfd: the fileDes from which to read line input
 *@histnum: the history line number count
 */
typedef struct PassedInformation
{
	char *argument;
	char **argument_v;/*argument Value*/
	char *str_path;
	int argument_c;/*argument Count*/
	unsigned int err_line_num;
	int err_code;
	int linenumflag;
	char *filename;
	stringlist_t *envir;
	stringlist_t *my_history;
	stringlist_t *my_alias;
	char **environ;
	int isenvchange;
	int my_status;

	char **cmdBuffer; /* pointer to CMD ; chain buffer, for memory mangement */
	int cmdBufferTybe; /* CMD_type ||, &&, ; */
	int rfd;
	int histnum;
} infolist_t;

#define initialInformatio \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct Builtin_Comands - Structure for storing information
 * about built-in commands.This structure defines a template for storing
 * information about built-in commands. It includes a flagand a function
 * pointer to the corresponding function that handles the command.
 * @flag: Command name or identifier.
 * @function: Pointer to the function handling the command.
 */
typedef struct Builtin_Comands
{
	char *flag;/**< Command name or identifier. */
	/**< Pointer to the function handling the command. */
	int (*function)(infolist_t *);
} stracOfBuildIn;


/* shellLoob.c */
int shellLoob(infolist_t *, char **);
int findBuiltinCom(infolist_t *);
void cheackPasses(infolist_t *);
void forkThread(infolist_t *);

/* PATH.c */
int isCMD(infolist_t *, char *);
char *duplCharacters(char *, int, int);
char *findPath(infolist_t *, char *, char *);

/* errStringFun.c */
void errPrintStr(char *);
int errPrintChar(char);
int WFileDescreptor(char c, int fileDes);
int charsCount(char *string, int fileDes);

/* stringFun.c */
int getStringLength(char *);
int compareStrings(char *, char *);
char *startsWith(const char *, const char *);
char *concatenetStrings(char *, char *);
char *StringCopy(char *, char *, int);

/* stringFun3.c */
char *concatenatesStrings(char *, char *, int);
char *locateChar(char *, char);
char **SplitString2(char *, char);

/* stringFun2.c */
char *copyStrings(char *, char *);
char *duplcatString(const char *);
void Puts(char *);
int PutCharacter(char);
char **SplitString(char *, char *);

/* MemoryFun */
char *fillMemoryWith(char *, char, unsigned int);
void freeFun(char **);
void *reAllocat(void *, unsigned int, unsigned int);

/* MemoryFun2.c */
int freePointers(void **);

/* Fun.c */
int IsInteractive(infolist_t *);
int IsDelimeter(char, char *);
int ISAlphabetic(int);
int StrToInt(char *);

/* Fun2.c */
int StringToInteger(char *);
void PrintError(infolist_t *, char *);
int printDescriptor(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtinEmulators.c */
int exitEmulator(infolist_t *);
int cdEmulator(infolist_t *);
int helpEmulator(infolist_t *);

/* builtinEmulators2.c */
int historyEmulator(infolist_t *);
int aliasEmulator(infolist_t *);

/* getline.c advans */
ssize_t getInput(infolist_t *);
int getNextLine(infolist_t *, char **, size_t *);
void hamdelSigin(int);

/* infolist.c advans */
void clearInformation(infolist_t *);
void setInformation(infolist_t *, char **);
void freeInformation(infolist_t *, int);

/* environment.c  */
char *getEnv(infolist_t *, const char *);
int my_env(infolist_t *);
int mySetEnv(infolist_t *);
int unSetEnv(infolist_t *);
int populateEnvList(infolist_t *);

/* environment2.c advans */
char **our_environ(infolist_t *);
int remov_environ(infolist_t *, char *);
int init_env_var(infolist_t *, char *, char *);

/* file_io_functions.c */
char *getFileHistory(infolist_t *infolist);
int w_history(infolist_t *infolist);
int r_history(infolist_t *infolist);
int buildHistoryList(infolist_t *infolist, char *buf, int linecount);
int renumberHistory(infolist_t *infolist);

/* stringList.c advans */
stringlist_t *ADDnode(stringlist_t **, const char *, int);
stringlist_t *ADDnodeEn(stringlist_t **, const char *, int);
size_t printListString(const stringlist_t *);
int deletNode(stringlist_t **, unsigned int);
void freeList(stringlist_t **);

/* liststr2.c advans */
size_t listLength(const stringlist_t *);
char **listToStrings(stringlist_t *);
size_t elementList(const stringlist_t *);
stringlist_t *nodeStartWith(stringlist_t *, char *, char);
ssize_t nodeIndex(stringlist_t *, stringlist_t *);

/* chain.c */
int isChain(infolist_t *, char *, size_t *);
void checkChain(infolist_t *, char *, size_t *, size_t, size_t);
int replaceAlies(infolist_t *);
int replaVars(infolist_t *);
int replaStr(char **, char *);

#endif
