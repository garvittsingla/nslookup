#ifndef DNS
#define DNS

#include <stdint.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>


void populate_request_header(char *request);

#endif