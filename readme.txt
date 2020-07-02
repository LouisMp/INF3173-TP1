# INF3173-TP1

## Description

Implémentation en C d’un « shell » qui manipulera des simples commandes (cd, clear, ls, etc.) aux commandes plus complexes (le shell doit prends en 
charge la redirection stdin et/ou stdout, etc.) Le programme `monshell` doit être lancé en ligne de commande avec les options suivantes :
   - Fichier contenant un ensemble de lignes de commande pour le shell à traiter. - Le shell prends les commandandes directement par entrée standard.
   
Ce programme a été conçu et écrit dans le cadre du cours INF3173 session été 2020 à l'Université du Quebec à Montréal.

## Auteur
   par 
	- MPANDZO-OTIANKOUYA Louis Junior (MPAL82010003)
	- On William (ONXW12069703)

## Fonctionnement
   
   Le programme doit être compilé : 
	make 

   Le programme (monshell) doit prendre en charge les commandes internes suivantes : 
	
	cd `<répertoire>` - changer le répertoire par défaut actuel à `<répertoire>`.
	Si l'argument <répertoire> n'est pas présent, signalez le répertoire courant. 

	clr - effacer l'écran 

	dir <répertoire> - lister le contenu du répertoire <répertoire>. 

	environ - lister tous les contenus d'environnement. 
	
	echo <comment> - afficher <comment> sur l'écran suivi d'une nouvelle ligne. 

	help - afficher le manuel d'utilisation à l'aide du filtre « more ». 
      
	pause - interrompre le fonctionnement du shell jusqu'à ce que vous appuyiez sur «Entrer». quit - quitter le shell.
   
   
   On gère égalements les redirections suivantes : - `<` - `>` - `>>` - `&`
   
   Voici quelques commandes à taper qu'on peut effectuer pour lancer le programme: 
	./monshell 
	./monshell .\crypto-tp1\data.txt
	./monshell data.txt
	./monshell < data.txt > out.txt   
   
### Détails sur les codes de retour

	+ `0` : le programme s’est exécuté avec succès; 
	+ `1` : il y a eu `trop` d'argument, l'argument `<batchfile>` indique un fichier non existant ou il y'a eu une erreur au cours de l'execution;
   

## Contenu du projet

	- Un fichier `monshell.c` contenant le code source du projet, ainsi que la fonction `main`; 
	- Les fichiers `tools.h` et `tools.c` contenant le code source de mes fonctions; 
	- Un fichier `readme.txt` ci-contre; 
	- Un fichier nommé `makefile` supportant l'appel `make`;
   
## Références

   **https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split*
   
   **https://stackoverflow.com/questions/3501338/c-read-file-line-by-line*
   
   **https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c*
   
## Statut

   Le projet est en peaufinement.

## Réflexions

   On a du mal a trouvé une façon efficace de mettre en `pause` le programme
   
