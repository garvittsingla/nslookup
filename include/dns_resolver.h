#ifndef DNS_RESOLVER_H
#define DNS_RESOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <resolv.h>
#include <arpa/inet.h>
#include "common.h"

/**
 * get the default DNS resolver provided by os
 * @return the ip address of the default DNS resolver
 */
char* get_default_dns_resolver (void);

/**
 * set the primary DNS resolver for this query
 * @param resolvers the resolvers to set
 * @param server_addr the server address to set
 */
void set_default_dns_resolver (struct resolvers resolvers,struct sockaddr_in *server_addr);

#endif
