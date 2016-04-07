#ifndef WS_H
#define WS_H
#include"webserv.h" 
#endif 

struct http_request request_header;
struct http_response response_header;

int main(int argc, char *argv[])
{
	unsigned int sockfd, newsockfd, clilen;
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

		parseRequest((char*)&buffer);

		char *response = NULL;
		memset(&response, 0, sizeof(request_header.request)); /* Reset Memory */
		if(getFileContents(request_header.request)){
			buildResponseDate();
			buildFullResponse();
			response = response_header.full_response;
		}else{
			response = not_found_response_template;
		}

		response_header.full_response = NULL;
		printf("Response : \n%s\n",response);

		n = write(newsockfd,response,strlen(response));
		close(newsockfd);

		if (n < 0)
			ERR("Error Responding");
	}
	return 0; 
}

/**
 * Parse the incoming TCP request.
 *	Special case first line, strtok by space.
 *	Strtok by : after first line.
 */
void parseRequest(char *buffer){
	char *end_str;
	char *token = strtok_r(buffer,"\r\n",&end_str);
	int method_set = 0;
	int first_line = 1;
	printf("Parsing request:\n\n%s\n\n",buffer);

	while(token != NULL){
		/* While there are tokens in "string" */
		char new[strlen(token)];
		char *end_token;
		char *end_token2;
		int strln = strlen(token);
		strncpy( new, token, strlen(token) );
		new[strln]='\0';
		char *tok2,*tok3;

		
		if(first_line){
			tok2 = strtok_r(new," ",&end_token);
			first_line = 0;
			tok3 = NULL;
		}else{
			tok3 = strtok_r(new,":",&end_token2);
			tok2 = NULL;
		}
		while(tok2 != NULL){
			if(!method_set && (strcmp(tok2,"GET") == 0 || strcmp(tok2,"POST") == 0 || strcmp(tok2,"PUT") == 0 || strcmp(tok2,"DELETE") == 0)){
				request_header.request_method = malloc(strlen(tok2) * sizeof(char));
				strcpy(request_header.request_method, tok2);
				method_set = 1;
			}

			tok2 = strtok_r( NULL, " ",&end_token);
			request_header.request = malloc(strlen(tok2) * sizeof(char));
			strcpy(request_header.request, ++tok2);

			tok2 = strtok_r( NULL, " ",&end_token);
			request_header.http_version = malloc(strlen(tok2) * sizeof(char));
			strcpy(request_header.http_version, tok2);
			tok2 = NULL;
		}
		while(tok3 != NULL){
			tok3 = strtok_r( NULL, ":",&end_token2);
		}
		
		/* Get next token: */
		token = strtok_r( NULL, "\r\n",&end_str);
	}
}

/**
 * Build proper TCP Formatted date.
 */
void buildResponseDate(){
	char time_buf[1000];
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(time_buf,sizeof time_buf, "Date: %a %d %b %Y %H:%M:%S %Z\r\n", &tm);
	response_header.date = malloc(sizeof(time_buf));
	response_header.date = time_buf;
}

/**
 * Get the requested file contents, and also get 
 * the content length of the data file.
 */
int getFileContents(char *filename){
	unsigned long length;
	FILE *fp = fopen(filename,"rb");
	if(fp){
		fseek(fp,0,SEEK_END);
		length = ftell(fp);
		fseek(fp,0,SEEK_SET);
		response_header.file_contents = malloc(length);
		if(response_header.file_contents){
			fread(response_header.file_contents,1,length,fp);
			char cl[2048];
			strcpy(cl,"Content-Length: ");
			char int_len[(int)floor(log10(abs(length)))+1];
			sprintf(int_len,"%lu",length);
			strcat(cl,int_len);
			strcat(cl,"\r\n");
			strcat(cl,"\0");
			response_header.content_length = malloc(sizeof(cl)); 
			response_header.content_length = cl; 
			response_header.content_length_int = (int*)length; 
			return 1;
		}
	}
	return 0;
}

/**
 * Build Full Response including headers to send to requester
 */
void buildFullResponse(){
	char final_form[responseLen()+100];
	final_form[0] = '\0';
	final_form[responseLen()+100] = '\0';
	strcat(final_form,two_hundred_ok);
	strcat(final_form,response_header.date);
	strcat(final_form,response_header.content_length);
	strcat(final_form,"\r\n");
	strcat(final_form,response_header.file_contents);
	strcat(final_form,"\r\n");
	strcat(final_form,"\r\n");
	response_header.full_response = malloc(sizeof(final_form));
	memset(response_header.full_response, 0, sizeof(final_form)); /* Reset Memory */
	strcpy(response_header.full_response,final_form);
}

/**
 * Get Full Response length to attach to header
 */
int responseLen(){
	int ok = strlen(two_hundred_ok);
	int date = strlen(response_header.date);
	int cl = strlen(response_header.content_length);
	int cll = (int)response_header.content_length_int;
	return ((ok+date+cl)*sizeof(char))+cll;

}
