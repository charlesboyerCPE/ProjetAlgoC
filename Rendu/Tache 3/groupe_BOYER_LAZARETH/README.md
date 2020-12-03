# Projet: Algorithmes et C appliqués aux Systèmes Numériques

## Objectif

L'objectif du projet est de créer un environnement client-serveur pour l'analyse et la gestion desimages et de leurs métadonnées. Cependant, contrairement aux applications client-serveurtraditionnelles, nous n'enverrons pas les images au serveur pour analyse, mais nous effectuerons une analyse d'image côté client et enverrons des rapports de synthèse au serveur.

Pour cette troisième tâche, notre a objectif a été de créer un validateur. Ce dernier vérifie le JSON, notammant si la synthaxe est bien respecté.

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
  - validateur.c
  - validateur.h
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

Le validateur a mit de temps, notammant parce que nous voulions faire quelques choses d'assez générale.
J'entend par là que si nous voulons, prochainement, rajouter différents types de message, ils seront
pris en compte.
Difficulté: Moyen


## Informations importantes
Pour utiliser la fonction "couleur" il vous faut décommenter la fonction "envoie_couleurs" dans client.c et mettre "envoie_recois_message" en commentaire.
Le code à été documenté avec Doxygen.
