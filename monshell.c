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
int internes_help();
int internes_quit();
int internes_dir(char **args);
int internes_clr();
int internes_echo(char **args);
int internes_environ(char **args);
int internes_pause();

// Liste des commandes internes
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

int nb_commandes_internes() {
  return sizeof(commandes_internes) / sizeof(char *);
}

// Implementation des commandes internes
int internes_cd(char **args)
{
  if (args[1] == NULL) { 
  printf("Argument manquant\n");
  char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);

  } else {
    if (chdir(args[1]) != 0) {
      perror("no such directory\n");
    }
  }
  return 1;
}

int internes_clr()
{
printf("\033[2J\033[1;1H");
    return 1;
}

int internes_dir(char **args)
{
struct dirent *pDirent;
        DIR *pDir;

if(args[1]){
 pDir = opendir(args[1]);
if(args[2]){
printf("un repertoire max \n");
return 1;
}
} else {
pDir = opendir(".");
}
        if (pDir == NULL) {
            printf ("Cannot open directory '%s'\n", args[1]);
            return 1;
        }

        // Process each entry.

        while ((pDirent = readdir(pDir)) != NULL) {
            printf ("%s ", pDirent->d_name);
        }
printf("\n");
  return 1;
}

int internes_environ(char **args)
{
extern char **environ;
  int i = 1;
  char *s = *environ;

  for (; s; i++) {
    printf("%s\n", s);
    s = *(environ+i);
  }
return 1;
}

int internes_echo(char **args)
{
char **ptr = args;
ptr++;
    while(*ptr)
    {
       printf("%s ", *ptr);
       ptr++;
    }
printf("\n");
return 1;
}


int internes_help()
{
  printf("Entreer une commande internes ou externes ou ctrl+d pour terminer\n");

  return 1;
}

int internes_pause()
{
char entree[60];
do{
printf("Appuyer SEULEMENT sur Entrer pour continuer ");
fgets(entree, 60, stdin);
//c = getchar();
}while(strncmp(entree, "\n", 1) != 0);
return 1;
}

int internes_quit()
{
  return 0;
}

int launch(char **args)
{
  pid_t pid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }

    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < nb_commandes_internes(); i++) {
    if (strcmp(args[0], commandes_internes[i]) == 0) {
      return (*commandes_internes_function[i])(args);
    }
  }

  return launch(args);
}

char *read_line(void)
{
  char *line = NULL;
  ssize_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1){
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  // We recieved an EOF
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}

#define LSH_TOK_DELIM " \t\r\n\a"

char **split_line(char *line)
{
  int bufsize = 64, position = 0;

  char **tokens = malloc(bufsize * sizeof(char*));

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  char * token = strtok(line, LSH_TOK_DELIM);
  while (token/*!=NULL*/) {
    tokens[position] = token;
    position++;
    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int check_input(char **args, char **input_file){
int i;
for(i = 0; args[i] != NULL; i++){
if(args[i][0] == '<'){
*input_file = args[i+1];
}
}
 return 0;
}

int main(int argc, char **argv, char * envp[])
{
  // Load config files, if any.
  //char cwd[100];
  char *ligneEntre;
  char **args;
  int status;
int i;
FILE *inputFile = NULL;
FILE *outputFile = NULL; 
for(i = 0; argv[i] != NULL; i++){
if(argv[i][0] == '<'){
inputFile = freopen(argv[i+1], "r", stdin);
//*input_file = args[i+1];
}
if (argv[i][0] == '>'){
outputFile = freopen(argv[i+1],"w",stdout);   
}
}


//FILE *fp = NULL;
 // if (argc == 2) fp=freopen(argv[1], "r", stdin);

//input = check_input(args, &input_file);
   do {
    char *buf=getcwd(NULL,0);
    printf("[%s]monshell> ",buf);
    ligneEntre = read_line();
    args = split_line(ligneEntre);
    status = execute(args);

    free(ligneEntre);
    free(args);
   }while(status);

if(inputFile){
 fclose(inputFile);
}
if(outputFile){
 fclose(outputFile);
}
  // Perform any shutdown/cleanup.

  return 0;
}

