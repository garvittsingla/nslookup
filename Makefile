build : 
	gcc src/main.c src/default_dns_resolver.c -lresolv -o lookup