#include "shell.h"

/**
* _shellexit-> exits the shell
* @info: Structure containing potential arguments
* Return: exits with a given exit
*/
int _shellexit(info_t *info)
{
int exitcheck;

if (info->argv[1])
{
exitcheck = _atoierror(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_putstring(info->argv[1]);
_putchar('\n');
return (1);
}
info->err_num = _atoierror(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
* _shellcd->changes the current directory of the process
* @info: Structure containing potential arguments
* Return: Always 0
*/

int _shellcd(info_t *info)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
dir = _getenv(info, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "can't change directory to ");
_putstring(info->argv[1]), _putchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* _shellhelp->changes the current directory of the process
* @info: Structure containing potential arguments.
* Return: Always 0
*/

int _shellhelp(info_t *info)
{
char **arg_array;

arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
