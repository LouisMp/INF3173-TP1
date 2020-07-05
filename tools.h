#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

extern char getline();

// Declarations des fonctions internes
int internes_cd(char **args);
int internes_help(char **args);
int internes_quit(char **args);
int internes_dir(char **args);
int internes_clr(char **args);
int internes_echo(char **args);
int internes_environ(char **args);
int internes_pause(char **args);

int nb_commandes_internes();

int internes_cd(char **args);

int commandes_externes(char **args, int ampers);

int execute(char **args, int ampers);

char *read_line(void);

char **parse_line(char *line);

int check_ampersand(char **args);

int check_input(char **args, char **input_file);

int check_output(char **args, char **output_file);

int check_doutput(char **args, char **output_file);

#endif // TOOLS_H_INCLUDED
