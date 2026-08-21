#include "simpleshell.h"

/**
 * read_line - lit une ligne écrite par l'utilisateur
 * Return: la ligne lue ou NULL si on arrive à la fin de l'entrée
 */
char *read_line(void)
{
	/* line va contenir le texte tapé par l'utilisateur */
	char *line = NULL;

	/* len va contenir la taille de la mémoire utilisée par getline */
	size_t len = 0;

	/* read_bytes va contenir le nombre de caractères lus par getline */
	ssize_t read_bytes;

	/* Lit une ligne complète depuis l'entrée standard */
	/* stdin correspond généralement au clavier */
	read_bytes = getline(&line, &len, stdin);

	/* Vérifie si getline n'a pas réussi à lire une ligne */
	/* -1 signifie généralement EOF ou une erreur */
	if (read_bytes == -1)
	{
		/* Libère la mémoire utilisée par getline */
		free(line);

		/* Indique qu'aucune ligne n'a été lue */
		return (NULL);
	}

	/* Retourne la ligne lue */
	return (line);
}

/**
 * handle_line - découpe la ligne et exécute la commande
 * @line: ligne lue depuis l'entrée standard
 * @program: nom du programme du shell utilisé pour les erreurs
 * @line_count: numéro de la ligne actuelle
 * @last_status: code de retour de la dernière commande
 * Return: 0 si tout va bien ou 127 si la commande n'est pas trouvée
 */
int handle_line(char *line, char *program, int line_count, int last_status)
{
	/* argv contient la commande et ses arguments */
	/* path contient le chemin complet de la commande */
	char **argv, *path;

	/* status contient le résultat de la commande exécutée */
	int status;

	/* Découpe la ligne en plusieurs morceaux */
	/* Exemple : "ls -l" devient ["ls", "-l", NULL] */
	argv = strtow(line);

	/* Vérifie si strtow a échoué ou si aucune commande n'a été donnée */
	if (argv == NULL || argv[0] == NULL)
	{
		/* Libère le tableau argv */
		free_array(argv);

		/* Libère la ligne lue */
		free(line);

		/* Rien à exécuter, donc on retourne 0 */
		return (0);
	}

	/* Vérifie si la commande est un builtin comme exit ou env */
	if (handle_builtin(argv, line, last_status))
	{
		/* Libère le tableau argv */
		free_array(argv);

		/* Libère la ligne */
		free(line);

		/* Le builtin a déjà été exécuté */
		return (0);
	}

	/* Cherche où se trouve la commande dans PATH */
	/* Exemple : "ls" peut devenir "/usr/bin/ls" */
	path = find_path(argv[0]);

	/* Vérifie si la commande n'a pas été trouvée */
	if (path == NULL)
	{
		/* Affiche un message d'erreur */
		/* Exemple : ./hsh: 1: ls: not found */
		fprintf(stderr, "%s: %d: %s: not found\n",
			program, line_count, argv[0]);

		/* Libère le tableau argv */
		free_array(argv);

		/* Libère la ligne */
		free(line);

		/* 127 signifie que la commande n'a pas été trouvée */
		return (127);
	}

	/* Lance la commande */
	/* execute utilise fork, execve et wait */
	status = execute(path, argv, program);

	/* Libère la mémoire utilisée pour le chemin */
	free(path);

	/* Libère le tableau contenant la commande et ses arguments */
	free_array(argv);

	/* Libère la ligne lue */
	free(line);

	/* Retourne le résultat de la commande */
	return (status);
}

/**
 * main - fonction principale du shell
 * @argc: nombre d'arguments donnés au programme
 * @argv: tableau contenant les arguments du programme
 * Return: code de retour de la dernière commande exécutée
 */
int main(int argc, char **argv)
{
	/* line contient la ligne tapée par l'utilisateur */
	char *line;

	/* interactive indique si le shell fonctionne avec un terminal */
	/* status contient le dernier code de retour */
	/* line_count compte le nombre de lignes exécutées */
	int interactive, status = 0, line_count = 0;

	/* argc n'est pas utilisé dans notre shell */
	(void)argc;

	/* Vérifie si l'entrée standard est un terminal */
	/* 1 = mode interactif */
	/* 0 = mode non interactif */
	interactive = isatty(STDIN_FILENO);

	/* Boucle principale du shell */
	/* Elle permet au shell de continuer à demander des commandes */
	while (1)
	{
		/* Vérifie si nous sommes en mode interactif */
		if (interactive)
		{
			/* Affiche le prompt du shell */
			printf("$ ");

			/* Force l'affichage immédiat du prompt */
			fflush(stdout);
		}

		/* Attend et lit une ligne */
		line = read_line();

		/* Vérifie si aucune ligne n'a été lue */
		if (line == NULL)
		{
			/* En mode interactif, affiche une nouvelle ligne */
			if (interactive)
				printf("\n");

			/* Sort de la boucle */
			break;
		}

		/* Une nouvelle commande vient d'être lue */
		/* On augmente le numéro de ligne */
		line_count++;

		/* Traite et exécute la commande */
		/* Le résultat devient le nouveau status */
		status = handle_line(line, argv[0], line_count, status);
	}

	/* Retourne le code de la dernière commande */
	return (status);
}