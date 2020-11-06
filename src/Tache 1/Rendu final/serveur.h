/*!
 * \file serveur.h
 * \brief Fichier contenant les prototypes des fonctions
 *      du programme serveur
 * \author John Samuel
 * \copyright 2020 John Samuel GPL-3.0-or-later
 * \version 1.0
 * \date 2020
 */

#ifndef __SERVER_H__
#define __SERVER_H__

/*!
 * \def PORT 8089
 */
#define PORT 8089

/*!
 * \fn recois_envoie_message(int socketfd)
 * \brief Fonction permettant l'envoi et la reception de message.
 *      La fonction accepte la connexion du client et lis les données envoyées
 *      par ce dernier. LA fonction envoi ensuite un message en retour.
 * \param [in] socketFd: l'identifiant de la socket de dialogue avec le client
 * 
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int recois_envoie_message(int socketfd);

#endif
