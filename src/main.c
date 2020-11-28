#include "tcp_connection.h"

#define BUFFER_LENGTH 2048

int main(int argc, char* argv[])
{
	lgr_init();
	if(argc != 2)
	{
		lgr_log_error("INVALID ARGC.", 0xDEADBEEF);
		return -1;
	}

	int sockfd = make_socket(atoi(argv[1]));

	start_listening(sockfd);
	
	uint8_t buffer[BUFFER_LENGTH] = {0};
	
	while(1)
	{
		int conn = accept_connection(sockfd);
		while(1)
		{
			memset(buffer, 0x0, sizeof(uint8_t) * BUFFER_LENGTH);
		
			if(receive_data(conn, buffer, BUFFER_LENGTH) == 0)
				break;
		}

	}

	kill_all(sockfd); // unreachable code for now
	return 0;
}
