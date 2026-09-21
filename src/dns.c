#include "../include/dns.h"

void populate_request_header(char *request){
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