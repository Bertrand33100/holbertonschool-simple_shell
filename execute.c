#include "simpleshell.h"

/**
 * execute - crée un processus et exécute une commande avec execve
 * @path: chemin complet du programme à exécuter
 * @argv: tableau contenant la commande et ses arguments
 * @program: nom du programme lancé par le shell
 * Return: 0 si tout s'est bien passé, 1 en cas d'erreur
 */
int execute(char *path, char **argv, char *program)
{
	/* pid va contenir le numéro du processus créé avec fork */
	pid_t pid;

	/* status va contenir le résultat du processus enfant */
	int status;

	/* Crée un nouveau processus */
	pid = fork();

	/* Vérifie si fork() n'a pas réussi */
	if (pid == -1)
	{
		/* Affiche le nom du programme et le message d'erreur */
		perror(program);

		/* Retourne 1 pour indiquer qu'il y a eu une erreur */
		return (1);
	}

	/* Si pid vaut 0, nous sommes dans le processus enfant */
	if (pid == 0)
	{
		/* Essaie de lancer le programme demandé */
		/* path = chemin du programme */
		/* argv = commande + arguments */
		/* environ = variables d'environnement */
		if (execve(path, argv, environ) == -1)
		{
			/* Affiche le nom du programme suivi de ": " */
			fprintf(stderr, "%s: ", program);

			/* Affiche l'erreur liée au chemin du programme */
			perror(path);

			/* Ferme le processus enfant avec le code d'erreur 127 */
			exit(127);
		}
	}
	else
	{
		/* Nous sommes dans le processus parent */
		/* Attend que le processus enfant ait terminé */
		wait(&status);

		/* Vérifie si le processus enfant s'est terminé normalement */
		if (WIFEXITED(status))
			/* Récupère le code de retour de l'enfant */
			return (WEXITSTATUS(status));
	}

	/* Retourne 1 si aucun résultat normal n'a été retourné */
	return (1);
}