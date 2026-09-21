build : 
	gcc src/main.c src/dns.c src/dns_resolver.c src/cli_parser.c -lresolv -o lookup