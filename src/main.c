#include "tcp_connection.h"

int main(int argc, char* argv[])
{
	lgr_init();
	if(argc != 2)
	{
		lgr_log_error("Usage: ./dzravi [port]", 0xDEADBEEF);
		return -1;
	}

	uint16_t port = atoi(argv[1]);
	int sockfd = make_socket(port);
	
	handle_socket(sockfd);

	return 0;
}
