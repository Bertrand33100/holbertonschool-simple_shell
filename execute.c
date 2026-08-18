#include "simpleshell.h"

/**
 * execute - fork + execve to execute a command
 * @argv: array of arguments
 * @path: full path already resolved
 * @program: first argument of the shell
 * Return: 0 on success, 1 on error
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
            return (WEXITSTATUS(status));
    }

    return (1);
}
