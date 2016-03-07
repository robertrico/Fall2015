#include "udp.h"
#include <ctype.h>

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr,client_addr;	
	socklen_t addr_len = sizeof(client_addr);
	int response_len;
	int sockfd;
	char *buffer[BUFF_SIZE];

	/* UDP SOCK_DGRAM */
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		ERR("Error Opening Socket");

	memset((char *)&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int port = SERVER_PORT;
	server_addr.sin_port = htons(port);

	printf("Opening Port %d\n", SERVER_PORT);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		ERR("Error Binding Socket");

	while(1) {
		printf("Port %d Open...Waiting on messages...\n", SERVER_PORT);
		memset((char *)&buffer,0,BUFF_SIZE);

		response_len = recvfrom(sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
		/* Check response and terminate */
		if (response_len != -1) {
			buffer[response_len] = '\0'; //Terminate the string
		} else {
			printf("Message failed to recieve.\n");
		}

		/* Port Close message and exit */
		if(strcmp((char *)buffer,"close") == 0){
			printf("Port Closed Remotely...Exiting...\n");
			char msg[BUFF_SIZE];
			memset((char *)&msg,0,BUFF_SIZE);
			strcpy(msg,"Remote Port Closed.\0");

			if (sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&client_addr, addr_len) < 0)
				ERR("Error Responding");

			exit(1);
		}

		/* Convert to uppercase */
		char *cur = (char*)buffer;
		char new[BUFF_SIZE];
		memset((char *)&new,0,BUFF_SIZE);
		int j = 0;
		while(*cur){
			new[j] = toupper(*cur++);
			j++;
		}

		printf("\nReplying with converted response.. \"%s\"\n", new);

		if (sendto(sockfd, new, strlen(new), 0, (struct sockaddr *)&client_addr, addr_len) < 0)
			ERR("Error Responding");
	}
}
