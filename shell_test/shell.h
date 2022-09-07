#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

/* buffer size */
#define READ_BUF 1000

#define DELIM " \a\t\r\n"

/* command type */
#define INTERNAL_CMD 1
#define EXTERNAL_CMD 2
#define PATH_CMD 3
#define INVALID_CMD -1

/* shell_signal methods*/
void main_c(int);
int print(char *, int);
void (*get_func(char *))(char **, data_h *);

/* global variable*/
extern char **envi;

/* map)_func struct*/
typedef struct internal_func
{
char *cmd_name;
void (*func)(char **command);
} map_func;

typedef struct data
{
char *oldPath;
} data_h;

/*shell build*/
void env(char **, data_h *);
void ch_dir(char **, data_h *);
void quit(char **, data_h *);

/* shell methods */
char *_getline(void);
char **tokenize(char *, const char *);
void shell_execute(char **, int);
int check_command(char *);
void execute(char **, int, data_h *);

/* shell_string method*/
int _strlen(char *);
int _strcmp(char*, char *);

/* memory managent */
/*void * _realloc(void *ptr, int a, int b);*/
void *_realloc(void *ptr, int o_size, int n_size);

/**env*/
char *_getenv(char *);
#endif
