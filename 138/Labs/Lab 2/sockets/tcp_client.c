#include "tcp.h" 

int main(int argc, char *argv[])
{
    int sockfd, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
		ERR("Error Opening Socket");

    server = gethostbyname(SERVER);
    if (server == NULL)
		ERR("Error Resolving Host");
    
	memset((char *)&serv_addr, 0, sizeof(serv_addr)); /* Reset Memory */
    serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int port = SERVER_PORT;
    serv_addr.sin_port = htons(port);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
		ERR("Error Connection");

	printf("Enter message to send to server...\n > ");

	memset((char *)&buffer, 0, BUFF_SIZE);
    fgets(buffer,BUFF_SIZE,stdin);
	buffer[strcspn(buffer, "\n")] = '\0'; /* Get rid of new line */

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
		ERR("Error Sending Message");
	memset((char *)&buffer, 0, BUFF_SIZE);

    n = read(sockfd,buffer,BUFF_SIZE);

    if (n < 0) 
		ERR("Error Recieving Response");

    printf("%s\n",buffer);
    return 0;
}
