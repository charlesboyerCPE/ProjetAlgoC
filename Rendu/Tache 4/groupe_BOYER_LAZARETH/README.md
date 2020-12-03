# Projet: Algorithmes et C appliqués aux Systèmes Numériques

## Objectif

L'objectif du projet est de créer un environnement client-serveur pour l'analyse et la gestion desimages et de leurs métadonnées. Cependant, contrairement aux applications client-serveurtraditionnelles, nous n'enverrons pas les images au serveur pour analyse, mais nous effectuerons une analyse d'image côté client et enverrons des rapports de synthèse au serveur.

Pour cette quatrième tâche, l'objectif a été de rajouter quatre autres opérations aux messages de type "calcul".

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
- math.h

## Références

- Groupe_BOURDIER_FIGUET pour quelques questions

## Difficultés

Le rajout d'opération a été extrêmement simple. Nous avons plus passer de temps à modifier le code
afin qu'il soit plus stable. Par exemple, l'utilisateur peux maintenant saisir des nombres flottants,
et saisir autant de nombre qu'il le désire.
Nous avons aussi optimiser le code de manière général.

Difficulté: Facile


## Informations importantes
Pour utiliser la fonction "couleur" il vous faut décommenter la fonction "envoie_couleurs" dans client.c et mettre "envoie_recois_message" en commentaire.
Le code à été documenté avec Doxygen.
