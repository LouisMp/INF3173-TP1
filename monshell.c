#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

int main(int argc, char *argv[], char **envp)
{ 
    environnement = envp;
    if(argc==2) {
        FILE *fichier = NULL;
        fichier = fopen(argv[1], "r");

        if (fichier == NULL){
            fprintf(stderr, "Usage: %s <batchfile> can't open file\n", argv[0]);
            exit(EXIT_FAILURE);
        }
        monshell_batchfile(fichier);

    } else if(argc==1) {
        monshell_cmdline();
    } else {
        fprintf(stderr, "Usage: %s <batchfile> or no arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}