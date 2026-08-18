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

## Flowchart

The following flowchart represents the main execution process of our Simple Shell:

<img width="3028" height="3920" alt="Flowchart" src="https://github.com/user-attachments/assets/b9c27652-3640-4542-804a-f706a42fcc04" />


The flowchart shows the different stages of the shell:

1. Check whether the shell is running in a terminal.
2. Display the prompt in interactive mode.
3. Read the command using `getline`.
4. Check for `EOF`.
5. Tokenize the command.
6. Check whether the command is a built-in.
7. Handle `exit` or `env` when applicable.
8. Search for the command using `PATH`.
9. Create a child process with `fork()`.
10. Execute the command with `execve()`.
11. The parent waits for the child process.
12. Free allocated memory.
13. Return to the shell prompt.

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
environment.c    # Environment management and printing
token.c          # Tokenizing commands
getline.c        # Reading user input
simpleshell.c    # Main shell loop
simpleshell.h    # Header file and function prototypes
