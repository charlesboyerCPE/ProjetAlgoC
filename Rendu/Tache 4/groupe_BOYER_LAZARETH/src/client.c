/*!
 * \file client.c
 * \brief Fichier contenant le programme client, ainsi
 *      que la définition de ses fonctions
 * \author John Samuel
 * \copyright 2020 John Samuel sous license GPL-3.0-or-later
 * \version 1.0
 * \date 2020
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"
#include "bmp.h"
#include "validateur.h"

void JSONParse(JSON json)
{
  printf("{\n");
  printf("\t\"code\":\"%s\",\n", json.code);
  printf("\t\"valeurs\": [ ");
  for(int i = 0; i < NB_STRINGS; i++){
    if (json.valeurs[i] && json.valeurs[i][0] != '\0')
    {
      printf("\"%s\"", json.valeurs[i]);
      if (i+1 < NB_STRINGS && json.valeurs[i+1][0] != '\0')
        printf(",");
    }
  } 
  printf("]\n");
  printf("}\n");
}

/* 
 * Fonction d'envoi et de réception de messages
 * Il faut un argument : l'identifiant de la socket
 */
int envoie_recois_message(int socketfd) 
{

  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  /*
  * Tests avec JSON en dur
  */
  char messageType[100] = "";
  char message[100] = "";
  char json[1024];

  //On demande à l'utilisateur quel type de message et ses valeurs
  printf("Votre type de message ? (calcul, message, couleurs, balises) : ");
  fgets(messageType, 1024, stdin);
  strtok(messageType, "\n");
  printf("Votre message : ");
  fgets(message, 1024, stdin);
  strtok(message, "\n");
  printf("Message : %s\n", message);
  
  //Préparation du JSON
  char *strToken;
  char tmpString[256] = "";
  char finalString[512] = "";
  strToken = strtok(message, ",");
  while (strToken != NULL)
  {
    //Si l'entrée n'est pas un nombre
    if (atoi(strToken) == 0)
    {
      //Si la chaine de caractères a déjà des guillemets on n'en rajoute pas
      if(strToken[0] == '\"' && strToken[strlen(strToken)-1] == '\"')
      {
        sprintf(tmpString, "%s,", strToken);
      }
      //en revanche si il n'y en a pas on en rajoute
      else
      {
        sprintf(tmpString, "\"%s\",", strToken);
      }
    }
    //Si c'est un nombre on ne touche à rien
    else
    {
      sprintf(tmpString, "%s,", strToken);
    }    
    
    strcat(finalString, tmpString);
    strToken = strtok(NULL, ",");
  }
  finalString[strlen(finalString) - 1] = '\0';
  

  sprintf(json, "{\"code\":\"%s\",\"valeurs\":[%s]}", messageType, finalString);

  //On demande au validateur
  char code_dump[1024];
  char valeurs_dump[1024];

  strcpy(code_dump, json);
  strcpy(valeurs_dump, json);

  if(validateur(code_dump) == 0 && verifierCode(valeurs_dump) == 0)
  { 
    printf("Message envoyé : %s\n", json);
    int write_status = write(socketfd, json, strlen(json));
    if ( write_status < 0 ) 
    {
      perror("erreur ecriture");
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    printf("non\n");
    return -1;
  }

  // la réinitialisation de l'ensemble des données
  memset(json, 0, sizeof(json));


  // lire les données de la socket
  int read_status = read(socketfd, data, sizeof(data));
  if ( read_status < 0 ) 
  {
    perror("erreur lecture");
    return -1;
  }

  printf("Message recu: %s\n", data);
 
  return 0;
}

void analyse(char *pathname, char *data) 
{
  //compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  int nbCouleurs;

  //Demander à l'utilisateur le nombre de couleurs
  do
  {
    printf("\nVeuillez saisir le nombre de couleurs (<= 30): ");
    scanf("%d", &nbCouleurs);

    if (nbCouleurs > 30)
    {
      printf("\nVeuillez saisir un nombre inférieur ou égale a 30");
    } else if (nbCouleurs < 0)
    {
      printf("\nVeuillez saisir un nombre supérieur a 0");
    }
  } while (nbCouleurs > 30 || nbCouleurs < 0);
  
  //Ajouter le nombre de couleur désiré
  char temp_string[nbCouleurs];
  sprintf(temp_string, "%d, ", nbCouleurs);
  
  if (cc->size < nbCouleurs) 
  {
    sprintf(temp_string, "%d,", cc->size);
  }
  strcat(data, temp_string);
  
  //choisir nbCouleurs couleurs
  for (count = 1; count < nbCouleurs + 1 && cc->size - count >0; count++) 
  {
    if(cc->compte_bit ==  BITS32) 
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc24[cc->size-count].c.rouge,cc->cc.cc32[cc->size-count].c.vert,cc->cc.cc32[cc->size-count].c.bleu);
    }
    if(cc->compte_bit ==  BITS24) 
    {
      sprintf(temp_string, "#%02x%02x%02x,", cc->cc.cc32[cc->size-count].c.rouge,cc->cc.cc32[cc->size-count].c.vert,cc->cc.cc32[cc->size-count].c.bleu);
    }
    strcat(data, temp_string);;
  }

  //enlever le dernier virgule
  data[strlen(data)-1] = '\0';
}

int envoie_couleurs(int socketfd, char *pathname) 
{
  char data[1024];
  memset(data, 0, sizeof(data));
  analyse(pathname, data);
  
  int write_status = write(socketfd, data, strlen(data));
  if ( write_status < 0 ) 
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  return 0;
}

int main(int argc, char **argv) 
{
  int socketfd;
  int bind_status;

  struct sockaddr_in server_addr, client_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if ( socketfd < 0 ) 
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  //détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  //demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if ( connect_status < 0 ) {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }
  //envoie_couleurs(socketfd, argv[1]);

  envoie_recois_message(socketfd);

  close(socketfd);


}
