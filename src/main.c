#include "tcp_connection.h"

#define BUFFER_LENGTH 2048

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		lgr_log_error("INVALID ARGC.", 0);
		return -1;
	}

	int sockfd = make_socket(atoi(argv[1]));

	start_listening(sockfd);
	
	uint8_t buffer[BUFFER_LENGTH] = {0};
	
	int conn = accept_connection(sockfd);
	while(1)
	{
		memset(buffer, 0x0, sizeof(int) * BUFFER_LENGTH);
		int res = receive_data(conn, buffer, BUFFER_LENGTH);
		if(res == 0)
			break;
		printf("%s (%d bytes)\n", (char*)buffer, res);
	}

	printf("Identifier: %d\n", sockfd);
	kill_all(sockfd);
	return 0;
}
