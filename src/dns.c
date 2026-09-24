#include "../include/dns.h"

int populate_request(char *request, char **hostname) {

  int size = populate_request_header(request);
  size += populate_request_questions(request, size, hostname);
  return size;
}

int populate_request_questions(char *request, int header_size,
                               char **hostname) {
  char *qname = qname_from_hostname(hostname);
  int size = 0;
  memcpy(request + header_size + size, qname, strlen(qname) + 1);
  size += strlen(qname) + 1;
  uint16_t qtype = htons(DNS_QTYPE_NS);

  memcpy(request + header_size + size, &qtype, sizeof(qtype));
  size += sizeof(qtype);

  uint16_t qclass = htons(1);

  memcpy(request + header_size + size, &qclass, sizeof(qclass));
  size += sizeof(qclass);

  return size;
}

int populate_request_header(char *request) {
  int size = 0;

  uint16_t id = 1234;
  id = htons(id);
  memcpy(request, &id, sizeof(id));
  size += sizeof(id);

  uint16_t flags = populate_request_flags();
  flags = htons(flags);
  memcpy(request + size, &flags, sizeof(flags));
  size += sizeof(flags);

  uint16_t qdcount = 1;
  qdcount = htons(qdcount);
  memcpy(request + size, &qdcount, sizeof(qdcount));
  size += sizeof(qdcount);

  uint16_t ancount = 0;
  ancount = htons(ancount);
  memcpy(request + size, &ancount, sizeof(ancount));
  size += sizeof(ancount);

  uint16_t nscount = 0;
  nscount = htons(nscount);
  memcpy(request + size, &nscount, sizeof(nscount));
  size += sizeof(nscount);

  uint16_t arcount = 0;
  arcount = htons(arcount);
  memcpy(request + size, &arcount, sizeof(arcount));
  size += sizeof(arcount);

  return size;
}

uint16_t populate_request_flags() {
  uint16_t flags = 0;
  uint16_t qr = 0;
  uint16_t opcode = 0;
  uint16_t aa = 0;
  uint16_t tc = 0;
  uint16_t rd = 1;
  uint16_t ra = 0;
  uint16_t z = 0;
  uint16_t rcode = 0;

  flags = (qr << 15) | (opcode << 11) | (aa << 10) | (tc << 9) | (rd << 8) |
          (ra << 7) | (z << 4) | (rcode << 0);

  return flags;
}

char *qname_from_hostname(char **hostname) {
  int hostname_length = strlen(*hostname);

  int labels = 0;
  for (int i = 0; i < hostname_length; i++) {
    if ((*hostname)[i] == '.') {
      labels++;
    }
  }

  char *qname = malloc(hostname_length + labels + 1);
  if (qname == NULL) {
    exit(-1);
  }

  int index = 0;
  char *token = strtok(*hostname, ".");
  while (token != NULL) {
    int token_length = strlen(token);
    qname[index++] = token_length;
    memcpy(qname + index, token, token_length);
    index += token_length;
    token = strtok(NULL, ".");
  }

  qname[index] = '\0';

  printf("qname: ");

  for (int i = 0; i < index + 1; i++) {
    printf("%02x ", (unsigned char)qname[i]);
  }

  printf("\n");
  return qname;
}