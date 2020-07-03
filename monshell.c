#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

int main(int argc, char **argv, char *envp[])
{
  //char cwd[100];
  char *ligneEntre;
  char **args;
  int status;
  int i;
  int ampers;
  int input;
  int output;
  int doutput;
  FILE *inputFile = NULL;
  FILE *outputFile = NULL;
  char *input_fileName;
  char *output_fileName;
  if (argc == 2)
    inputFile = freopen(argv[1], "r", stdin);

  for (i = 0; argv[i] != NULL; i++)
  {
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
    //if (argv[i][0] == ">>"){
    //outputFile = freopen(argv[i+1],"a",stdout);
    //}
  }

  do
  {
    if (argc == 1)
    {
      char *buf = getcwd(NULL, 0);
      printf("[%s]monshell> ", buf);
    }
    ligneEntre = read_line();
    args = split_line(ligneEntre);
    ampers = (check_ampersand(args) == 0);

    // appel de redirection < dans le monshell
    input = check_input(args, &input_fileName);
    if (input)
    {
      inputFile = freopen(input_fileName, "r", stdin);
      ligneEntre = read_line();
      args = split_line(ligneEntre);
      ampers = (check_ampersand(args) == 0);
      status = execute(args, ampers);
      return 0;
    }

    // appel redirection > dans monshell
    output = check_output(args, &output_fileName);
    if (output)
    {
      printf("le file name output w: %s\n", output_fileName);
      outputFile = freopen(output_fileName, "w", stdout);
      // ligneEntre = read_line();
      //args=split_line(ligneEntre);
      //ampers = (check_ampersand(args) == 0);
      //  status= execute(args,ampers);
      // return 0;
      status = execute(args, ampers);
      //	printf("le status %i\n",status);
      //return status;
      return 0;
    }
    printf("ici ta\n");
    doutput = check_doutput(args, &output_fileName);

    if (doutput)
    {
      printf("ok le douput %i\n", doutput);
      printf("le file name doutputa: %s\n", output_fileName);
      //outputFile =
      freopen(output_fileName, "a", stdout);
      // ligneEntre = read_line();
      //args=split_line(ligneEntre);
      //ampers = (check_ampersand(args) == 0);
      //  status= execute(args,ampers);
      // return 0;
      status = execute(args, ampers);
      return 0;
    }

    //if(!doutput){
    //	printf("why\n");
    status = execute(args, ampers);
    //	}
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
