#include "simpleshell.h"
#include <sys/types.h>

/**
 * execute - fork + execve pour exécuter une commande
 * @argv: tableau d'arguments
 *
 * Return: 0 si succès, 1 si erreur
 */
int execute(char **argv)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }

    if (pid == 0)
    {
        if (execve(argv[0], argv, environ) == -1)
        {
            perror("execve");
            exit(1);
        }
    }
    else
    {
        wait(&status);
    }

    return (0);
}
