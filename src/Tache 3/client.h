/*!
 * \file client.h
 * \brief Fichier contenant les prototypes des fonctions
 *      du programme client
 * \author John Samuel
 * \copyright 2020 John Samuel GPL-3.0-or-later
 * \version 1.0
 * \date 2020
 */
#ifndef __CLIENT_H__
#define __CLIENT_H__

/*!
 * \def PORT 8089
 */
#define PORT 8089

/*!
 * \def NB_STRINGS 30
 */
#define NB_STRINGS 30

/*!
 * \def STRING_LENGTH 256
 */
#define STRING_LENGTH 256

typedef struct JSON JSON;
struct JSON
{
    char code[50];
    char valeurs[NB_STRINGS][STRING_LENGTH];
};

/*!
 * \fn int envoie_recois_message(int socketfd)
 * \brief Fonction permettant l'envoi et la reception de message
 * \param [in] socketFd: l'identifiant de la socket de dialogue avec le serveur
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int envoie_recois_message(int socketfd);

/*!
 * \fn struct JSON JSONparse(char str[])
 * \brief Fonction permettant de parser le JSON
 * \param [in] str: le buffer contenant le json sous forme de chaine de caractère
 * 
 * \return Le JSON
 */
void JSONParse(JSON json);



#endif
