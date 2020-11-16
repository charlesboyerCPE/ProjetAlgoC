/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */


#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

#define NB_STRINGS 30
#define STRING_LENGTH 256
/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
int recois_envoie_message(int socketfd);

typedef struct JSON JSON;
struct JSON
{
    char code[50];
    char valeurs[NB_STRINGS][STRING_LENGTH];
};

#endif
