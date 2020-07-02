#include "tools.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

int cd(char **args, Redirections *r)
{
    return 0;
}
int clr(char **args, Redirections *r)
{
    return 0;
}
int dir(char **args, Redirections *r)
{
    return 0;
}
int env(char **args, Redirections *r)
{
    return 0;
}
int echo(char **args, Redirections *r)
{
    return 0;
}
int hlp(char **args, Redirections *r)
{
    return 0;
}
int paus(char **args, Redirections *r)
{
    return 0;
}
int quit(char **args, Redirections *r)
{
    return 0;
}

void monshell_cmdline()
{
    char *line;
    Arguments* argv;
    Redirections *r;
    int code;

    do
    {
        fprintf(stdout, "> ");
        line = read_line();
        argv = parse_args(line);
        r = handle_redirection(argv);
        code = run(argv->args, r);

        free(line);
        free(argv->args);
    } while (code);
}

void monshell_batchfile(FILE *file)
{
    char *line = NULL;
    Arguments* argv;
    Redirections *r;

    size_t len = 0;

    while (getline(&line, &len, file) != -1)
    {
        fprintf(stdout, "> ");

        argv = parse_args(line);
        r = handle_redirection(argv);
        run(argv->args, r);

        free(argv->args);
    }
    free(line);
}

char *read_line()
{
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(EXIT_SUCCESS); // We recieved an EOF
        }
        else
        {
            perror("monshell---getline\n");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

Arguments *parse_args(char *args) {
    Arguments* p=
}
Redirections *handle_redirection(Arguments *redirections) {}

int run(char **args, Redirections *r)
{
}

int run_external(char **args)
{
    pid_t pid;
    int child_status;

    pid = fork();
    if (pid == -1)
    {
        perror("Echec du fork");
    }
    else if (pid == 0)
    {
        // Processus fils
        execvp(args[0], args);
        perror("Echec d'exec");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Processus parent
        wait(&child_status);
        return child_status;
    }

    return EXIT_SUCCESS;
}