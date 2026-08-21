#include "simpleshell.h"

/**
 * handle_builtin - vérifie et exécute une commande intégrée
 * @argv: tableau qui contient les commandes et leurs arguments
 * @line: ligne complète récupérée avec getline
 * @last_status: dernier code de retour du shell
 * Return: 1 si une commande intégrée a été exécutée, 0 sinon
 */
int handle_builtin(char **argv, char *line, int last_status)
{
	/* Vérifie si la commande tapée est "exit" */
	if (strcmp(argv[0], "exit") == 0)
	{
		/* Libère la mémoire utilisée par le tableau argv */
		free_array(argv);

		/* Libère la mémoire utilisée pour la ligne lue avec getline */
		free(line);

		/* Ferme le shell avec le dernier code de retour */
		exit(last_status);
	}

	/* Vérifie si la commande tapée est "env" */
	if (strcmp(argv[0], "env") == 0)
	{
		/* Affiche toutes les variables d'environnement */
		print_environ();

		/* Indique qu'une commande intégrée a bien été exécutée */
		return (1);
	}

	/* La commande n'est pas une commande intégrée */
	return (0);
}