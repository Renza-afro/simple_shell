#include "shell.h"

/**
* main_c-> print signal
* @signum:..
* Return:..
*/
void main_c(int signum)
{
if (signum == SIGINT)
print("\n ($) ", STDIN_FILENO);
}

/**
* _getline -> accept input
* Return: string
*/
char *_getline(void)
{
int buff_size = READ_BUF, n_read, position = 0;
char *buffer = malloc(buff_size * sizeof(char));
char c;

if (buffer == NULL)
{
perror("memory allocation failed");
exit(EXIT_FAILURE);
}
while (1)
{
n_read = read(STDIN_FILENO, &c, 1);
if (c == EOF || !n_read)
{
if (isatty(STDIN_FILENO) == 1)
{
print("\n", STDIN_FILENO);
return (NULL);
}
}
else if (c == '\n' || !n_read)
{
buffer[position] = '\0';
return (buffer);
}
else
buffer[position] = c;
position++;

if (position >= buff_size)
{
buff_size += READ_BUF;
buffer = _realloc(buffer, READ_BUF, buff_size);
if (!buffer)
{
perror("re-allocation failed");
exit(EXIT_FAILURE);
}
}
}
}

int is_delimeter(const char *delimeters, char c);

/**
* **tokenize->...
* @line_read:...
* @delim:..
* Return:...
*/
char **tokenize(char *str, const char *delim)
{
int k = 0, j = 0, i = 0, size = 0, len[1200];
char **arr;

if (str == NULL || !(str))
return (NULL);
   
/*cal no of word and lenght*/
for (i = 0; str[i]; i++)
{
if (is_delimeter(delim, str[i]))
continue;
 
j = i;
while (!is_delimeter(delim, str[i]) && str[i])
i++;
if (i > j)
len[size++] = i - j;
if (!str[i])
break; 
}
if (!size)
return(NULL); 
arr = malloc((size + 1) * sizeof(char *));
for (i = 0; str[i]; i++)
{
if (is_delimeter(delim, str[i]))
continue;
arr[k] = malloc((len[k] + 1) * sizeof(char));
j = 0;
while (!is_delimeter(delim, str[i]) && str[i])
arr[k][j++] = str[i++];
arr[k++][j] = '\0';
if (!str[i])
break;
}
arr[size] = NULL;
return (arr);

}


/**
* is_delimeter->....
* @delimeters: pointer
* @c: character to be checked
* Return: 1 if true. 0n false
*/
int is_delimeter(const char *delimeters, char c)
{
int i = 0;
if (!delimeters)
return (0);
while (delimeters[i])
{
if (delimeters[i] == c)
return (1);
i++;
}
return (0);
}

/**
* shell_execute->...
* @command: ...
* @cmd_type:..
* Return:..
*/
void shell_execute(char **command, int cmd_type, data_h *p)
{
int stat;
pid_t PID;

if (cmd_type == EXTERNAL_CMD || cmd_type == PATH_CMD)
{
PID = fork();

if (PID == 0)
{
execute(command, cmd_type, p);
}
if (PID < 0)
{
perror("failed to call fork");
exit(1);
}
else
wait(&stat);
}
else
execute(command, cmd_type, p);
}

/**
* chech_command->..
* @command:..
* Return:..
*/
int check_command(char *command)
{
int i = 0;
char *int_cmd[] = {"exit", "cd", "env", NULL};

while (command[i])
{
if (command[i] == '/')
return (EXTERNAL_CMD);
i++;
}

i = 0;
while (int_cmd[i] != NULL)
{
if (_strcmp(command, int_cmd[i]) == 0)
return (INTERNAL_CMD);
i++;
}

return (INVALID_CMD);

}

/**
* execute->..
* @cmd_type:..
* Return:..
*/
void execute(char **commands, int cmd_type, data_h *var)
{
void (*func)(char **command, data_h *);

switch (cmd_type)
{
case EXTERNAL_CMD:
{
if (execve(commands[0], commands, NULL) == -1)
{
perror(_getenv("PWD"));
exit(2);
}
break;
}
case INTERNAL_CMD:
{
printf("<<got here>>\n");
func = get_func(commands[0]);
func(commands, var);
break;
}
case PATH_CMD:
{
break;
}
case INVALID_CMD:
{
break;
}
}
}
