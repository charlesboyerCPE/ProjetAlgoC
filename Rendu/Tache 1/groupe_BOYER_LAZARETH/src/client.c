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


void analyse(char *pathname, char *data) 
{
  //compte de couleurs
  couleur_compteur *cc = analyse_bmp_image(pathname);

  int count;
  strcpy(data, "couleurs: ");
  char temp_string[10] = "10,";
  if (cc->size < 10) 
  {
    sprintf(temp_string, "%d,", cc->size);
  }
  strcat(data, temp_string);
  
  //choisir 10 couleurs
  for (count = 1; count < 11 && cc->size - count >0; count++) 
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


int envoi_nom_de_client(char *data)
{
  strcpy(data, "nom: ");
  strcat(data, "neptune");

  return 0;
}


int envoie_operateur_numeros(int socketfd)
{
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));


  // Demandez à l'utilisateur d'entrer un message
  char message[1024];
  printf("calcule : ");
  fgets(message, 1024, stdin);
  strcpy(data, "calcul: ");
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

  printf("Resultat: %s\n", data);
 
  return 0;
}


int envoie_couleurs(int socketfd, char *pathname) 
{
  char data[1024];

  //Initialisation du buffer
  memset(data, 0, sizeof(data));

  analyse(pathname, data);

  //Envoi au serveur des resultats de l'analyse  
  int write_status = write(socketfd, data, sizeof(data));
  if (write_status < 0)  
  {
    perror("Erreur Ecriture");
    exit(EXIT_FAILURE);
  }

  //On réinitialise le buffer pour y mettre la réponse du serveur
  memset(data, 0, sizeof(data));

  //Attente de la réponse du serveur
  int read_status = read(socketfd, data, sizeof(data));
  if (read_status < 0) 
  {
    perror("Erreur Lecture");
    exit(EXIT_FAILURE);
  }
  
  printf("Message Recu: %s\n", data);
  return 0;
}


int envoie_balises(int socketfd)
{
  char data[1024];
  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  // Demandez à l'utilisateur d'entrer un message
  char message[100];
  printf("Balises : ");
  fgets(message, 1024, stdin);
  strcpy(data, "balises:");
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


int main(int argc, char **argv) 
{
  int socketfd;
  int bind_status;
  char message_statut[50];

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
  if ( connect_status < 0 ) 
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  /*printf("Quel type de message souhaitez vous envoyer : ");
  scanf("%s", message_statut);

  if(strcmp("nom", message_statut)){
    printf("%s \n", message_statut);
  }
  else if (strcmp("calcul", message_statut))
  {
    printf("%s \n", message_statut);
  }
  else if(strcmp("couleur", message_statut))
  {
    printf("%s \n", message_statut);
  }
  else
  {
    envoie_couleurs(socketfd, argv[1]);
  }*/
  
  envoie_balises(socketfd);

  //printf("%i", message_statut);
  //envoie_recois_message(socketfd);
  //envoie_couleurs(socketfd, argv[1]);


  close(socketfd);
}