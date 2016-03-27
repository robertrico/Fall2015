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
