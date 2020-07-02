# INF3173-TP1
## Description

Implémentation en C d’un « shell » qui manipulera des simples commandes (cd, clear, ls, etc.) aux commandes plus complexes (le shell doit prendre en charge la redirection stdin et/ou stdout, etc.) 

Le programme `monshell` doit être lancé en ligne de commande avec les options suivantes :
* ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) <batchfile> Une clé simple : un nombre positif ou négatif;
* ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) -c Le code permanent de l'utilisateur qui doit être de taille 12:
* ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) -d | -e : décoder OU encoder;
* ![#6600A1](https://placehold.it/15/6600A1/000000?text=+) -b & -l : bruteforce avec dossiers contenant les dictionnaires de langue dans `-l`;
Ce programme a été conçu et écrit dans le cadre du cours INF3135 session été 2019 à l'Université du Quebec à Montréal.
## Auteur

   par *_MPANDZO-OTIANKOUYA_* _Louis Junior_ *(MPAL82010003)*.

   ## Fonctionnement

   Comme expliqué plus haut il y a des paramètres obligatoire mais il y'en a d'autres qui peuvent augmenter le nombres de combinaisons :
   * ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) -i `<fichier source en entrée avant le traitement>` si argument absent, l'utilisateur est solicité pour taper les caractères à crypter.
   * ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) -o `<fichier traité en sortie après l'exécution voulue>` si argument absent, Résultat de la requête enregistré dans le fichier <sortie_standard.out>.
   * ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) -a `<chemin vers le fichier alphabet>` si argument absent, on lira le fichier `<alphabet.txt>` situé dans le repertoire du projet.
   
   Voici quelques commandes à taper qu'on peut effectuer :
   + `$ ./tp2 -c MPAL82010003 -d -k 3 -o C:\Users\louis\OneDrive\Documents\Cours\Session 4 Été 2019\INF3135\crypto.sortie`
   + `$ ./tp2 -c MPAL82010003 -b -l \modeles\ -a .\ok <.\crypto-tp1\crypto-mgs03.in`
   
   
   ### Détails sur les codes de retour
 + `0` : le programme s’est exécuté avec succès;
 + `1` : il n'y a `aucun` d'argument ou l'argument `-c` n'est pas présent;
 + `2` : l'argument -c est présent, mais le code n'est pas 12 de long;
 + `3` : un argument non voulu est présent. Voici un exemple : `-t BLA`;
 + `4` : l'argument -d ou -e n'est pas présent;
 + `5` : une erreur (lecture, ouverture, présence ...) avec le fichier en entrée;
 + `6` : une erreur (création, ...) avec le fichier en sortie; `Attention` Si le fichier existe il faut l'écraser;
 + `7` : l'argument -k n'est pas présent, ou la valeur passée n'est pas conforme;
 + `8` : l'argument -a est présent, mais impossible d'ouvrir le fichier alphabet.txt;
 + `9` : les options obligatoires ne sont pas toutes présentes ou mal utilisées;
 + `11` : erreur d'ouverture dossier envoyé par l'option `-l`;
 + `12` : le dossier envoyé par l'option `-l` est vide;
 + `13` : `-c -k -l -a -i -o` sont présents mais n'ont pas reçu la seconde chaine qu'ils ont besoin pour fonctionner;

   ## Contenu du projet

- Un fichier `cp.txt` contenant mon code permanent en majuscule et complet;
- Un fichier `tp2.c` contenant le code source du projet, ainsi que la fonction `main`;
- Les fichiers `outils.h` et `outils.c` contenant le code source de vos fonctions;
- Les fichiers `structure.h` et `structure.c` contenant le code source de la structure des données utilisées;
- Un fichier `README.md` ci-contre;
- Un fichier nommé `Makefile` supportant les appels `make`, `make clean`, `make data`, `make test` et `make resultat`;
- Un fichier ``.gitignore``.;
- Un script  bash `evaluer-tp2.sh` qui automatise les test pour ce nouveau projet;

   ## Références

   **https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split*
   
   **https://github.com/json-c/json-c/blob/master/arraylist.c*
   
   **http://sdz.tdct.org/sdz/arcourir-les-dossiers-avec-dirent-h.html*

   ## Statut

   Le projet a été amélioré et réussi 25 test sur 26.
   OPTION BRUTEFORCE NON IMPLEMENTE

   ## Réflexions
   
   On utilise 3 structures pour l’option `bruteforce` :
  ~_ `structure Mot` qui n’est qu’une chaîne de caractère de taille maximale 136 (pour contenir même le mot le plus grand du monde).~
   
   ~_ `structure Dictionnaire` qui est un tableau dynamique de mots avec plusieurs caractéristiques comme~
     ~sa taille maximale et le nombre de Mots entrés~
     
   ~_ `structure Bibliotheque` qui est un tableau dynamique de dictionnaire avec les mêmes caractéristiques.~
   
   _ Finalement j'utiliserais une structure plus simple `vector`
  
   Il y est aussi implémenté un type enumeratif `LANG` pour identifier les langues des dictionnaires dans une `Bibliotheque`. 
