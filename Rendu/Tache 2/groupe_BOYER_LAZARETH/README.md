# Projet: Algorithmes et C appliqués aux Systèmes Numériques

## Objectif

L'objectif du projet est de créer un environnement client-serveur pour l'analyse et la gestion desimages et de leurs métadonnées. Cependant, contrairement aux applications client-serveurtraditionnelles, nous n'enverrons pas les images au serveur pour analyse, mais nous effectuerons une analyse d'image côté client et enverrons des rapports de synthèse au serveur.
Pour cette deuxième tâche, l'objectif est de travailler avec des messages de type JSON. De plus, nous ne travaillons plus avec 10 couleurs, mais avec un nombre inférieur ou égale à 30.

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

Nous n'étions pas partie sur la bonne base en ce qui concerne le JSON. En effet, nous avons commencer par juste envoyer des structures.
Après concertation avec un professeur, le but était d'envoyer une chaine de caractère. Nous avons donc dû tout adapter.
Difficulté : Elevé.
