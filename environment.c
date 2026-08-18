#include "simpleshell.h"

/**
 * print_environ - prints the current environment
 */
void print_environ(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the variable to check
 * Return: pointer to the value in environ or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	size_t len;

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}
	return (NULL);
}

/**
 * build_path - builds "dir/cmd" as a newly allocated string
 * @dir: directory name
 * @cmd: command name
 * Return: pointer to the new path or NULL if fail
 */
static char *build_path(char *dir, char *cmd)
{
	char *full;
	size_t len;

	len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	if (full == NULL)
		return (NULL);
	sprintf(full, "%s/%s", dir, cmd);
	return (full);
}

/**
 * find_path - find the path of a command
 * @cmd: command name
 * Return: new path or NULL if not found
 */
char *find_path(char *cmd)
{
	char *path_value, *path_copy, *dir, *full;

	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) != 0)
			return (NULL);
		full = malloc(strlen(cmd) + 1);
		if (full != NULL)
			strcpy(full, cmd);
		return (full);
	}

	path_value = _getenv("PATH");
	if (path_value == NULL)
		return (NULL);

	path_copy = malloc(strlen(path_value) + 1);
	if (path_copy == NULL)
		return (NULL);
	strcpy(path_copy, path_value);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full = build_path(dir, cmd);
		if (full != NULL && access(full, X_OK) == 0)
		{
			free(path_copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
