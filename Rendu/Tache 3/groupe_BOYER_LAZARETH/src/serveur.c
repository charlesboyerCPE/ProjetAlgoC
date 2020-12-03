/*
 * SPDX-FileCopyrightText: 2020 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
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
#include "validateur.h"

void JSONToString(JSON json)
{
  printf("{\n");
  printf("\t\"code\":\"%s\",\n", json.code);
  printf("\t\"valeurs\": [ ");
  for(int i = 0; i < NB_STRINGS; i++){
    if (json.valeurs[i] && json.valeurs[i][0] != '\0')
    {
      if (atoi(json.valeurs[i]) != 0)
      {
        printf("%s", json.valeurs[i]);
      }
      else
      {
        printf("\"%s\"", json.valeurs[i]);
      }
      if (i+1 < NB_STRINGS && json.valeurs[i+1][0] != '\0')
        printf(",");
    }
  } 
  printf("]\n");
  printf("}\n");
}

struct JSON JSONparse(char str[])
{
  //Initialise une structure JSON
  struct JSON json = { "", { "" }};
  char delim[] = "\":,{[]}";

  if(str[0] == '{' && str[strlen(str) - 1] == '}') {
    char valeurs[NB_STRINGS][STRING_LENGTH];
    int i = 0;

    char *ptrtoken = strtok(str, delim);
    ptrtoken = strtok(NULL, delim);
    char *code = strdup(ptrtoken);
    strcpy(json.code, code); // copie la valeur prélevé dans la string dans le champ code
    ptrtoken = strtok(NULL, delim);
    ptrtoken = strtok(NULL, delim);

    while(ptrtoken != NULL) {
      char *temp = strdup(ptrtoken);
      strcpy(json.valeurs[i], temp); // copie la valeur dans une case du tableau du champs valeurs
      i = i + 1;
      ptrtoken = strtok(NULL, delim);
    }
  }
  return json;
}

int traite_calcul(JSON json){
  int op1 = atoi(json.valeurs[1]);
  int op2 = atoi(json.valeurs[2]);
  if (strstr(json.valeurs[0], "+") != NULL)
  {
    return op1+op2;
  }
  else if (strstr(json.valeurs[0], "-") != NULL)
  {
    return op1-op2;
  }
  else if(strstr(json.valeurs[0], "*") != NULL)
  {
    return op1*op2;
  }
  else
  {
    return 0;
  }
  
}

//TODO : factoriser le traitement des balises/couleur en une fonction
int traite_couleurs(JSON json){
  FILE *fichier;
  fichier = fopen("couleurs.txt", "w");
  if(fichier == NULL){
    return -1;
  }

  if(fichier){
    for(int i = 0; i < sizeof(json.valeurs) / sizeof(json.valeurs[0]); i++)
    {
      if(json.valeurs[i][0] != '\0'){
        char insert[50] = "";
        strcpy(insert, json.valeurs[i]);
        strcat(insert, "\n");
        printf("ligne %i : %s", i, insert);
        fputs(insert, fichier);
      }
    }
  }
  fclose(fichier);
  return 0;
}

int traite_balises(JSON json){
  FILE *fichier;
  fichier = fopen("balises.txt", "w");
  if(fichier == NULL){
    return -1;
  }

  if(fichier)
  {
    for(int i = 0; i < sizeof(json.valeurs) / sizeof(json.valeurs[0]); i++)
    {
      if(json.valeurs[i][0] != '\0')
      {
        char insert[50] = "";
        strcpy(insert, json.valeurs[i]);
        strcat(insert, "\n");
        printf("ligne %i : %s", i, insert);
        fputs(insert, fichier);
      }
    }
  }
  fclose(fichier);
  return 0;
}

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
    else {
      // Le numéro 36, parceque 360° (cercle) / 10 couleurs = 36
      fprintf(p, "0 0 10 %d %d 0x%s\n", (count-1)*36, count*36, token+1);
    }
    count++;
  }
  fprintf(p, "e\n");
  printf("Plot: FIN\n");
  pclose(p);
}

/* renvoyer un message (*data) au client (client_socket_fd)
 */
int renvoie_message(int client_socket_fd, char *data) {
  int data_size = write (client_socket_fd, (void *) data, strlen(data));
      
  if (data_size < 0) {
    perror("erreur ecriture");
    return(EXIT_FAILURE);
  }
}

/* accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour
 */
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
  int data_size = read (client_socket_fd, data, sizeof(data));
  printf("Message recu : %s\n", data);
  JSON json = JSONparse(data);

  printf("Parsing en JSON :\n");
  JSONToString(json);
  printf("Message de type : %s\n", json.code);


  //Gestion des retours au client
  char result[1024];
  if (strstr(json.code, "calcul") != NULL)
  {
    int res = traite_calcul(json);
    sprintf(result, "{\"code\":\"calcul\",\"valeurs\":[%d]}", res);
    printf("Resultat : %s\n", result);
    renvoie_message(client_socket_fd, result);
  }
  else if(strstr(json.code, "message") != NULL)
  {
    sprintf(result, "{\"code\":\"message\",\"valeurs\":[\"%s\"]}", json.valeurs[0]);
    printf("Message recu : %s\n", json.valeurs[0]);
    renvoie_message(client_socket_fd, result);
  }
  else if(strstr(json.code, "couleurs"))
  {
    int res = traite_couleurs(json);
    if (res == -1)
    {
      renvoie_message(client_socket_fd, "{\"code\":\"couleurs\",\"valeurs\":[\"Impossible d\'ouvrir le fichier\"]}");
    }
    else if(res == 0)
    {
      renvoie_message(client_socket_fd, "{\"code\":\"couleurs\",\"valeurs\":[\"Couleurs enregistrées\"]}");
    }
  }
  else if(strstr(json.code, "balises")){
    int res = traite_balises(json);
    if(res == -1)
    {
      renvoie_message(client_socket_fd, "{\"code\":\"balises\",\"valeurs\":[\"Impossible d\'ouvrir le fichier\"]}");
    }
    else if(res == 0)
    {
      renvoie_message(client_socket_fd, "{\"code\":\"balises\",\"valeurs\":[\"Balises enregistrées\"]}");
    }
  }

  //fermer le socket 
  close(socketfd);
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
  recois_envoie_message(socketfd);

  return 0;
}
