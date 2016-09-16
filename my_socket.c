#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void) {


  struct addrinfo {
   int ai_flags; // AI_PASSIVE, AI_CANONNAME, т.д.
   int ai_family; // AF_INET, AF_INET6, AF_UNSPEC
   int ai_socktype; // SOCK_STREAM, SOCK_DGRAM
   int ai_protocol; // используйте 0 для"any"
   size_t ai_addrlen; // размер ai_addr в байтах
   struct sockaddr *ai_addr; // struct sockaddr_in или _in6
   char *ai_canonname; // полное каноническое имя хоста
   struct addrinfo *ai_next; // связанный список, следующий
  };

  printf("Welcome\n" );
  getaddrinfo();
  printf("\n", addrinfo);

}
