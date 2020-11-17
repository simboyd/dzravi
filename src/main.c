#include "tcp_connection.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		lgr_log_error("INVALID ARGC.", 0);
		return -1;
	}

	int sockfd = make_socket(atoi(argv[1]));
	start_listening(sockfd);
	accept_connection(sockfd);
	uint8_t buffer[2048] = {0};
	receive_data(sockfd, buffer, 2048);
	printf("%s\n", (char*)buffer);
	printf("Identifier: %d\n", sockfd);
	kill_all(sockfd);
	return 0;
}
