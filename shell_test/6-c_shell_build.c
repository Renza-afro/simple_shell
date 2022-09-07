#include "shell.h"

/**
* env->..
* @command:..
* Return:..
*/
void env(char **command __attribute__((unused)), data_h __attribute__((unused)))
{
int x = 0;

while (envi[x])
{
print(envi[x++], STDOUT_FILENO);
print("\n", STDOUT_FILENO);
}
}

/**
* quit->...
* @command:..
* Return:..
*/
void quit(char **command, data_h *var)
{
(void) command;
(void) var;
}

/**
* ch_dir->..
* @command:..
* Return:..
*/
#define SET_OLD(V) (V = _strdup(_getenv("OLDPWD")))
void ch_dir(char **command, data_h *var)
{
/*(void) command;*/
char *home;
home = _getenv("HOME");
if (command[1] == NULL)
{
SET_OLD(var->oldPath);
if (chdir(home) < 0)
exit(EXIT_FAILURE);
}
if (strcmp(command[1], "-") == 0)
{
if (var->oldPath == NULL)
{
SET_OLD(var->oldPath);
if (chdir(home) < 0)
exit(EXIT_FAILURE);
}
else
{
SET_OLD(var->oldPath);
if (chdir(var->oldPath) < 0)
exit(EXIT_FAILURE);
}
}
else
{
SET_OLD(var->oldPath);
if (chdir(command[1]) < 0)
exit(EXIT_FAILURE);
}
}
