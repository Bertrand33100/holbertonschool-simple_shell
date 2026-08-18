## Tests et vérifications

Cette section regroupe les commandes utilisées pour vérifier le respect du style Betty, compiler le projet et tester le fonctionnement du shell.

### 1. Vérification Betty

#### Vérifier tous les fichiers `.c`

```bash
betty *.c
```

#### Vérifier tous les fichiers `.h`

```bash
betty *.h
```

#### Vérifier la documentation des fonctions

```bash
betty-doc *.c
```

Une absence de message d'erreur indique que les fichiers respectent les règles vérifiées par Betty.

---

### 2. Compilation complète

Pour compiler tous les fichiers `.c` du projet en une seule commande :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-long-long *.c -o hsh
```

Les options utilisées sont celles demandées pour le projet :

* `-Wall` : active de nombreux avertissements.
* `-Werror` : transforme les avertissements en erreurs.
* `-Wextra` : active des avertissements supplémentaires.
* `-pedantic` : vérifie la conformité au standard.
* `-std=gnu89` : utilise le standard GNU C89.
* `-Wno-long-long` : désactive l'avertissement concernant `long long`.
* `*.c` : sélectionne tous les fichiers C présents dans le dossier.
* `-o hsh` : crée l'exécutable nommé `hsh`.

Pour vérifier que l'exécutable a bien été créé :

```bash
ls -l hsh
```

---

### 3. Compilation propre

Pour supprimer l'ancien exécutable avant de recompiler :

```bash
rm -f hsh
```

Puis :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-long-long *.c -o hsh
```

---

### 4. Test du mode interactif

Lancer le shell :

```bash
./hsh
```

Tester plusieurs commandes :

```text
ls
pwd
echo Hello
env
exit
```

Le shell doit exécuter les commandes puis retourner son prompt après chaque commande.

---

### 5. Test du mode non interactif

Le shell peut également recevoir des commandes depuis l'entrée standard.

#### `pwd`

```bash
printf "pwd\n" | ./hsh
```

#### `ls`

```bash
printf "ls\n" | ./hsh
```

#### `echo`

```bash
printf "echo Hello\n" | ./hsh
```

#### Plusieurs commandes

```bash
printf "pwd\nls\necho Hello\n" | ./hsh
```

---

### 6. Test des builtins

#### `exit`

```bash
printf "exit\n" | ./hsh
```

#### `env`

```bash
printf "env\n" | ./hsh
```

#### `echo`

```bash
printf "echo Hello World\n" | ./hsh
```

---

### 7. Test d'une commande inexistante

```bash
printf "azertyuiop\n" | ./hsh
```

Le shell doit afficher un message d'erreur et ne doit pas provoquer de crash.

Tester également que le shell continue après l'erreur :

```bash
printf "azertyuiop\npwd\n" | ./hsh
```

Le shell doit signaler l'erreur puis exécuter `pwd`.

---

### 8. Test de l'environnement

Afficher les variables d'environnement :

```bash
printf "env\n" | ./hsh
```

Tester également `PATH` :

```bash
printf "echo $PATH\n" | ./hsh
```

---

### 9. Test de EOF

Lancer le shell :

```bash
./hsh
```

Puis utiliser :

```text
Ctrl + D
```

Le shell doit quitter proprement.

Test en mode non interactif :

```bash
./hsh < /dev/null
```

---

### 10. Test Valgrind

Pour rechercher les erreurs et fuites mémoire :

```bash
valgrind --leak-check=full --show-leak-kinds=all ./hsh
```

Pour tester plusieurs commandes :

```bash
printf "pwd\nls\necho Hello\nexit\n" | valgrind --leak-check=full --show-leak-kinds=all ./hsh
```

À vérifier dans le résultat :

```text
definitely lost: 0 bytes in 0 blocks
```

et :

```text
ERROR SUMMARY: 0 errors
```

---

### 11. Vérification Git

Vérifier l'état du dépôt :

```bash
git status
```

Vérifier les erreurs d'espacement détectables par Git :

```bash
git diff --check
```

Voir les modifications :

```bash
git diff
```

Voir les fichiers suivis et non suivis :

```bash
git status
```

---

### 12. Pré-check complet

Avant un commit, il est possible de lancer une vérification regroupant Betty et la compilation :

```bash
betty *.c && betty *.h && gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-long-long *.c -o hsh
```

Si toutes les commandes réussissent, aucun message d'erreur ne doit apparaître.

---

### 13. Test complet du shell

Après une compilation réussie :

```bash
printf "pwd\nls\necho Hello\nenv\nazertyuiop\npwd\nexit\n" | ./hsh
```

Ce test vérifie notamment :

* l'exécution de `pwd` ;
* l'exécution de `ls` ;
* l'exécution de `echo` ;
* le builtin `env` ;
* la gestion d'une commande inexistante ;
* la capacité à continuer après une erreur ;
* la sortie avec `exit`.

---

### 14. Commande de pré-vérification avant GitHub

Commande recommandée avant un `git add` :

```bash
betty *.c && betty *.h && gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-long-long *.c -o hsh && printf "pwd\nls\necho Hello\nenv\nazertyuiop\npwd\nexit\n" | ./hsh
```

Puis vérifier Git :

```bash
git status
```

```bash
git diff --check
```

Une fois les vérifications terminées :

```bash
git add .
```

Puis :

```bash
git commit -m "Run shell tests and validation"
```

Et enfin :

```bash
git push origin master
```

> **Note:** ces commandes permettent de vérifier le style Betty, la compilation et plusieurs comportements fonctionnels du projet. Elles ne garantissent pas à elles seules le passage de l'ensemble des tests automatisés ou du manual review de Holberton School.
