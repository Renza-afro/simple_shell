#include "shell.h"
/**
* main->.....
* @argv:...
* @argc:...
* Return:....
*/

int main (int argc __attribute__((unused)), char **argv)
{
char *line;
char **args;
char cmd_type;
(void) argv;
signal(SIGINT, main_c);
while (1)
{
print(" ($) ", STDOUT_FILENO);
line = _getline();

/*printf("\n<<%s>>\n", line);*/
/*return (1);*/
if (line == NULL)
{
if (isatty(STDIN_FILENO))
break;
}
args = tokenize(line, DELIM);
/*while (args[i])*/
/*printf("<<%s>>\n", args[i++]);*/
/*return (1);*/
cmd_type = check_command(args[0]);
shell_execute(args, cmd_type);
}
return (1);
}
