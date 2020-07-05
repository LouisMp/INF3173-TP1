#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

int main(int argc, char **argv, char *envp[])
{
  char *ligneEntre;
  char **args;
  int retour = 1;
  int ampers, input, output, doutput;
  FILE *inputFile = NULL;
  FILE *outputFile = NULL;
  char *input_fileName;
  char *output_fileName;

  if (argc == 2)
  {
    inputFile = freopen(argv[1], "r", stdin);
    if (inputFile == NULL)
    {
      fprintf(stderr, "Impossible d'ouvrir le fichier\n");
      exit(-1);
    }
  }

  // Si pas de fichier redirection alors lire la ligne de commande jusqu'a l'utilisateur quit ou entre un fichier batch
  do
  { // Si redirection < alors pas besoin de print la demande dentree pour l'utilisateur
    if (isatty(0))
    {
      char *buf = getcwd(NULL, 0);
      printf("[%s]monshell> ", buf);
    }

    // Lire la ligne entree
    ligneEntre = read_line();
    // Decouper la ligne et mettre arguments dans un array
    args = parse_line(ligneEntre);
    // Verifier si & est present dans la ligne entree
    ampers = (check_ampersand(args) == 0);

    // Verifie si il y a une redirection < quand nous sommes dans le monshell
    input = check_input(args, &input_fileName);
    if (input)
      inputFile = freopen(input_fileName, "r", stdin);

    // Verifie si il y a une redirection > quand nous sommes dans monshell
    // Si redirection > alors ouvrir le fichier en monde w
    output = check_output(args, &output_fileName);
    if (output)
      outputFile = freopen(output_fileName, "w", stdout);

    // Verifie si il y a une redirectoin >> quand nous sommes dans monshell
    // Si redirection >> ouvrire le fichier en mode a
    doutput = check_doutput(args, &output_fileName);
    if (doutput)
      outputFile = freopen(output_fileName, "a", stdout);

    // le retour de la commande si status = 0 le programme termine, sinon loop continue
    retour = execute(args, ampers);

    // Si redirection vers fichier revenir stdout pour la prochaine commande entree
    if (output || doutput)
    {
      freopen("/dev/tty", "w", stdout);
    }

    free(ligneEntre);
    free(args);

  } while (retour);

  if (inputFile)
    fclose(inputFile);

  if (outputFile)
    fclose(outputFile);

  return 0;
}
