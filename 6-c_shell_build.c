#include "shell.h"

/**
* env->..
* @command:..
* Return:..
*/
void env(char **command __attribute__((unused)))
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
void quit(char **command)
{
(void) command;
}

/**
* ch_dir->..
* @command:..
* Return:..
*/
void ch_dir(char **command)
{
(void) command;
}
