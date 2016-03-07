#include "udp.h"

int main(int argc, char *argv[])
{
	struct sockaddr_in server_address, client_address;
	int sockfd, response_len, addr_len = sizeof(server_address);
	char buffer[BUFF_SIZE];

	/* UDP DGRAM */
	if ((sockfd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("Socket Established\n");

	memset((char *)&server_address, 0, sizeof(server_address)); 
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	int serv_port = SERVER_PORT;
	server_address.sin_port = htons(serv_port);

	/* Collect and send message */
	printf("Enter message to send to server...\n > ");
	memset((char *)&buffer,0,BUFF_SIZE);

	fgets(buffer,BUFF_SIZE,stdin);
	buffer[strcspn(buffer, "\n")] = '\0'; /* Get rid of new line */

	if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_address, addr_len)==-1)
		ERR("Error Sending Message");

	memset((char *)&buffer,0,BUFF_SIZE);
	/* Retrieve Converted Text From Server */
	response_len = recvfrom(sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr *)&server_address, &addr_len);
	if (response_len != -1) {
		buffer[response_len] = '\0';
		printf("Response message: \"%s\"\n", buffer);
	}

	close(sockfd);
	return 0;
}
