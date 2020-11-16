/*!
 * \file serveur.c
 * \brief Fichier contenant le programme serveur, ainsi
 *      que la définition de ses fonctions
 * \author John Samuel
 * \copyright 2020 John Samuel sous license GPL-3.0-or-later
 * \version 1.0
 * \date 2020
 */

#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serveur.h"

void plot(char *data) 
{

  //Extraire le compteur et les couleurs RGB 
  FILE *p = popen("gnuplot -persist", "w");
  printf("Plot");
  int count = 0;
  int n;
  char *saveptr = NULL;
  char *str = data;
  fprintf(p, "set xrange [-15:15]\n");
  fprintf(p, "set yrange [-15:15]\n");
  fprintf(p, "set style fill transparent solid 0.9 noborder\n");
  fprintf(p, "set title 'Top 10 colors'\n");
  fprintf(p, "plot '-' with circles lc rgbcolor variable\n");
  while(1) 
  {
    char *token = strtok_r(str, ",", &saveptr);
    if (token == NULL) 
    {
      break;
    }
    str=NULL;
    if (count == 0) 
    {
      n = atoi(token);
    }
    else 
    {
      // Le numéro 36, parceque 360° (cercle) / 10 couleurs = 36
      fprintf(p, "0 0 10 %d %d 0x%s\n", (count-1)*36, count*36, token+1);
    }
    count++;
  }
  fprintf(p, "e\n");
  printf("Plot: FIN\n");
  pclose(p);
}


int renvoie_message(int client_socket_fd, char *data) 
{
  int data_size = write (client_socket_fd, (void *) data, strlen(data));
      
  if (data_size < 0) {
    perror("erreur ecriture");
    return(EXIT_FAILURE);
  }

  return 0;
}


int recois_envoie_message(int socketfd) 
{
  struct sockaddr_in client_addr;
  char data[1024];

  int client_addr_len = sizeof(client_addr);
 
  // nouvelle connection de client
  int client_socket_fd = accept(socketfd, (struct sockaddr *) &client_addr, &client_addr_len);
  if (client_socket_fd < 0 ) {
    perror("accept");
    return(EXIT_FAILURE);
  }

  // la réinitialisation de l'ensemble des données
  memset(data, 0, sizeof(data));

  //lecture de données envoyées par un client
  int data_size = read (client_socket_fd, (void *) data, sizeof(data));
      
  if (data_size < 0) {
    perror("erreur lecture");
    return(EXIT_FAILURE);
  }
  
  /*
   * extraire le code des données envoyées par le client. 
   * Les données envoyées par le client peuvent commencer par le mot "message :" ou un autre mot.
   */
  printf ("Message recu: %s\n", data);
  char code[10];
  sscanf(data, "%s", code);

  //En fonction du type de message
  if (strcmp(code, "nom:") == 0) 
  {
    renvoi_nom(client_socket_fd, data);
  }
  else if (strcmp(code, "couleurs:") == 0)
  {
    recois_couleurs(client_socket_fd, data);
  }
  else 
  {
    plot(data);
  }

  //fermer le socket 
  close(socketfd);
}


int renvoi_nom(int client_socket_fd, char *data)
{
  renvoie_message(client_socket_fd, data);

  return 0;
}


int recois_numeros_calcule(int client_socket_fd, char *data)
{
  int op1;
  int op2;
  char response[100] = "calcul : ";
  char buffer[100];

  if (2 == sscanf(data, "%*[^0-9]%d%*[^0-9]%d", &op1, &op2))
  {
    if (strchr(data, '+') != NULL){
      sprintf(buffer, "%i", (op1+op2));
    }
    else if (strchr(data, '-') != NULL){
      sprintf(buffer, "%i", (op1-op2));
    }
    else if (strchr(data, '*') != NULL){
      sprintf(buffer, "%i", (op1*op2));
    }
    else{
      sprintf(buffer, "Pas d'oparateur valable");
    }
    strcat(response, buffer);
  }

  renvoie_message(client_socket_fd, response);
  
  printf ("Message recu: %s\n", data);
  char code[10];
  sscanf(data, "%s", code);

  return 0;
}


int recois_couleurs(int client_socket_fd, char *data)
{
  FILE *fichierCouleur;

  //Ouverture du fichier
  fichierCouleur = fopen("saveCouleur.txt", "w");
  if (fichierCouleur == NULL)
  {
    fprintf(stderr, "Impossible d'ouvrir le fichier\n");
    return -1;
  }

  //Enregistrement du buffer dans le fichier
  if (fichierCouleur)
  {
    if (fwrite(data, sizeof(char), strlen(data), fichierCouleur) == 0)
    {
      fprintf(stderr, "Erreur dans l'écriture du fichier\n");
      return -1;
    }
    else
    {
      memset(data, 0, sizeof(data));
      data = "Couleurs enregistrees";
    }
  }
  else
  {
    printf("Impossible d'ecrire dans le fichier.\n");
    
    memset(data, 0, sizeof(data));
    data = "Erreur enregistrement couleurs";
  }
  
  //Envoi de la réponse au client
  printf("Contenu data: %s\n", data);
  renvoie_message(client_socket_fd, data);

  //Fermeture du fichier
  fclose(fichierCouleur);
}


int recois_balises(int client_socket_fd, char *data)
{
  int nb_balises;
  int index = 1;
  char response[100];
  char *str = strtok(data, "#");

  FILE *file = fopen("balises.txt", "w");

  if(file == NULL){
    printf("Impossible d'ouvrir le fichier\n");
    renvoie_message(client_socket_fd, "Un problème est survenu sur le serveur\n");
    return -1;
  }

  if (1 == sscanf(str, "%*[^0-9]%d", &nb_balises)){
    printf ("Message recu: %s\n", data);
    str = strtok(NULL, "#");
    while (str != NULL && index <= nb_balises)
    {
      char write[15] = "#";
      strcpy(response, str);
      printf("%s", str);
      response[strlen(response)-1] = '\n';
      strcat(write, response);
      fputs(write, file);

      str = strtok(NULL, "#");
      index++;
    }
    
    renvoie_message(client_socket_fd, "Balises enregistrées"); 
  }
  fclose(file);

  return 0;
}


int main() 
{

  int socketfd;
  int bind_status;
  int client_addr_len;

  struct sockaddr_in server_addr, client_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if ( socketfd < 0 ) 
  {
    perror("Unable to open a socket");
    return -1;
  }

  int option = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  //détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Relier l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
  if (bind_status < 0 ) 
  {
    perror("bind");
    return(EXIT_FAILURE);
  }
 
  // Écouter les messages envoyés par le client
  listen(socketfd, 10);

  //Lire et répondre au client
  //recois_envoie_message(socketfd);
  recois_balises(socketfd);

  return 0;
}
