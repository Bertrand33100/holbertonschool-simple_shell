#include "simpleshell.h"

/**
 * read_line - reads line from stdin
 * Return: pointer to the line read or NULL if EOF
*/
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read_bytes;

	read_bytes = getline(&line, &len, stdin);
	if (read_bytes == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * handle_line - tokenizes and executes
 * @line: line read from stdin
 * @program: argv[0] of the shell for error messages
 * @line_count: current line number for error messages
 * @last_status: get the last status generated at exit
 * Return: 0 if success or 127 if the command is not found
 */
int handle_line(char *line, char *program, int line_count, int last_status)
{
	char **argv, *path;
	int status;

	argv = strtow(line);
	if (argv == NULL || argv[0] == NULL)
	{
		free_array(argv);
		free(line);
		return (0);
	}

	if (handle_builtin(argv, line, last_status))
	{
		free_array(argv);
		free(line);
		return (0);
	}

	path = find_path(argv[0]);
	if (path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", program, line_count, argv[0]);
		free_array(argv);
		free(line);
		return (127);
	}

	status = execute(path, argv, program);

	free(path);
	free_array(argv);
	free(line);

	return (status);
}

/**
* main - main function of the shell looping
* @argc: argument count
	* @argv: argument vector where argv[0] is the program name
	* Return: exit status of the last command executed
	*/
int main(int argc, char **argv)
{
	char *line;
	int interactive, status = 0, line_count = 0;

	(void)argc;

	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (interactive)
		{
			printf("$ ");
			fflush(stdout);
		}

		line = read_line();
		if (line == NULL)
		{
			if (interactive)
				printf("\n");
			break;
		}

		line_count++;
		status = handle_line(line, argv[0], line_count, status);
	}
	return (status);
}
