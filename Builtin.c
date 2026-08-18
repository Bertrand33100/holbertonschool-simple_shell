#include "simpleshell.h"

/**
 * handle_builtin - Vérifie et exécute un builtin
 * @argv: tableau d'arguments
 *
 * Return: 1 si un builtin a été exécuté, 0 sinon
 */
int handle_builtin(char **argv, char *line)

{
    /* builtin: exit */
    if (strcmp(argv[0], "exit") == 0)
    {
        
        free_array(argv);
        free(line);
        exit(0);
    }

    /* builtin: env */
    if (strcmp(argv[0], "env") == 0)
    {
        print_environ();
        return (1);
    }

    return (0);
}
