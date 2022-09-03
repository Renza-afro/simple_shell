#include "shell.h"

/**
* _strlen-> print string length
* @str: string
* Return: string
*/

int _strlen(char *str)
{
int x = 0;
while (str[x])
x++;
return (x);
}

/**
* _strcmp-> compare strings
* @str1: string 1
* @str2: string 2
* Return:..
*/
int _strcmp(char *str1, char *str2)
{
int lenA = _strlen(str1);
int lenB = _strlen(str2);
int x;

if (lenA != lenB)
return (-1);

while (str1[x])
{
if (str1[x] != str2[x])
return (-1);
x++;
}
return (0);
}


