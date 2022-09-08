#include "shell.h"

/**
* _strcat - concatenates from src string to dest string
* @dest: destination string
* @src: source string
* @n: number of bytes to concatenate
*
* Return: pointer to destination
*/
char *_strcat(char *dest, char *src)
{

char *rev = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (rev);
}


/**
* _strlen - finds and returns length of string
* @str: string to find length
*
* Return: length of string
*/
unsigned int _strlen(const char *str)
{
int i = 0;

while (str[i] != '\0')
i++;

return (i);
}


/**
* starts_with - checks if needle starts with haystack
* @haystack: string to search
* @needle: the substring to find
*
* Return: address of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
* _strncmp - checks if 2 strings are of equal value and length
* @s1: first string
* @s2: second string
* Return: difference of first chars of diff value or 0 on success
*/
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
return (*s1 - *s2);
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 < *s2 ? -1 : 1);
}
