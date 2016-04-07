#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h> 
#include <math.h> 

#define BUFF_SIZE 2048
#define ERR(msg){perror(msg);exit(1);}

//Define a server port to access from client, and init on server
#define SERVER_PORT 3000
#define SERVER "localhost"

struct http_request{
	char *request_method;
	char *http_version;
	char *request;
	char *content_type;
	char *content_len;
	char *serv;
	char *date;
};

struct http_response{
	int *status_code;
	char *status;
	char *date;
	char *file_contents;
	char *content_length;
	int *content_length_int;
	char *full_response;
};

static char* not_found_response_template = 
	"HTTP/1.0 404 Not Found\r\n"
	"Content-Type: text/html\r\n"
	"Content-Length: 176\r\n"
	"\r\n"
	"<html><head><style>h1,h3,p{text-align:center;}</style></head><body><h1>404</h1><h3>File Not found.</h3><p>The file you requested does not exist on the server.</p></body></html>"
	"\r\n"
	"\r\n";
static char *two_hundred_ok = 
	"HTTP/1.1 200 OK"
	"\r\n"
	"Server: webserv/1.0"
	"\r\n";

void buildHead(char *buffer);
void buildResponseDate();
void buildFullResponse();
int getFileContents();
int responseLen();
