#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SOCK_ERROR              -1
#define PROTOCOL_TYPE_SOCK       0
#define PORT_SOCK             5000

int main() {

  int sock, connection;
  char client_msg[1024],
       server_msg[1024];

  struct sockaddr_in address;
  address.sin_family    = AF_INET;
  address.sin_port      = htons(PORT_SOCK);
  memset(address.sin_zero, 0x0, 8);

  //Creating socket
  if((sock = socket(AF_INET, SOCK_STREAM, PROTOCOL_TYPE_SOCK)) == SOCK_ERROR) {
    perror("[ERROR] socket");
    return 0;
  }
  printf("[OK]: socket() -> successfully\n");

  //Creating bind
  if(bind(sock, (struct sockaddr*)&address, sizeof(address)) == SOCK_ERROR) {
    perror("[ERROR] bind");
    return 0;
  }
  printf("[OK]: bind() -> successfully\n");

  //Creating listen
  if(listen(sock, 0)) {
    perror("[ERROR] listen");
    return 0;
  }
  printf("[OK]: listen() -> successfully\n[OK]: waiting connection with client...\n");

  //Client connected
  int size = sizeof(address);
  if((sock = accept(sock, (struct sockaddr*)&address, &size)) == SOCK_ERROR) {
    perror("[ERROR] accept");
    return 0;
  }
  printf("[OK]: accept() -> successfully\n[OBS]: to exit this session, typing \"exit\"\n");
  strcpy(server_msg, "CONECTADO");
  send(sock, server_msg, 1024, 0);

  do {
    //Clean buffer
    memset(server_msg, 0, sizeof(server_msg));
    memset(client_msg, 0, sizeof(client_msg));

    //Receiving message from Client:
    connection = recv(sock, &client_msg, sizeof(client_msg), 0);
    if(connection == SOCK_ERROR) {
      perror("[ERROR] recv");
      break;
    }
    printf("[CLIENT] MSG: %s\n", client_msg);

    if(strcmp(client_msg, "exit") == 0){
      printf("Exiting...\n");
      break;
    }

    //Sending message to the Client:
    printf("[SERVER] MSG: ");
    scanf("%[^\n]s", server_msg);
    setbuf(stdin, NULL);
    send(sock, &server_msg, strlen(server_msg), 0);

  }while (!strcmp(server_msg, "exit")==0);

  //Closing socket
  shutdown(sock, SHUT_RDWR);

  return 1;
}
