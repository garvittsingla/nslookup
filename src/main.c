#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../include/dns_resolver.h"
#include "../include/common.h"
#include "../include/cli_parser.h"


int main(int argc,char *argv[]){
    struct resolvers resolvers = {.current_index = 0, .primary = get_default_dns_resolver(), .secondary = "1.1.1.1", .tertiary = "8.8.8.8"};
    char *hostname = "";
    
    parse_cli(argc,argv,hostname,&resolvers);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(53);

    set_default_dns_resolver(resolvers,&server_addr);

    printf("resolver: %s\n", resolvers.primary);
    char request[512]; //dns request is 512 bytes

    memset(request, 0, sizeof(request));

    uint16_t id = 1234;
    id = htons(id);
    memcpy(request, &id, sizeof(id));

    uint16_t flags = 0;
    flags = htons(flags);
    memcpy(request + sizeof(id), &flags, sizeof(flags));

    uint16_t qdcount = 1;
    qdcount = htons(qdcount);
    memcpy(request + sizeof(id) + sizeof(flags), &qdcount, sizeof(qdcount));

    uint16_t ancount = htons(0);
    memcpy(request + sizeof(id) + sizeof(flags) + sizeof(qdcount),
           &ancount, sizeof(ancount));

    uint16_t nscount = htons(0);
    memcpy(request + sizeof(id) + sizeof(flags) + sizeof(qdcount) + sizeof(ancount),
           &nscount, sizeof(nscount));

    uint16_t arcount = htons(0);
    memcpy(request + sizeof(id) + sizeof(flags) + sizeof(qdcount) + sizeof(ancount) + sizeof(nscount),
           &arcount, sizeof(arcount));

}
