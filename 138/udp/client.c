#include "udp.h"

int main(int argc, char *argv[])
{
	struct sockaddr_in server_address, client_address;
	int sockfd, response_len, addr_len = sizeof(client_address);
	char buffer[BUFF_SIZE];

	/* UDP DGRAM */
	if ((sockfd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("Socket Established\n");

	/* Set up Client Port for message response */
	memset((char *)&server_address, 0, sizeof(server_address)); /* Reset Memory */
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	int cli_port = CLIENT_PORT;
	server_address.sin_port = htons(cli_port);

	if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
		ERR("Error Opening Socket");

	memset((char *) &client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET;
	int serv_port = SERVER_PORT;
	client_address.sin_port = htons(serv_port); /* Send to port defined in udp.h*/
	if (inet_aton((char *)SERVER, &client_address.sin_addr)==0)
		ERR("Error inet_aton() failed");

	/* Collect and send message */
	printf("Enter message to send to server...\n > ");
	memset((char *)&buffer,0,BUFF_SIZE);

	fgets(buffer,BUFF_SIZE,stdin);
	buffer[strcspn(buffer, "\n")] = '\0'; /* Get rid of new line */

	if (sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_address, addr_len)==-1)
		ERR("Error Sending Message");

	memset((char *)&buffer,0,BUFF_SIZE);
	/* Retrieve Converted Text From Server */
	response_len = recvfrom(sockfd, buffer, BUFF_SIZE, 0, (struct sockaddr *)&client_address, &addr_len);
	if (response_len != -1) {
		buffer[response_len] = '\0';
		printf("Response message: \"%s\"\n", buffer);
	}

	close(sockfd);
	return 0;
}
