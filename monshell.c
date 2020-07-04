#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

int main(int argc, char **argv, char *envp[])
{
  //char cwd[100];
  char *ligneEntre;
  char **args;
  int status=1;
  int i, ampers, input, output, doutput;
  FILE *inputFile = NULL;
  FILE *outputFile = NULL;
  char *input_fileName;
  char *output_fileName;

  if (argc == 2)inputFile = freopen(argv[1], "r", stdin);


  // Au demarage(pas dans monshell) du monshell verifie si redirection
  for (i = 0; argv[i] != NULL; i++)
  {
	printf("le argv : %s\n", argv[i]);
    if (argv[i][0] == '<')
    {
      inputFile = freopen(argv[i + 1], "r", stdin);
    }
    if (argv[i][0] == '>')
    {
      if (argv[i][1] == '>')
      {
        outputFile = freopen(argv[i + 1], "a", stdout);
      }
      else
      {
        outputFile = freopen(argv[i + 1], "w", stdout);
      }
    }
  }

  do
  { // Si redirection < alors pas besoin de print la demande dentree pour l'utilisateur
    if (!inputFile)
    {
      char *buf = getcwd(NULL, 0);
      printf("[%s]monshell> ", buf);
    }
    ligneEntre = read_line();
    args = split_line(ligneEntre);
    ampers = (check_ampersand(args) == 0);

    // Verifie si il y a une redirection < quand nous sommes dans le monshell
    input = check_input(args, &input_fileName);
    if (input) 
    {
      inputFile = freopen(input_fileName, "r", stdin);
    }

    // verifie si il y a une redirection > quand nous sommes dans monshell
    output = check_output(args, &output_fileName);
    if (output)
    { // Ouvrir le fichier en mode w
      outputFile = freopen(output_fileName, "w", stdout);
    }

    // verifie si il y a une redirectoin >> quand nous sommes dans monshell
    doutput = check_doutput(args, &output_fileName);

    if (doutput)
    { // Ouvrir le fichier en mode a
      outputFile = freopen(output_fileName, "a", stdout);
    }

    status = execute(args, ampers);

 // Si redirection vers fichier revenir stdout pour la prochaine commande entree
 if (output || doutput)
  {
        freopen("/dev/tty", "w", stdout);
  }


    free(ligneEntre);
    free(args);

  } while (status);

  if (inputFile)
  {
    fclose(inputFile);
  }

  if (outputFile)
  {
    fclose(outputFile);
  }

  return 0;
}
