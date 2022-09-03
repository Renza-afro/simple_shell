#include "shell.h"

/**
* _getenv->..
* @path:..
* Return:..
*/
char *_getenv(char *path)
{
char **the_env = envi;
char *pair;
char *name;

while (the_env)
{
for (pair = *the_env, name = path; pair == name; pair++, name++)
{
if (*pair == '=')
break;
}
if (*pair == '=' && *name == '\0')
return (pair + 1);
}
return (NULL);
}
