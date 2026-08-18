#include "simpleshell.h"

/**
 * handle_builtin - Check and execute a builtin command
 * @argv: array of arguments
 * @line: raw line read by getline
 * Return: 1 if a builtin was executed, 0 otherwise
 */
int handle_builtin(char **argv, char *line, int last_status)
{
    /* builtin: exit */
    if (strcmp(argv[0], "exit") == 0)
    {
        free_array(argv);
        free(line);
        exit(last_status);
    }

    /* builtin: env */
    if (strcmp(argv[0], "env") == 0)
    {
        print_environ();
        return (1);
    }

    return (0);
}
