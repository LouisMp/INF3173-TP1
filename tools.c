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
    Arguments *argv;
    Redirections r = {false, "", false, "", false, "", false};
    int code;

    do
    {
        fprintf(stdout, "[monshell]> ");
        line = read_line();
        argv = parse_args(line);
        handle_redirection(argv, &r);
        code = run(argv->args, &r);

        free(line);
        free(argv->args);
    } while (code);
}

void monshell_batchfile(FILE *file)
{
    char *line = NULL;
    Arguments *argv;
    Redirections r = {false, "", false, "", false, "", false};

    size_t len = 0;

    while (getline(&line, &len, file) != -1)
    {
        fprintf(stdout, "[monshell]> ");

        argv = parse_args(line);
        handle_redirection(argv, &r);
        run(argv->args, &r);

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
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("monshell---getline\n");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

Arguments *parse_args(char *args)
{
    Arguments *p = NULL;
    char *delim = " \t\r\n\a";
    int taille = DEFAUT_ARG_NUMBER, position = 0;
    char **argvv = malloc(taille * sizeof(char *));
    char *token, **backup;

    if (!argvv)
    {
        fprintf(stderr, "monshell--erreur d'allocation\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(args, delim);
    while (token != NULL)
    {
        argvv[position] = token;
        position++;

        if (position >= taille)
        {
            taille += DEFAUT_ARG_NUMBER;
            backup = argvv;
            argvv = realloc(argvv, taille * sizeof(char *));
            if (!argvv)
            {
                free(backup);
                fprintf(stderr, "monshell--erreur d'allocation\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, delim);
    }
    argvv[position] = NULL;
    p->argc = position;
    p->args = argvv;
    return p;
}

void handle_redirection(Arguments *redirections, Redirections* r) {
    int i;
    int j;

      for(i = 0; args[i] != NULL; i++) {

        // Look for the >
        if(args[i][0] == '>') {
          //free(args[i]);

          // Get the filename 
          if(args[i+1] != NULL) {
        *output_filename = args[i+1];
          } else {
        return -1;
          }

          // Adjust the rest of the arguments in the array
          for(j = i; args[j-1] != NULL; j++) {
        args[j] = args[j+2];
          }

          return 1;
        }
      }

      return 0;
}

int run(char **args, Redirections *r)
{
    int i;

  if (args[0] == NULL) {
    // Rien entré
    return 1;
  }

  for (i = 0; i < INTERNAL_FUNCTION_NUMBER; i++) {
    if (strcmp(args[0], internal_command_list[i]) == 0) {
      return (*internal_functions[i])(args, r);
    }
  }

  return run_external(args, r);
}

int run_external(char **args, Redirections *r)
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
        if(r->in==true) freopen(r->in_filename, "r", stdin);
        if(r->out==true) freopen(r->out_filename,"w",stdout);
        if (r->append==true) freopen(r->a_filename, "a", stdout);
        // Processus fils
        execvp(args[0], args);
        perror("Echec d'exec");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Processus parent
        if (r->background == false)
        {
            wait(&child_status);
            return child_status;
        }
    }

    return EXIT_SUCCESS;
}