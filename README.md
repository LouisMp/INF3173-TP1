# INF3173-TP1
## Description

Implémentation en C d’un « shell » qui manipulera des simples commandes (cd, clear, ls, etc.) aux commandes plus complexes (le shell doit prends en charge la redirection stdin et/ou stdout, etc.) 

Le programme `monshell` doit être lancé en ligne de commande avec les options suivantes :
* ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) `<batchfile>`  Fichier contenant un ensemble de lignes de commande pour le shell à traiter.;
* ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) `<None>`Le shell prends les commandandes directement par entrée standard;
   
Ce programme a été conçu et écrit dans le cadre du cours INF3135 session été 2019 à l'Université du Quebec à Montréal.
## Auteur

   par *_MPANDZO-OTIANKOUYA_* _Louis Junior_ *(MPAL82010003)*.

   ## Fonctionnement

   Le programme (monshell) doit prendre en charge les commandes internes suivantes :
   * ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) cd `<répertoire>` - changer le répertoire par défaut actuel à `<répertoire>`. 
   * ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) 
   * ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) 
   
   Voici quelques commandes à taper qu'on peut effectuer pour lancer le programme:
   + `$ ./monshell`
   + `$ ./monshell .\crypto-tp1\crypto-mgs03.in`
   
   
   ### Détails sur les codes de retour
 + `0` : le programme s’est exécuté avec succès;
 + `1` : il y a eu `trop` d'argument, l'argument `<batchfile>` indique un fichier non existant ou il y'a eu une erreur au cours de l'execution;

   ## Contenu du projet

- Un fichier `monshell.c` contenant le code source du projet, ainsi que la fonction `main`;
- Les fichiers `tools.h` et `tools.c` contenant le code source de mes fonctions;
- Un fichier `README.md` ci-contre;
- Un fichier nommé `makefile` supportant l'appel `make`;
- Un fichier ``.gitignore``.;

   ## Références

   **https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split*
   
   **https://stackoverflow.com/questions/3501338/c-read-file-line-by-line*
   
   **https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c*

   ## Statut

   Le projet est en peaufinement.

   ## Réflexions
   
   
