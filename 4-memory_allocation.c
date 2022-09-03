#include "shell.h"

/**
* 1: allocate temp memeory
* 2: cpy from buff to tmp
* 3: free buff
* 4: reallocate
* 5: cpy from tmp to buff
* 6: return new buff
*/
void *_realloc(void *ptr, int o_size, int n_size)
{
void *tmp;
int min, x;
if (!ptr)
return (malloc (n_size));
else if (n_size == o_size)
return (ptr);
else if (n_size == 0 && ptr)
{
free (ptr);
return (NULL);
}
else
{
min = (n_size < o_size) ? n_size : o_size;
tmp = malloc(n_size);
if (tmp)
{
for (x = 0; x < min; x++)
*((char * )tmp + x) = *((char *)ptr + x);
free(ptr);
return (tmp);
}
else
return (NULL);
}
/******************/ 

}
