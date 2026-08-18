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
/*simpleshell.c*/

/* token.c */
char **strtow(char *str);
void free_array(char **array);
/* Builtin.c */
int handle_builtin(char **argv);
/* environment.c */
void print_environ(void);
char *_getenv(const char *name);
char *find_path(char *cmd);
/* execute.c */
int execute(char **argv);

#endif /* SIMPLE_SHELL_H */