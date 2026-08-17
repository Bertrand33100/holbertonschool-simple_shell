#include "simpleshell.h"

/**
 * strtow - converts a string into words
 * @str: string to be converted into words
 * Return: array of words ended by '\0' or NULL if alloc fail
 */
 char **strtow(char *str)
{
    int i, j;
    char *token, **array, *copy;
    const char *separators = " \t\n";

    copy = malloc(strlen(str) +1);
    if (copy == NULL)
        return (NULL);
    strcpy(copy, str);

    token = strtok(copy, separators);
    for (i = 0; token != NULL; i++)
        token = strtok(NULL, separators);
    free(copy);

    array = malloc(sizeof(char *) * (i + 1));
    if (array == NULL)
        return (NULL);
    
    token = strtok(str, separators);
    for (j = 0; token != NULL; j++)
    {
        array[j] = malloc(strlen(token) +1);
        if (array[j] == NULL)
        {
            while (j > 0)
                free (array[--j]);
            free (array);
            return (NULL);
        }
        strcpy(array[j], token);
        token = strtok(NULL, separators);
    }
    array[j] = NULL;
    return (array);
}

/**
 * free_array - frees the array
 * @array: array to be freed
 */
void free_array(char **array)
{
    int k;

    if (array == NULL)
        return;
    for (k = 0; array[k] != NULL; k++)
        free(array[k]);
    free(array);
}