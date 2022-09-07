#include "shell.h"

/**
* print->...
* @var:..
* @fd:..
* Return:...
*/
int print(char *var, int fd)
{
return (write(fd, var, _strlen(var)));
}

/**
* get_func->..
* @command:..
* Return:...
*/
void (*get_func(char *command))(char **)
{
int x;
map_func map[] = {
{"env", env},
{"cd", ch_dir},
{"exit", quit}
};
for (x = 0; x < 3; x++)
{
if (_strcmp(command, map[x].cmd_name) == 0)
return (map[x].func);
}
return (NULL);
}
