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
int internes_quit();
int internes_dir(char **args);
int internes_clr();
int internes_echo(char **args);
int internes_environ(char **args);
int internes_pause();
/*
char *commandes_internes[] = {
  "cd",
  "clr",
  "dir",
  "environ",
  "echo",
  "help",
  "pause",
  "quit"
};

// pointeur vers la fonction de la commande internes
int (*commandes_internes_function[]) (char **) = {
  &internes_cd,
  &internes_clr,
  &internes_dir,
  &internes_environ,
  &internes_echo,
  &internes_help,
  &internes_pause,
  &internes_quit
};
*/
int nb_commandes_internes();

int internes_cd(char **args);

int launch(char **args, int ampers);

int execute(char **args, int ampers);

char *read_line(void);

char **split_line(char *line);

int check_ampersand(char **args);


#endif // TOOLS_H_INCLUDED
