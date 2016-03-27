#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFF_SIZE 2048
#define ERR(msg){perror(msg);exit(1);}

//Define a server port to access from client, and init on server
#define SERVER_PORT 3000
#define SERVER "localhost"

struct http_request{
	char *request_method;
	char *http_version;
	char *content_type;
	char *content_len;
	char *serv;
	char *date;
};

struct http_respones{
	char *status;
	int *status_code;
};

void buildHead(char *buffer);
