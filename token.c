#include "simpleshell.h"

/**
 * strtow - transforme une phrase en plusieurs mots
 * @str: phrase à découper
 * Return: tableau contenant les mots ou NULL si malloc échoue
 */
char **strtow(char *str)
{
	/* i sert à compter combien de mots nous avons trouvés */
	int i;

	/* j sert à parcourir les mots une deuxième fois */
	int j;

	/* token va contenir un mot trouvé dans la phrase */
	char *token;

	/* array va contenir tous les mots */
	char **array;

	/* copy va contenir une copie de la phrase */
	char *copy;

	/* Ces caractères servent à séparer les mots */
	/* espace, tabulation et retour à la ligne */
	const char *separators = " \t\n";

	/* Réserve de la mémoire pour faire une copie de la phrase */
	/* +1 permet de garder de la place pour '\0' à la fin */
	copy = malloc(strlen(str) + 1);

	/* Vérifie si malloc a réussi */
	if (copy == NULL)
		/* Si malloc échoue, on retourne NULL */
		return (NULL);

	/* Copie la phrase originale dans copy */
	strcpy(copy, str);

	/* Cherche le premier mot dans la copie */
	/* strtok va utiliser espace, tabulation et '\n' comme séparateurs */
	token = strtok(copy, separators);

	/* Continue tant qu'un mot est trouvé */
	for (i = 0; token != NULL; i++)
		/* Cherche le mot suivant */
		token = strtok(NULL, separators);

	/* La copie ne sert plus, donc on libère sa mémoire */
	free(copy);

	/* Réserve de la mémoire pour le tableau de mots */
	/* +1 permet de garder une place pour NULL à la fin */
	array = malloc(sizeof(char *) * (i + 1));

	/* Vérifie si malloc a réussi */
	if (array == NULL)
		/* Si malloc échoue, on retourne NULL */
		return (NULL);

	/* Recommence depuis le début de la phrase originale */
	/* On va maintenant réellement copier chaque mot */
	token = strtok(str, separators);

	/* Parcourt tous les mots trouvés */
	for (j = 0; token != NULL; j++)
	{
		/* Réserve la mémoire nécessaire pour le mot */
		/* +1 permet de garder une place pour '\0' */
		array[j] = malloc(strlen(token) + 1);

		/* Vérifie si malloc a réussi */
		if (array[j] == NULL)
		{
			/* Si malloc échoue, il faut libérer les mots déjà créés */
			while (j > 0)
				/* Diminue j puis libère le mot correspondant */
				free(array[--j]);

			/* Libère également le tableau */
			free(array);

			/* Signale l'échec */
			return (NULL);
		}

		/* Copie le mot trouvé dans la mémoire réservée */
		strcpy(array[j], token);

		/* Passe au mot suivant */
		token = strtok(NULL, separators);
	}

	/* Met NULL après le dernier mot */
	/* Cela permet de savoir où le tableau s'arrête */
	array[j] = NULL;

	/* Retourne le tableau contenant tous les mots */
	return (array);
}

/**
 * free_array - libère la mémoire du tableau de mots
 * @array: tableau à libérer
 */
void free_array(char **array)
{
	/* k sert à parcourir le tableau */
	int k;

	/* Vérifie si le tableau existe */
	if (array == NULL)
		/* Si le tableau n'existe pas, il n'y a rien à libérer */
		return;

	/* Parcourt tous les mots du tableau */
	/* On s'arrête lorsque l'on trouve NULL */
	for (k = 0; array[k] != NULL; k++)
		/* Libère la mémoire utilisée par chaque mot */
		free(array[k]);

	/* Une fois tous les mots libérés, libère le tableau lui-même */
	free(array);
}