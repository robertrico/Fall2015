#include "tcp.h" 

struct http_request header;

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

		buildHead((char*)&buffer);

		printf("Request Method : %s\n",header.request_method);
		//printf("%s\n",header.http_version);

		/*

		HTTP/1.1 200 OK
		Date: Thu, 25 Jul 2013 03:55:00 GMT
		Server: sadaf2605-server/1.0
		Content-Type: text/html
		Content-Length: 40595

		< contents of filename.html follows here >
		*/

		//n = write(newsockfd,new,BUFF_SIZE);

		if (n < 0)
			ERR("Error Responding");
	}
	return 0; 
}

void buildHead(char *buffer){
	char *end_str;
	char *token = strtok_r(buffer,"\r\n",&end_str);

	while(token != NULL){
		/* While there are tokens in "string" */
		char new[strlen(token)];
		char *end_token;
		int strln = strlen(token);
		strncpy( new, token, strlen(token) );
		new[strln]='\0';
		char *tok2;
		//printf("%s\n",new);
		tok2 = strtok_r(&new," ",&end_token);
		int method_set = 0;
		while(tok2 != NULL){
			if(!method_set && (strcmp(tok2,"GET") == 0 || strcmp(tok2,"POST") == 0 || strcmp(tok2,"PUT") == 0 || strcmp(tok2,"DELETE") == 0)){
				header.request_method = malloc(strlen(tok2) * sizeof(char));
				strcpy(header.request_method, tok2);
				method_set = 1;
			}
			printf("%s\n", tok2);
			tok2 = strtok_r( NULL, "\r\n",&end_token);
		}
		
		/* Get next token: */
		//printf("%s\n",token);
		token = strtok_r( NULL, "\r\n",&end_str);
	}
}
