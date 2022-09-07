#include "shell.h"

/**
* link_count - counts number of nodes in linked list
* @head: pointer to head of linked list
*
* Return: number of nodes
*/
unsigned int link_count(env_t *head)
{
env_t *tmp;
unsigned int count;

tmp = head;
count = 0;

while (tmp != NULL)
{
tmp = tmp->next;
count++;
}

return (count);
}

/**
* env_list - creates a linked list
* Return: head (pointer to first node of linked list of environ variables)
*/
env_t *env_list(void)
{
int i;
env_t *head;
char **variable;

head = NULL;
for (i = 0; environ[i] != NULL; i++)
{
variable = separate_string(environ[i]);
if (add_node_env(&head, variable[0], variable[1]) == NULL)
return (NULL);
free(variable[0]);
free(variable[1]);
free(variable);
}

return (head);
}

/**
* zelda_to_ganondorf->converts linked list to double pointer
* @head: head pointer
* Return: array of pointers,*strings
*/
char **zelda_to_ganondorf(env_t *head)
{
int x;
unsigned int count, lenA, lenB, newLen;
char **ganondorf, *var, *val, *new_val;
env_t *tmp;

count = link_count(head);
ganondorf = malloc(sizeof(char *) * (count + 1));

tmp = head;
x = 0;
while (tmp != NULL)
{
var = tmp->var;
val = tmp->val;
lenA = _strlen(var);
lenB = _strlen(val);

newLen = lenA + lenB + 2;
new_val = safe_malloc(newLen *sizeof(char));

_strncat(new_val, var, lenA);
_strncat(new_val, "=", 1);
_strncat(new_val, val, lenB);
ganondorf[x] = new_val;
tmp = tmp->next;
x++;
}
ganondorf[x] = NULL;

return (ganondorf);
}
