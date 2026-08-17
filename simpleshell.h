#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <sys/types.h>


int handle_builtin(char **argv);
void print_environ(char **env);
extern char **environ;








#endif