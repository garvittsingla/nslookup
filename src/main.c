#include "../include/cli_parser.h"
#include "../include/common.h"
#include "../include/dns.h"
#include "../include/dns_resolver.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct resolvers resolvers = {.current_index = 0,
                                .primary = get_default_dns_resolver(),
                                .secondary = "1.1.1.1",
                                .tertiary = "8.8.8.8"};
  char *hostname = "";

  parse_cli(argc, argv, &hostname, &resolvers);
  printf("hostname %s\n", hostname);

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(53);

  set_default_dns_resolver(resolvers, &server_addr);

  printf("resolver: %s\n", resolvers.primary);
  char request[512];

  int bytes_populated = populate_request(request, &hostname);

  printf("DNS resolver = %s\n", resolvers.primary);
  printf("DNS IP = %s\n", inet_ntoa(server_addr.sin_addr));
  printf("DNS port = %d\n", ntohs(server_addr.sin_port));

  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  int bytes_send = sendto(sock, request, bytes_populated, 0,
                          (struct sockaddr *)&server_addr, sizeof(server_addr));

  printf("bytes sent: %d\n", bytes_send);
  if (bytes_send < bytes_populated) {
    perror("sendto");
    return 1;
  }

  char response[512];

  int bytes_recv = recvfrom(sock, response, sizeof(response), 0, NULL, NULL);

  printf("bytes recieved: %d\n", bytes_recv);
  if (bytes_recv == -1) {
    perror("recvfrom");
    return 1;
  }
}
