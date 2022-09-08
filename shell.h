#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* included standard library headers */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>

/* included structs */
/*#include "struct.h"*/

/* -----MACROS----- */
#define BUFSIZE 1024
#define EXT_SUCCESS 0
#define EXT_FAILURE 1
#define TRUE (1 == 1)
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define FALSE (!TRUE)

/* this defines the macros for token_t struct */
#define TOKEN_STRING     0
#define TOKEN_SEMICOLON  1
#define TOKEN_PIPE       2
#define TOKEN_REWRITE    3
#define TOKEN_APPEND     4
#define TOKEN_CAT        5
#define TOKEN_BACKGROUND 6
#define TOKEN_AND        7
#define TOKEN_OR         8

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* -----environ----- */
extern char **environ;

/**
* struct liststr - singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
*struct passinfo - contains pseudo-arguements to pass into a function,		
*allowing uniform prototype for function pointer struct
*@arg: a string generated from getline containing arguements
*@argv: an array of strings generated from arg
*@path: a string path for the current command
*@argc: the argument count
*@line_count: the error count
*@err_num: the error code for exit()s
*@linecount_flag: if on count this line of input
*@fname: the program filename
*@env: linked list local copy of environ
*@environ: custom modified copy of environ from LL env
*@history: the history node
*@alias: the alias node
*@env_changed: on if environ was changed
*@status: the return status of the last exec'd command
*@cmd_buf: address of pointer to cmd_buf, on if chaining
*@cmd_buf_type: CMD_type ||, &&, ;
*@readfd: the fd from which to read line input
*@histcount: the history line number count
*/
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
*struct builtin - contains a builtin string and related function
*@type: the builtin command flag
*@func: the function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;


/* --------- exit ---------- */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/*-------- shellvar----------*/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

/* ---------------tokenizer--------------- */
char **strtow(char *, char *);
char **strtow2(char *, char);


/* -------environ------- */
char *_getenv(info_t *, const char *);
int _env(info_t *);
int _ssetenv(info_t *);
int _unssetenv(info_t *);
int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* ---------------builtin--------------- */
int _shellexit(info_t *);
int _shellcd(info_t *);
int _shellhelp(info_t *);

int _shellhistory(info_t *);
int _shellalias(info_t *);

/* ---------------strings--------------- */
/*int _strlen(char *);*/
unsigned int _strlen(const char *str);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* -----custom C std lib----- */
int loophsh(char **);

/* ---------------errors--------------- */
void _putstring(char *);
int _stutchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _atoierror(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* ---------------history--------------- */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);


/* ---------------allocation--------------- */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

/* ---------------atoi--------------- */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* ---------------list--------------- */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* ---------------parser--------------- */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* --------------shelcmd--------------- */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* ----getline---- */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*----- shell exit-----------*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#endif
