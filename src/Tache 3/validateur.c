/*!
 * \file validateur.c
 * \brief Fichier contenant les définitions des fonctions
 *      permettant de valider un message JSON
 * \author Boyer Charles, Lazareth Baptiste
 * \copyright 2020 John Samuel sous license GPL-3.0-or-later
 * \version 1.0
 * \date 2020
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int verifierCode (char *json)
{
    char delim[] = "\":,{[]}";

    char *code = strtok(json, delim);

    code = strtok(NULL, delim);
    printf("code : %s\n", code);
    if (strstr(code, "calcul"))
    {
        return 0;
    }
    else if (strstr(code, "message"))
    {
        return 0;
    }
    else if (strstr(code, "nom"))
    {
        return 0;
    }
    else if (strstr(code, "couleurs"))
    {
        return 0;
    }
    else if (strstr(code, "balises"))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int validateur (char *json)
{
    char *cpyJSON;
    char *delimiter = "[]{},:";
    char *strToken;
    printf("JSON: %s\n", json);
    
    //On parcours la chaine de caractère en supprimant les éléments inutiles
    strToken = strtok(json, delimiter);
    while (strToken != NULL)
    {       
        //On teste pour savoir si c'est un nombre
        if (atoi(strToken) == 0)
        {
            //Si ce n'est pas un nombre, on regarde si il y a des guillemets
            if(strToken[0] != '\"' && strToken[strlen(strToken)-1] != '\"')
            {
                printf("JSON Non valide\n");
                return -1;
            }  
        }
        else
        {
            //SI c'est un nombre, on regarde qu'il n'y ai pas de guillemets
            if(strToken[0] == '\"' && strToken[strlen(strToken)-1] == '\"')
            {
                printf("JSON Non valide\n");
                return -1;
            } 
        }
        
        //On prend le token suivant
        strToken = strtok(NULL, delimiter);
    }
    
    return 0;
}
