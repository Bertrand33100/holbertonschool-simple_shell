# Simple Shell

### By **Eva Galiano** & **Bertrand Oeung**

**Holberton School – 2026**

## Overview

This project is a basic implementation of a Unix command interpreter.

Our goal was to understand how a shell works internally: reading user input, parsing commands, creating processes, and executing programs using system calls.

## Features

* Displays a prompt
* Reads user input
* Tokenizes commands
* Executes programs using `fork()` and `execve()`
* Waits for child processes
* Handles simple errors
* Supports built-in commands:

  * `exit` – closes the shell
  * `env` – prints environment variables

## Allowed Functions

We followed Holberton School's restrictions and used authorized functions such as:

* `fork`
* `execve`
* `wait`
* `perror`
* `getline`
* `strtok`
* `malloc`
* `free`
* `write`
* `access`
* `stat`

and other functions permitted by the project requirements.

## File Structure

```text
builtin.c        # Built-in commands such as exit and env
execute.c        # Process creation and command execution
env.c            # Environment management and printing
getline.c        # Reading user input
token.c          # Tokenizing commands
simpleshell.c    # Main shell loop
simpleshell.h    # Header file and function prototypes
```

## Compilation

Compile the project with:

```bash
gcc -Wall -Wextra -Werror -pedantic *.c -o hsh
```

## Usage

Start the shell:

```bash
./hsh
```

Example:

```text
$ ls
$ env
$ exit
```

The shell reads the command entered by the user, processes it, and executes the requested program when appropriate.

## Authors

This project was created by **Eva Galiano** and **Bertrand Oeung** as part of the **Holberton School** curriculum in 2026.
