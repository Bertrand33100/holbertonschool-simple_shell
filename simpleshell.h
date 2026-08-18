#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* ==== INCLUDES required for builtin.c + execute.c ==== */
#include <stdio.h>		/* printf, perror */
#include <stdlib.h>		/* exit */
#include <unistd.h>		/* fork, execve */
#include <string.h>		/* strcmp */
#include <sys/types.h>	/* pid_t */
#include <sys/wait.h>	/* wait */

/* Access to the global environment variable */
extern char **environ;

/* ==== PROTOTYPES used ==== */

/*simpleshell.c*/
char *read_line(void);
int handle_line(char *line, char *prog_name, int line_count, int last_status);
/* token.c */
char **strtow(char *str);
void free_array(char **array);
/* Builtin.c */
int handle_builtin(char **argv, char *line, int last_status);
/* environment.c */
void print_environ(void);
char *_getenv(const char *name);
char *find_path(char *cmd);
/* execute.c */
int execute(char *path, char **argv, char *program);

#endif /* SIMPLE_SHELL_H */
