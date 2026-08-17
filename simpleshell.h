#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* ==== INCLUDES nécessaires pour builtin.c + execute.c ==== */
#include <stdio.h>       /* printf, perror */
#include <stdlib.h>      /* exit */
#include <unistd.h>      /* fork, execve */
#include <string.h>      /* strcmp */
#include <sys/types.h>   /* pid_t */
#include <sys/wait.h>    /* wait */

/* Accès à la variable globale environ */
extern char **environ;

/* ==== PROTOTYPES utilisés ==== */
int handle_builtin(char **argv);
int execute(char **argv);
void print_environ(char **env);

#endif /* SIMPLE_SHELL_H */
