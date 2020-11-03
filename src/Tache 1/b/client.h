/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

/* 
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */
int envoie_recois_message(int socketfd);

/*
 * Fonction d'envoi du nom du client
 * Prend en paramètre: le buffer a envoyer, et le buffer contenant le message
 */ 
int envoi_nom_de_client(char data[1024], char message[1024]);
#endif
