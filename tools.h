#ifndef MONSHELL_H_INCLUDED
#define MONSHELL_H_INCLUDED
#define DEFAUT_ARG_NUMBER 12
#include <stdio.h>
#include <stdlib.h>

void monshell_cmdline();
void monshell_batchfile(FILE *file);

char* read_line()
#endif // MONSHELL_H_INCLUDED