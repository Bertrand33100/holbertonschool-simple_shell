#include "simpleshell.h"

/**
 * print_prompt - Affiche le prompt
 *
 * Return: rien
 */
void print_prompt(void)
{
    	write(STDOUT_FILENO, "$ ", 2);
}

ssize_t read_input(char **line, size_t *len)
{
	return (getline(line, len, stdin));
}
