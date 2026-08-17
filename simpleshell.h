#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

int handle_builtin(char **argv);
void print_environment(char **env);
extern char **environ;








#endif