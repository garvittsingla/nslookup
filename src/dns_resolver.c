#include "../include/dns_resolver.h"

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
    return resolvers;
}

void set_default_dns_resolver (struct resolvers resolvers,struct sockaddr_in *server_addr){
    
    for(int i = 0 ; i < 3 ; i++){
        if(i == 0){
            if(inet_pton(AF_INET, resolvers.primary, &server_addr->sin_addr)  != -1 ){
                resolvers.current_index = 0;
                break;
            }
        }else if(i == 1){
            if(inet_pton(AF_INET, resolvers.secondary, &server_addr->sin_addr)  != -1 ){
                resolvers.current_index = 1;
                break;
            }
        }else if(i == 2){
            if(inet_pton(AF_INET, resolvers.tertiary, &server_addr->sin_addr)  != -1 ){
                resolvers.current_index = 2;
                break;
            }
        }

        if(i == 2){
            printf("No valid DNS server address found\n");
            exit(1);
        }
        
    }
}