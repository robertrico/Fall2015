//Standard Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//Networking Libraries
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Buffer Size
#define BUFF_SIZE 2048
#define ERR(msg){perror(msg);exit(1);}

//Define a server port to access from client, and init on server
#define SERVER "127.0.0.1"
#define SERVER_PORT 66666
