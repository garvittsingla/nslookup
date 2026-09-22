#ifndef DNS
#define DNS

#include <stdint.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * DNS response codes
 */
#define DNS_RESPONSE_NO_ERROR 0
#define DNS_RESPONSE_FORMAT_ERROR 1
#define DNS_RESPONSE_SERVER_FAILURE 2
#define DNS_RESPONSE_NAME_ERROR 3
#define DNS_RESPONSE_NOT_IMPLEMENTED 4
#define DNS_RESPONSE_REFUSED 5
#define DNS_RESPONSE_RESERVED 6

/**
 * DNS query types
 */
#define DNS_QTYPE_A 1
#define DNS_QTYPE_NS 2
#define DNS_QTYPE_MD 3
#define DNS_QTYPE_MF 4
#define DNS_QTYPE_CNAME 5
#define DNS_QTYPE_SOA 6
#define DNS_QTYPE_MB 7
#define DNS_QTYPE_MG 8
#define DNS_QTYPE_MR 9
#define DNS_QTYPE_NULL 10
#define DNS_QTYPE_WKS 11
#define DNS_QTYPE_PTR 12
#define DNS_QTYPE_HINFO 13
#define DNS_QTYPE_MINFO 14
#define DNS_QTYPE_MX 15
#define DNS_QTYPE_TXT 16
#define DNS_QTYPE_AXFR 252
#define DNS_QTYPE_MAILB 253
#define DNS_QTYPE_MAILA 254
#define DNS_QTYPE_ALL 255


/**
 * make the dns request
 * @param request pointer to populate
 */
void populate_request(char *request, char** hostname);

/**
 * make the dns request header 
 * @param request pointer to populate
 * @return size of request
 */
int populate_request_header(char *request);

/**
 * make the dns request questions
 * @param request pointer to populate
 * @param header_size size of the request header
 */
void populate_request_questions(char *request, int header_size,char** hostname);

/**
 * populate the dns request flags
 * @return flags
 */
uint16_t populate_request_flags();

/**
 * populate the qname from the hostname
 * @param hostname hostname to convert
 * @return qname
 */
char* qname_from_hostname(char **hostname);

#endif