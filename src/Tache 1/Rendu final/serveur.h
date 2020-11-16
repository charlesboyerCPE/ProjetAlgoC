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
 * \fn int recois_envoie_message(int socketfd)
 * \brief Fonction permettant l'envoi et la reception de message.
 *      La fonction accepte la connexion du client et lis les données envoyées
 *      par ce dernier. La fonction envoi ensuite un message en retour.
 * \param [in] socketFd: l'identifiant de la socket
 * 
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int recois_envoie_message(int socketfd);

/*!
 * \fn void plot(char *data)
 * \brief Procédure permettant d'ouvir une fenêtre GNUPlot affichant les couleurs
 * \param [in] data: Pointeur vers un tableau contenant les couleurs d'une image
 */
void plot(char *data);

/*!
 * \fn int renvoi_nom(int client_socket_fd, char *data)
 * \brief Fonction permettant de renvoyer le nom au client
 * \param [in] client_socket_fd: l'identifiant de la socket de dialogue avec le client
 * \param [in] data: Pointeur vers un tableau contenant le message à renvoyer
 * 
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int renvoi_nom(int client_socket_fd, char *data);

/*!
 * \fn int recois_numeros_calcule(int socketfd)
 * \brief Fonction permettant de recevoir un opérateur et deux nombre.
 *      La fonction calcul l'opération et envoi le résultat au client
 * \param [in] client_socket_fd: l'identifiant de la socket de dialogue avec le client
 * \param [in] data: le buffer contenant le message recu
 * 
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int recois_numeros_calcule(int client_socket_fd, char *data); //A REFAIRE

/*!
 * \fn int renvoie_message(int client_socket_fd, char *data)
 * \brief Fonction permettant de renvoyer un message au client
 * \param [in] client_socket_fd: l'identifiant de la socket de dialogue avec le client
 * \param [in] data: POinteur vers un tableau contenant le message à envoyer
 * 
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int renvoie_message(int client_socket_fd, char *data);

/*!
 * \fn int renvoie_message(int client_socket_fd, char *data)
 * \brief Fonction permettant de recevoir les couleurs d'une image.
 *      La fonction sauvegarde le message dans un fichier txt.
 * \param [in] client_socket_fd: l'identifiant de la socket de dialogue avec le client
 * \param [in] data: Buffer contenant le message à envoyer
 * 
 * \return 0 si tout a bien fonctionner, -1 si il y a eu une erreur
 */
int recois_couleurs(int client_socket_fd, char *data);

/*!
 * \fn int recois_balises(int socketfd)
 * \brief Fonction permettant de recevoir des balise en provenance du client.
 *      La fonction enregistre les balises dans un fichier et envoi un message au client
 *      pour lui indiquer que les balises ont étaient enregistrés.
 * \param [in] client_socket_fd: l'identifiant de la socket de dialogue avec le client
 * \param [in] data: le buffer contenant le message recu
 * 
 * \return 0
 */
int recois_balises(int client_socket_fd, char *data);

#endif
