/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */


#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd);

/*
 * Fonction renvoyant au client le nom
 * Paramètre: 
 *      le socket de dialogue avec le client
 *      LE tableau contenant le message
 */
int renvoi_nom(int client_socket_fd, char *data);

/*
 * Fonction renvoyant au client la couleur
 * Paramètre: 
 *      le socket de dialogue avec le client
 *      Le tableau contenant le message
 */
int recois_couleurs(int client_socket_fd, char *data);

#endif
