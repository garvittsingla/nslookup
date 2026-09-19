#ifndef DNS_RESOLVER_H
#define DNS_RESOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <resolv.h>
#include <arpa/inet.h>
#include "common.h"


char* get_default_dns_resolver(void);
void set_default_dns_resolver (struct resolvers resolvers,struct sockaddr_in *server_addr);

#endif
