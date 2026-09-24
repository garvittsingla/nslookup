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

  
}
