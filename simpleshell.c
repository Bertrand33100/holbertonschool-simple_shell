#include <simpleshell.h>

/*

*/

int start_shell(void)
{
    char *line = NULL;
    size_t len = 0;

    while(1)
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");
        if (getline(&line, &len, stdin) == -1)
            free (line);
            return (0);
    }
}