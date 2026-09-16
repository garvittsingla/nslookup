#include <stdio.h>
#include <stdlib.h>
#include <resolv.h>
#include <arpa/inet.h>

char* get_default_dns_resolver() {
    int status = res_init();
    if (status!=0) {
        return NULL;
    }
    
    char *resolvers = malloc(1024);
    
    if (resolvers == NULL) {
        return NULL;
    }

    if (inet_ntop(AF_INET,&_res.nsaddr_list[0].sin_addr,resolvers,INET_ADDRSTRLEN) == NULL){
           free(resolvers);
           return NULL;
    }
    printf("resolver: %s\n", resolvers);
    return resolvers;
}
