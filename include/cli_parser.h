#ifndef CLI_PARSER
#define CLI_PARSER

#include "stdio.h"
#include <stdlib.h>
#include "common.h"

void parse_cli(int argc, char* argv[],char *hostname,struct resolvers *resolvers);

#endif