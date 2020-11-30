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
 * \fn void JSONToString(JSON json)
 * \brief Fonction permettant de mettre un JSON sous forme de chaine de caractère
 * \param [in] json: Le JSON
 */
void JSONToString(JSON json);

/*!
 * \fn struct JSON JSONparse(char str[])
 * \brief Fonction permettant de parser le JSON
 * \param [in] str: le buffer contenant le json sous forme de chaine de caractère
 * 
 * \return Le JSON
 */
struct JSON JSONparse(char str[]);

/*!
 * \fn int traite_calcul(JSON json)
 * \brief Fonction permettant de traiter le message de type calcule
 * \param [in] json : Le JSON avec le message
 * 
 * \return 0 si tout s'est bien passer
 */
int traite_calcul(JSON json);

/*!
 * \fn int traite_couleurs(JSON json)
 * \brief Fonction permettant de traiter le message de type couleurs
 * \param [in] json : Le JSON avec le message
 * 
 * \return 0 si tout s'est bien passer
 */
int traite_couleurs(JSON json);

/*!
 * \fn int traite_balises(JSON json)
 * \brief Fonction permettant de traiter le message de type balise
 * \param [in] json : Le JSON avec le message
 * 
 * \return 0 si tout s'est bien passer
 */
int traite_balises(JSON json);

#endif
