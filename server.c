#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 1024

//function declaration
void Display(int sockfd, struct sockaddr_in addr);
void error_handler(char* message);

int main() {

  // Defining the IP and Port
  char *ip = "127.0.0.1";
  const int port = 8080;

  // Defining variables
  int server_sockfd;
  struct sockaddr_in server_addr, client_addr;
  char buffer[SIZE];
  int e;

  // Creating a UDP socket
  server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_sockfd < 0) {
    error_handler("[ERROR] socket error");
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (e < 0) {
    error_handler("[ERROR] bind error");
    
  }

  printf("[STARTING] UDP File Server started. \n");
  Display(server_sockfd, client_addr);

  printf("\n[SUCCESS] Data transfer complete.\n");
  printf("[CLOSING] Closing the server.\n");

  close(server_sockfd);

  return 0;
}


//display function 
void Display(int sockfd, struct sockaddr_in addr) {

  int n;
  char buffer[SIZE];
  socklen_t addr_size;

  // Receiving the data and display.
  while (1) {
    addr_size = sizeof(addr);
    n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr *)&addr, &addr_size);

    if (strcmp(buffer, "END") == 0) {
      break;
    }

    printf("[RECEVING] Data: %s", buffer);
    //printf("%s", buffer);
    bzero(buffer, SIZE);
  }

}

//error handler function
void error_handler(char* message){
	perror(message);
	exit(EXIT_FAILURE);
}
