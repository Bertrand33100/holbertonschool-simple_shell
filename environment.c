#include "simpleshell.h"

/**
 * print_environ - affiche toutes les variables d'environnement
 */
void print_environ(void)
{
	/* i sert à savoir sur quelle ligne du tableau environ nous sommes */
	int i;

	/* On commence à la première variable et on avance une par une */
	/* On s'arrête lorsque environ[i] contient NULL */
	for (i = 0; environ[i] != NULL; i++)
		/* Affiche la variable d'environnement à l'écran */
		printf("%s\n", environ[i]);
}

/**
 * _getenv - cherche une variable dans l'environnement
 * @name: nom de la variable que l'on cherche
 * Return: sa valeur ou NULL si elle n'existe pas
 */
char *_getenv(const char *name)
{
	/* i sert à parcourir toutes les variables de environ */
	int i;

	/* len va contenir la longueur du nom que l'on cherche */
	size_t len;

	/* Compte le nombre de caractères dans name */
	/* Exemple : "PATH" contient 4 caractères */
	len = strlen(name);

	/* Parcourt toutes les variables de l'environnement */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Vérifie si le début de la variable correspond au nom recherché */
		/* Exemple : si on cherche "PATH", on cherche une ligne qui commence par PATH */
		/* Vérifie aussi que le caractère juste après est '=' */
		/* Cela évite de confondre PATH avec une autre variable comme PATH_TEST */
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			/* Retourne ce qui se trouve après le signe '=' */
			/* Exemple : PATH=/bin:/usr/bin */
			/* On retourne seulement /bin:/usr/bin */
			return (environ[i] + len + 1);
	}

	/* La variable n'existe pas */
	return (NULL);
}

/**
 * build_path - construit le chemin complet d'une commande
 * @dir: dossier dans lequel chercher
 * @cmd: nom de la commande
 * Return: nouveau chemin ou NULL si malloc échoue
 */
static char *build_path(char *dir, char *cmd)
{
	/* full va contenir le chemin complet */
	char *full;

	/* len va contenir la taille nécessaire pour créer le chemin */
	size_t len;

	/* Calcule la place nécessaire en mémoire */
	/* strlen(dir) = taille du dossier */
	/* strlen(cmd) = taille de la commande */
	/* +2 = un caractère pour '/' et un pour '\0' */
	len = strlen(dir) + strlen(cmd) + 2;

	/* Demande à l'ordinateur de réserver cette place en mémoire */
	full = malloc(len);

	/* Vérifie si malloc n'a pas réussi à réserver la mémoire */
	if (full == NULL)
		/* Si ça n'a pas fonctionné, on retourne NULL */
		return (NULL);

	/* Met le dossier, '/', puis la commande dans full */
	/* Exemple : dir = "/bin" et cmd = "ls" */
	/* Résultat : "/bin/ls" */
	sprintf(full, "%s/%s", dir, cmd);

	/* Retourne le chemin que nous venons de construire */
	return (full);
}

/**
 * find_path - cherche où se trouve une commande
 * @cmd: nom de la commande
 * Return: chemin complet de la commande ou NULL si elle n'est pas trouvée
 */
char *find_path(char *cmd)
{
	/* path_value = contient le PATH de l'ordinateur */
	/* path_copy = copie de PATH que l'on peut modifier */
	/* dir = contient un dossier de PATH */
	/* full = contient le chemin complet de la commande */
	char *path_value, *path_copy, *dir, *full;

	/* Vérifie si la commande contient déjà un '/' */
	/* Exemple : "./main" ou "/bin/ls" */
	if (strchr(cmd, '/') != NULL)
	{
		/* Vérifie si cette commande existe et peut être exécutée */
		if (access(cmd, X_OK) != 0)
			/* Si elle n'est pas exécutable, on retourne NULL */
			return (NULL);

		/* Réserve de la mémoire pour copier le nom de la commande */
		full = malloc(strlen(cmd) + 1);

		/* Vérifie que malloc a bien réservé la mémoire */
		if (full != NULL)
			/* Copie cmd dans full */
			strcpy(full, cmd);

		/* Retourne le chemin de la commande */
		return (full);
	}

	/* On demande la valeur de PATH */
	/* Exemple : /usr/local/bin:/usr/bin:/bin */
	path_value = _getenv("PATH");

	/* Vérifie si PATH existe */
	if (path_value == NULL)
		/* Si PATH n'existe pas, on ne peut pas chercher la commande */
		return (NULL);

	/* Réserve de la mémoire pour faire une copie de PATH */
	path_copy = malloc(strlen(path_value) + 1);

	/* Vérifie si malloc a réussi */
	if (path_copy == NULL)
		/* Si malloc échoue, on arrête la recherche */
		return (NULL);

	/* Copie PATH dans path_copy */
	/* On fait une copie car strtok va modifier la chaîne */
	strcpy(path_copy, path_value);

	/* Prend le premier dossier de PATH */
	/* ':' sert à séparer les différents dossiers */
	/* Exemple : "/usr/bin:/bin" */
	/* Premier dossier = "/usr/bin" */
	dir = strtok(path_copy, ":");

	/* Continue tant qu'il reste un dossier à tester */
	while (dir != NULL)
	{
		/* Construit le chemin avec le dossier et la commande */
		/* Exemple : "/usr/bin" + "/" + "ls" */
		/* Résultat : "/usr/bin/ls" */
		full = build_path(dir, cmd);

		/* Vérifie si le fichier existe et peut être exécuté */
		if (full != NULL && access(full, X_OK) == 0)
		{
			/* On n'a plus besoin de la copie de PATH */
			free(path_copy);

			/* On a trouvé la commande */
			/* On retourne son chemin complet */
			return (full);
		}

		/* Ce chemin n'était pas le bon */
		/* On libère la mémoire utilisée pour ce chemin */
		free(full);

		/* Passe au dossier suivant dans PATH */
		/* Exemple : après /usr/bin, on passe à /bin */
		dir = strtok(NULL, ":");
	}

	/* On a testé tous les dossiers sans trouver la commande */
	/* On libère la mémoire utilisée pour la copie de PATH */
	free(path_copy);

	/* La commande n'a pas été trouvée */
	return (NULL);
}