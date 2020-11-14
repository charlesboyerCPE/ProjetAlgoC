/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
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

void JSONParse(JSON json){
  printf("{\n");
  printf("\t\"code\":%s,\n", json.code);
  printf("\t\"valeurs\": [ ");
  /* for(int i = 0; i < sizeof(json.valeurs); i++){
    //Peut être tester si c'est un chiffre ou une string
    printf("%s,", json.valeurs[i]);
  } */
  printf("%s", json.valeurs);
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


  // Demandez à l'utilisateur d'entrer un message
  char message[100];
  printf("Votre message (max 1000 caracteres): ");
  fgets(message, 1024, stdin);
  strcpy(data, "message: ");
  strcat(data, message);
  
  int write_status = write(socketfd, data, strlen(data));
  if ( write_status < 0 ) 
  {
    perror("erreur ecriture");
    exit(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));


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

int envoie_nom_de_client(int socketfd)
{
  
}

void analyse(char *pathname, char *data) 
{
  //compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  int nbCouleurs;
  char temp_string[nbCouleurs];

  strcpy(data, "couleurs: ");

  //Demander à l'utilisateur le nombre de couleurs
  do
  {
    printf("\nVeuillez saisir le nombre de couleurs (<= 30): ");
    scanf("%d\n", &nbCouleurs);
    if (nbCouleurs > 30)
    {
      printf("Veuillez saisir un nombre inférieur ou égale à 30: ");
    } else if (nbCouleurs < 0)
    {
      printf("Veuillez saisir un nombre supérieur à 0: ");
    }

  } while (nbCouleurs > 30 || nbCouleurs < 0);
  
  strcpy(data, "couleurs: ");
  printf("Contenu data: %s\n", data);
  printf("Contenu temp_string: %s\n", temp_string);

  temp_string[nbCouleurs] = nbCouleurs;
  strcat(temp_string, ", ");
  printf("Contenu temp_string: %s\n", temp_string);

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
    strcat(data, temp_string);
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
  /* int socketfd;
  int bind_status;

  struct sockaddr_in server_addr, client_addr; */

  /*
   * Creation d'une socket
   */
  /* socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if ( socketfd < 0 ) 
  {
    perror("socket");
    exit(EXIT_FAILURE);
  } */

  //détails du serveur (adresse et port)
  /* memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;
 */
  //demande de connection au serveur
  /* int connect_status = connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if ( connect_status < 0 ) {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  } */
  //envoie_recois_message(socketfd);
  //envoie_couleurs(socketfd, argv[1]);

  //close(socketfd);

  JSON json;
  strcpy(json.code, "calcul");
  strcpy(json.valeurs, "oui, non, caca");
  JSONParse(json);


}
