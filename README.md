*This project has been created as part of the 42 curriculum by Hhervieu, Jbayet.*

[![jbayet's 42 stats](https://42cv.dev/api/badge/cmmevnk9g0006n286hxhjp6au/stats?cursusId=21&coalitionId=piscine)](https://42cv.dev)
[![hhervieu's 42 stats](https://42cv.dev/api/badge/cmmkqicmn0000pkpd0wgzlibp/stats?cursusId=21&coalitionId=48)](https://42cv.dev)
# Minishell

## Description

Minishell is a simplified Unix shell written in C.
The goal of this project is to understand how a shell works internally by recreating some of the core features of bash.

The program reads and interprets user commands, executes them, and handles system interactions such as process creation, pipes, redirections, and environment variables.

Through this project, students learn about:
- process management (`fork`, `execve`, `wait`)
- file descriptors and redirections
- pipes and inter-process communication
- signal handling
- parsing and tokenization of user input

Minishell aims to reproduce the behavior of basic shell commands while respecting the constraints of the 42 school.

## Instructions

### Compilation

Clone the repository and compile the project using:

```make```

This will generate the executable:

```minishell```

### Execution

Run the shell with:

```./minishell```

You can then type commands just like in a standard shell.

Example:

```minishell$ ls -la```\
```minishell$ echo Hello World```\
```minishell$ cat file.txt | grep word```\
```Cleaning```\
```make clean```\
```make fclean```\
```make re```\

## Resources

The following resources were used to better understand shell implementation and Unix system programming:

- The Linux manual pages (man fork, man execve, man pipe, man dup2)
- The GNU Bash reference manual
- The POSIX documentation
- Various Unix programming tutorials and articles

## AI Usage

AI tools were used only as learning support, mainly for:

- understanding system calls and shell concepts
- clarifying theoretical aspects of parsing and process management
- reviewing explanations of C programming concepts

All code was written and implemented manually in accordance with the rules of the 42 project.
