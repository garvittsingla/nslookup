#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "../include/default_dns_resolver.h"

struct dns_question_format{
    uint16_t qtype; // type of question
    uint16_t qclass; // class of question
    char qname[256]; // name of question
};

struct dns_resource_record_format{
    uint16_t type; // type of resource record
    uint16_t class; // class of resource record
    uint32_t ttl; // time to live
    uint16_t rdlength; // length of rdata
    char rdata[256]; // rdata of resource record
};

// for my refernce
struct dns_request_format{
    uint16_t id; // for a application for multiple queries
    uint16_t flags; // some flags that indicate the type of query
    uint16_t qdcount; // number of questions
    uint16_t ancount; // number of answers
    uint16_t nscount; // number of name servers
    uint16_t arcount; // number of additional records
    struct dns_question_format questions[1]; // array of questions
    struct dns_resource_record_format answers[1]; // array of answers
    struct dns_resource_record_format name_servers[1]; // array of name servers
    struct dns_resource_record_format additional_records[1]; // array of additional records
};

struct resolvers {
    int current_index;
    char *primary;
    char *secondary;
    char *tertiary;
};

int main(int argc,char *argv[]){
    struct resolvers resolvers = {.current_index = 0, .primary = get_default_dns_resolver(), .secondary = "1.1.1.1", .tertiary = "8.8.8.8"};
    char *hostname = "";

    if(argc < 2){
        printf("Incorrect usage: ./lookup hostname/domain (options:dns_server)");
        exit(1);
    }
    hostname = argv[1];
    if(argc == 3){
        resolvers.primary = argv[2];
    }

    if(argc > 3){
        printf("Too many arguments: Incorrect usage: ./lookup hostname/domain (options:dns_server)");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(53);

    for(int i = 0 ; i < 3 ; i++){
        if(i == 0){
            if(inet_pton(AF_INET, resolvers.primary, &server_addr.sin_addr)  != -1 ){
                resolvers.current_index = 0;
                break;
            }
        }else if(i == 1){
            if(inet_pton(AF_INET, resolvers.secondary, &server_addr.sin_addr)  != -1 ){
                resolvers.current_index = 1;
                break;
            }
        }else if(i == 2){
            if(inet_pton(AF_INET, resolvers.tertiary, &server_addr.sin_addr)  != -1 ){
                resolvers.current_index = 2;
                break;
            }
        }

        if(i == 2){
            printf("No valid DNS server address found\n");
            exit(1);
        }
        
    }

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
