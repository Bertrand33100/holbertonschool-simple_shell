#include "simpleshell.h"

/**
 * execute - fork + execve pour exécuter une commande
 * @argv: tableau d'arguments
 *
 * Return: 0 si succès, 1 si erreur
 */
int execute(char *path, char **argv, char *program)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror(program);
        return (1);
    }

    if (pid == 0)
    {
        if (execve(path, argv, environ) == -1)
        {
            fprintf(stderr, "%s: ", program);
            perror(path);
            exit(127);
        }
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
            return (weitstatus(status));
    }

    return (1);
}
