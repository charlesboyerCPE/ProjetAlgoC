# Projet: Algorithmes et C appliqués aux Systèmes Numériques

## Objectif

L'objectif du projet est de créer un environnement client-serveur pour l'analyse et la gestion desimages et de leurs métadonnées. Cependant, contrairement aux applications client-serveurtraditionnelles, nous n'enverrons pas les images au serveur pour analyse, mais nous effectuerons une analyse d'image côté client et enverrons des rapports de synthèse au serveur.
Pour cette troisième tache l'objectif est de mettre en place un validateur qui va valider notre protocole.

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

Le traitement de chaînes de caractères en C est un peu compliqué. Nous avons mis en place des algorithmes de traitement de chaînes de caractère pour palier cette difficulté (strtok). Baptiste est un habitué des langages de hauts niveaux et le traitement des chaînes de caractères en C lui semble un peu barbare.
Difficulté : Elevé.

## Informations importantes
Pour utiliser la fonction "couleur" il vous faut décommenter la fonction "envoie_couleurs" dans client.c et mettre "envoie_recois_message" en commentaire.
Le code à été documenté avec Doxygen.
