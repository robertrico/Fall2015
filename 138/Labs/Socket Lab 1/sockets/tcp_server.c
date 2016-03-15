#include "tcp.h" 

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, clilen;
	char buffer[BUFF_SIZE];
	struct sockaddr_in server_addr, cli_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		ERR("Error Opening Socket");

	memset((char *)&server_addr, 0, sizeof(server_addr)); /* Reset Memory */
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int port = SERVER_PORT;
    server_addr.sin_port = htons(port);

	if (bind(sockfd, (struct sockaddr *) &server_addr,sizeof(server_addr)) < 0)
		ERR("Error Binding Socket");

	while(1){
		printf("Waiting for messages on Port %d...\n",SERVER_PORT);
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if (newsockfd < 0)
			ERR("Error Accepting Message");

		memset((char *)&buffer, 0, BUFF_SIZE);
		n = read(newsockfd,buffer,255);

		if (n < 0)
			ERR("Error Reading Message");

		/* Port Close message and exit */
		if(strcmp(buffer,"close") == 0){
			printf("\nPort Closed Remotely...Exiting...\n");
			char msg[BUFF_SIZE];
			memset((char *)&msg,0,BUFF_SIZE);
			strcpy(msg,"Remote Port Closed.\0");

			printf("\nReplying with termination response.. \"%s\"\n", msg);
			n = write(newsockfd,msg,BUFF_SIZE);
			exit(1);
		}

		/* Convert to uppercase */
		char *cur = buffer;
		char new[BUFF_SIZE];
		memset((char *)&new, 0, BUFF_SIZE);
		int j = 0;
		while(*cur){
			new[j] = toupper(*cur++);
			j++;
		}

		printf("\nReplying with converted response.. \"%s\"\n", new);
		n = write(newsockfd,new,BUFF_SIZE);

		if (n < 0)
			ERR("Error Responding");
	}
	return 0; 
}
