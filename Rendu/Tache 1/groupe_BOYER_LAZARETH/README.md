# Projet: Algorithmes et C appliqués aux Systèmes Numériques

## Objectif

L'objectif du projet est de créer un environnement client-serveur pour l'analyse et la gestion desimages et de leurs métadonnées. Cependant, contrairement aux applications client-serveurtraditionnelles, nous n'enverrons pas les images au serveur pour analyse, mais nous effectuerons une analyse d'image côté client et enverrons des rapports de synthèse au serveur.
L'objectif de cette première tâche est de se familiariser avec le code et de manipuler les différents types de messages qui seront transmits.

## Fichiers

- src/
  - bmp.c
  - bmp.h
  - client.c
  - client.h
  - serveur.c
  - serveur.h
  - couleur.c
  - couleur.h
- CONTRIBUTORS.md
- INSTALL.md
- MakeFile
- README.md

## Bibliothèques

- sys/types.h
- sys/socket.h
- sys/epoll.h
- netinet/in.h
- stdio.h
- stdlib.h
- string.h
- unistd.h

## Références

- Groupe_BOURDIER_FIGUET pour quelques questions
- StackOverflow

## Difficultés

Charles BOYER:
Mon travail dans cette tâche a été d'effectué les questions b et d, ainsi que l'ajout de commentaires Doxygen.
Travaillant actuellement sur un projet personnel comportant des communications client-serveur en C++, le compréhension du code a été assez rapide.
Les réels soucis que j'ai rencontré ont été au niveau de la compréhension des questions.

Baptiste LAZARETH:
Ma tâche a été de réaliser les question a, c, e. Pas très à l'aise avec le C.
J'ai trouvé la tâche 1 de difficulté moyenne.
