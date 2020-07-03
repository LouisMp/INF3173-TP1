#include "tools.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

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


// le nombre de commandes internes
int nb_commandes_internes() { return sizeof(commandes_internes) / sizeof(char *); }

// Implementation des commandes internes

// commandes internes changer le répertoire par défaut actuel à <répertoire>.
int internes_cd(char **args)
{
    if (args[1] == NULL)
    {
        printf("Argument manquant. Signalez le répertoire courant.\n");
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("Dir: %s\n", cwd);
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("no such directory\n");
        }
    }
    return 1;
}

// commandes internes clr - effacer l'écran.
int internes_clr()
{
    printf("\033[2J\033[1;1H");
    return 1;
}

// commandes internes dir <répertoire> - lister le contenu du répertoire <répertoire>.
int internes_dir(char **args)
{
    struct dirent *pDirent;
    DIR *pDir;
    if (args[1])
    {
        pDir = opendir(args[1]);
        if (args[2])
        {
            printf("un repertoire max \n");
            return 1;
        }
    }
    else
    {
        pDir = opendir(".");
    }
    if (pDir == NULL)
    {
        printf("Cannot open directory '%s'\n", args[1]);
        return 1;
    }

    while ((pDirent = readdir(pDir)) != NULL)
    {
        printf("%s ", pDirent->d_name);
    }
    printf("\n");
    return 1;
}

// commandes internes environ - lister tous les contenus d'environnement
int internes_environ(char **args)
{
    extern char **environ;
    int i = 1;
    char *s = *environ;
    for (; s; i++)
    {
        printf("%s\n", s);
        s = *(environ + i);
    }
    return 1;
}

// commandes internes echo <comment> - afficher <comment> sur l'écran suivi d'une nouvelle ligne
int internes_echo(char **args)
{
    char **ptr = args;
    ptr++;
    while (*ptr)
    {
        printf("%s ", *ptr);
        ptr++;
    }
    printf("\n");
    return 1;
}

// commandes internes help - afficher le manuel d'utilisation à l'aide du filtre « more ».
int internes_help(char **args)
{
    if (!args[1])
    {
        printf("help <commandes internes> - pour obtenir le man de la commande internes\n");
        printf("help sans  arguments - affiche le manuel complet\n");
        printf("\ncd <répertoire> - changer le répertoire par défaut actuel à <répertoire>.\n");
        printf("\nclr - Effacer l'ecran\n");
        printf("\ndir <répertoire> - lister le contenu du répertoire <répertoire>.\n");
        printf("\nenviron - lister tous les contenus d'environnement.\n");
        printf("\necho <comment> - afficher <comment> sur l'écran suivi d'une nouvelle ligne\n"); 
        printf("\npause - interrompre le fonctionnement du shell jusqu'à ce que vous appuyiez sur «Entrer».\n"); 
        printf("\nquit - quitter le shell.\n");
return 1;
    }
    if (strncmp(args[1], "cd", 10) == 0)
    {
        printf("\ncd <répertoire> - changer le répertoire par défaut actuel à <répertoire>.\n");
        printf("Si l'argument <répertoire> n'est pas présent, signalez le répertoire courant.\n"); 
        printf("Si le répertoire n'existe pas, une erreur appropriée doit être signalée.\n"); 
        printf("Cette commande doit également modifier la variable d'environnement PWD\n\n");
    }
    else if (strncmp(args[1], "clr", 10) == 0)
    {
        printf("\nclr = Effacer l'ecran\n\n");
    }
    else if (strncmp(args[1], "dir", 10) == 0)
    {
        printf("\ndir <répertoire> - lister le contenu du répertoire <répertoire>.\n\n");
    }
    else if (strncmp(args[1], "environ", 10) == 0)
    {
        printf("\nenviron - lister tous les contenus d'environnement.\n\n");
    }
    else if (strncmp(args[1], "echo", 10) == 0)
    {
        printf("\necho <comment> - afficher <comment> sur l'écran suivi d'une nouvelle ligne\n\n");
    }
    else if (strncmp(args[1], "pause", 10) == 0)
    {
        printf("\npause - interrompre le fonctionnement du shell jusqu'à ce que vous appuyiez sur «Entrer».\n\n");
    }
    else if (strncmp(args[1], "quit", 10) == 0)
    {
        printf("\nquit - quitter le shell.\n\n");
    }
    else
    {
        printf("\nComandes internes inexistante\n\n");
    }
    return 1;
}

// Commandes internes pause - interrompre le fonctionnement du shell jusqu'à ce que vous appuyiez sur «Entrer».
int internes_pause()
{
    char entree[60];
    do
    {
        printf("Appuyer SEULEMENT sur Entrer pour continuer ");
        fgets(entree, 60, stdin);
        //c = getchar();
    } while (strncmp(entree, "\n", 1) != 0);
    return 1;
}

// Commandes internes quit - quitter le shell.
int internes_quit()
{
    return 0;
}

// Execute les commandes externes et si & parent nattend pas le retour de lenfant
int commandes_externes(char **args, int ampers)
{
    if (args != NULL)
    {
        pid_t pid;
        int resultat;
        pid = fork();
        if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                perror("Error in fork()");
            }
            exit(1);
        }
        else if (pid < 0)
        {
            // Error forking
            perror("Error in fork()");
        }
        else
        {
            // Parent process
            if (ampers)
            {
                do
                {
                    waitpid(pid, &resultat, 0);
                } while (!WIFEXITED(resultat) && !WIFSIGNALED(resultat));
            }
        }
    }
    return 1;
}

// Fonction qui execute la ligne de commandes
int execute(char **args, int ampers)
{
    int i;
    if (args[0] == NULL)
    {
        // Rien n'a ete entree
        return 1;
    }
    // verifie si commandes internes entree
    for (i = 0; i < nb_commandes_internes(); i++)
    {
        if (strcmp(args[0], commandes_internes[i]) == 0)
        {
            return (*commandes_internes_function[i])(args);
        }
    }
    // Fonction non internes donc externes
    return commandes_externes(args, ampers);
}

// Fonction qui li lentree de utilisateur
char *read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0;
    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            exit(0); // We recieved an EOF
        }
        else
        {
            perror("readline");
            exit(1);
        }
    }
    return line;
}

// Split lentree de lutilisateur en un array of pointers
#define LSH_TOK_DELIM " \t\n"
char **split_line(char *line)
{
    int bufsize = 64, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(1);
    }
    char *token = strtok(line, LSH_TOK_DELIM);
    while (token /*!=NULL*/)
    {
        tokens[position] = token;
        position++;
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// Verifie si il y a & dans la commandes entree
int check_ampersand(char **args)
{
    int i;
    for (i = 0; args[i] != NULL; i++){
    if (args[i][0] == '&')
    {
        return 1;
    }
    else
    {
        return 0;
    }
	}
    return 0;
}
