#ifndef CLI_PARSER
#define CLI_PARSER

#include "stdio.h"
#include <stdlib.h>
#include "common.h"

/**
 * parse the command line arguments and set the hostname and resolvers
 * @param argc the number of arguments
 * @param argv the arguments
 * @param hostname the hostname to resolve
 * @param resolvers the resolvers to set
 */
void parse_cli(int argc, char* argv[],char **hostname,struct resolvers *resolvers);

#endif