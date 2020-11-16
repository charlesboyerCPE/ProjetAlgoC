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
 * \fn int envoie_recois_message(int socketfd)
 * \brief Fonction permettant l'envoi et la reception de message
 * \param [in] socketFd: l'identifiant de la socket de dialogue avec le serveur
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int envoie_recois_message(int socketfd);

/*!
 * \fn int envoi_nom_de_client(char *data)
 * \brief Fonction permettant l'envoi du nom du client au serveur
 * \param [in] data: le buffer contenant le message a envoyer
 * \return 0
 */
int envoi_nom_de_client(char *data);

/*!
 * \fn int envoie_operateur_numeros(int socketfd)
 * \brief Fonction permettant d'un opérateur et de deux nombres.
 * \param [in] socketfd: l'identifiant de la socket de dialogue avec le serveur
 * \return 0
 */
int envoie_operateur_numeros(int socketfd); //A REFAIRE

/*!
 * \fn int envoie_balises(int socketfd)
 * \brief Fonction permettant l'envoi de balises
 * \param [in] socketFd: l'identifiant de la socket de dialogue avec le serveur
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int envoie_balises(int socketfd);

/*!
 * \fn int envoie_couleurs(int socketfd, char *pathname)
 * \brief Fonction permettant l'envoi des couleurs présente dans une image
 * \param [in] socketFd: l'identifiant de la socket de dialogue avec le serveur
 * \param [in] pathname: Pointeur vers le chemin d'une image
 * 
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int envoie_couleurs(int socketfd, char *pathname);

#endif
