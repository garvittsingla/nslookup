#include "../include/cli_parser.h"


void parse_cli(int argc, char* argv[],char *hostname,struct resolvers* resolvers){
    if(argc < 2){
        printf("Incorrect usage: ./lookup hostname/domain (options:dns_server)");
        exit(1);
    }
    hostname = argv[1];
    if(argc == 3){
        resolvers->primary = argv[2];
    }

    if(argc > 3){
        printf("Too many arguments: Incorrect usage: ./lookup hostname/domain (options:dns_server)");
        exit(1);
    }
}