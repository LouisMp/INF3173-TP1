#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

int main(int argc, char **argv, char *envp[])
{
  // Load config files, if any.
  //char cwd[100];
  char *ligneEntre;
  char **args;
  int status;
  //int i;
  int ampers;

  FILE *inputFile = NULL;
  FILE *outputFile = NULL;

  if (argc == 2)
    inputFile = freopen(argv[1], "r", stdin);

  /*
for(i = 0; argv[i] != NULL; i++){
if(argv[i][0] == '<'){
inputFile = freopen(argv[i+1], "r", stdin);
}
if (argv[i][0] == '>'){
outputFile = freopen(argv[i+1],"w",stdout);   
}
}
*/

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
    status = execute(args, ampers);

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
  // Perform any shutdown/cleanup.

  return 0;
}
