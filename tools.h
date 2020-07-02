#ifndef MONSHELL_H_INCLUDED
#define MONSHELL_H_INCLUDED
#define DEFAUT_ARG_NUMBER 12
#define INTERNAL_FUNCTION_NUMBER 8
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Redirections Redirections;
struct Redirections
{
    bool in;
    char* in_filename;
    bool out;
    char* out_filename;
    bool append;
    char* a_filename;
    bool background;
};

int cd(char** args, Redirections* r);
int clr(char** args, Redirections* r);
int dir(char** args, Redirections* r);
int env(char** args, Redirections* r);
int echo(char** args, Redirections* r);
int hlp(char** args, Redirections* r);
int pause(char** args, Redirections* r);
int quit(char** args, Redirections* r);

char* internal_command_list [INTERNAL_FUNCTION_NUMBER] = {"cd","clr","dir","environ","echo","help","pause","quit"};
int (*internal_functions[INTERNAL_FUNCTION_NUMBER]) (char** args, Redirections* r)= {&cd, &clr, &dir, &env, &echo, &hlp, &pause, &quit};
void monshell_cmdline();
void monshell_batchfile(FILE *file);

char* read_line();
char** parse_args(char* args);

int run(char** args, Redirections* r);
int run_external(char** args);

#endif // MONSHELL_H_INCLUDED