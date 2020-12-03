/*!
 * \file validateur.h
 * \brief Fichier contenant les prototypes des fonctions
 *      concernant le validateur de JSON
 * \author BOYER Charles, LAZARETH Baptiste
 * \copyright 2020 John Samuel GPL-3.0-or-later
 * \version 1.0
 * \date 2020
 */

#ifndef VALIDATEUR_H
#define VALIDATEUR_H

/*!
 * \fn int verifierCode(char *json)
 * \brief Fonction permettant de vérifier que le code du JSON est valide
 * \param [in] json : le JSON a traité
 * 
 * \return 0 si c'est conforme, -1 si il y a eu une erreur
 */
int verifierCode(char *json);

/*!
 * \fn int validateur (char *json);
 * \brief Fonction permettant de valider le JSON. La fonction recherche dans le JSON
 *      qu'il y a bien des guillemets sur les chaine de caractère. ELle vérifie qu'il n'y en
 *      ai pas sur les nombres.
 * \param [in] json : le JSON a traité
 * 
 * \return 0 si c'est conforme, -1 si il y a eu une erreur
 */
int validateur (char *json);

#endif