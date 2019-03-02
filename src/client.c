#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SOCK_ERROR              -1
#define PROTOCOL_TYPE_SOCK       0
#define PORT_SOCK             5100

int main() {

  int sock, connection;
  char client_msg[1024],
       server_msg[1024],
          addressIP[12];

  struct sockaddr_in address;

  //Creating socket
  if((sock = socket(AF_INET, SOCK_STREAM, PROTOCOL_TYPE_SOCK)) == SOCK_ERROR)
  {
    perror("[ERROR] socket");
    return 0;
  }
  printf("[OK]: socket() -> successfully\n");

  printf("[OK]: Digite o endereço do servido (IPv4): ");
  scanf("%[^\n]s", addressIP);
  setbuf(stdin, NULL);

  address.sin_family      = AF_INET;
  address.sin_port        = htons(PORT_SOCK);
  address.sin_addr.s_addr = inet_addr(addressIP);

  //Connected with the Server
  if(connect(sock, (struct sockaddr*)&address, sizeof(address)) == SOCK_ERROR)
  {
    perror("[ERROR] connect");
    return 0;
  }
  printf("[OK]: connect() -> successfully\n");

  do{
    memset(client_msg, 0, sizeof(client_msg));
    memset(server_msg, 0, sizeof(server_msg));

    //Receiving message from Server
    connection = recv(sock, &server_msg, sizeof(server_msg), 0);
    if(connection == SOCK_ERROR)
    {
      perror("[ERROR] recv");
      break;
    }
    if(strcmp(server_msg, "exit") == 0){
      printf("Exiting...\n");
      break;
    }
    printf("[SERVER] MSG: %s\n", server_msg);

    //Sending message to the Server
    printf("[CLIENT] MSG: ");
    scanf("%[^\n]s", &client_msg);
    setbuf(stdin, NULL);
    send(sock, &client_msg, strlen(client_msg), 0);

  }while (!strcmp(client_msg, "exit") == 0);

  shutdown(sock, SHUT_RDWR);
  return 1;
}
