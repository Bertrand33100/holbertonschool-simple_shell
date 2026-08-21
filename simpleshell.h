#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/*
 * Cette ligne évite que le fichier .h soit chargé plusieurs fois.
 * C'est ce qu'on appelle une "protection contre les inclusions multiples".
 *
 * Exemple :
 * si plusieurs fichiers utilisent #include "simpleshell.h",
 * le compilateur ne va pas recopier tout le contenu plusieurs fois.
 */

/* ============================================================
 * BIBLIOTHÈQUES NÉCESSAIRES
 * ============================================================ */

/* stdio.h contient notamment printf(), perror() et fprintf() */
#include <stdio.h>

/* stdlib.h contient notamment malloc(), free() et exit() */
#include <stdlib.h>

/* unistd.h contient notamment fork(), execve(), access() et isatty() */
#include <unistd.h>

/* string.h contient notamment strcmp(), strlen(), strcpy() et strtok() */
#include <string.h>

/* sys/types.h contient notamment le type pid_t utilisé par fork() */
#include <sys/types.h>

/* sys/wait.h contient les fonctions et macros utilisées avec wait() */
#include <sys/wait.h>


/*
 * environ est une variable fournie par le système.
 *
 * Elle contient les variables d'environnement du programme.
 *
 * Exemple :
 *
 * environ
 *    |
 *    ├── "PATH=/usr/local/bin:/usr/bin:/bin"
 *    ├── "HOME=/home/user"
 *    ├── "USER=user"
 *    └── NULL
 *
 * "extern" signifie que la variable existe ailleurs.
 * Ici, on indique simplement au compilateur que nous voulons l'utiliser.
 */
extern char **environ;


/* ============================================================
 * PROTOTYPES DES FONCTIONS
 * ============================================================ */

/*
 * ============================================================
 * simpleshell.c
 * ============================================================
 */

/*
 * Lit une ligne écrite par l'utilisateur.
 *
 * Exemple :
 *
 * utilisateur tape : ls -l
 *
 * read_line() retourne la ligne "ls -l".
 */
char *read_line(void);


/*
 * Traite une ligne de commande.
 *
 * Elle va notamment :
 * 1. découper la ligne ;
 * 2. vérifier les builtins ;
 * 3. chercher la commande dans PATH ;
 * 4. exécuter la commande.
 */
int handle_line(char *line, char *prog_name, int line_count, int last_status);


/*
 * ============================================================
 * token.c
 * ============================================================
 */

/*
 * Découpe une chaîne de caractères en plusieurs morceaux.
 *
 * Exemple :
 *
 * "ls -l /tmp"
 *
 * devient :
 *
 * argv[0] = "ls"
 * argv[1] = "-l"
 * argv[2] = "/tmp"
 * argv[3] = NULL
 */
char **strtow(char *str);


/*
 * Libère la mémoire utilisée par un tableau de chaînes.
 *
 * Ici, elle sert notamment à libérer argv après son utilisation.
 */
void free_array(char **array);


/*
 * ============================================================
 * builtin.c
 * ============================================================
 */

/*
 * Vérifie si la commande est un builtin.
 *
 * Dans notre shell, les builtins sont notamment :
 *
 * exit
 * env
 *
 * Retourne :
 *
 * 1 = un builtin a été trouvé et exécuté
 * 0 = ce n'est pas un builtin
 */
int handle_builtin(char **argv, char *line, int last_status);


/*
 * ============================================================
 * environment.c
 * ============================================================
 */

/*
 * Affiche toutes les variables d'environnement.
 *
 * Exemple :
 *
 * PATH=/usr/bin:/bin
 * HOME=/home/user
 * USER=user
 */
void print_environ(void);


/*
 * Cherche une variable d'environnement.
 *
 * Exemple :
 *
 * _getenv("PATH")
 *
 * retourne la valeur de PATH.
 */
char *_getenv(const char *name);


/*
 * Cherche le chemin complet d'une commande.
 *
 * Exemple :
 *
 * find_path("ls")
 *
 * peut retourner :
 *
 * /usr/bin/ls
 */
char *find_path(char *cmd);


/*
 * ============================================================
 * execute.c
 * ============================================================
 */

/*
 * Exécute une commande.
 *
 * Cette fonction utilise notamment :
 *
 * fork()  → crée un processus enfant
 * execve() → lance le programme
 * wait() → le parent attend l'enfant
 */
int execute(char *path, char **argv, char *program);


/*
 * Fin de la protection contre les inclusions multiples.
 */
#endif /* SIMPLE_SHELL_H */