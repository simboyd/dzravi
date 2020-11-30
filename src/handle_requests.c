#include "handle_requests.h"

int handle_connection(int sock)
{
	uint8_t receive_buffer[BUFFER_LENGTH] = {0};

	int res;
	if((res = recv(sock, receive_buffer, BUFFER_LENGTH, 0)) > 0)
	{
		lgr_log_bytes(receive_buffer, res);
		const char* data = "HELLO NIGGA";
		send(sock, data, strlen(data), 0);
	}
	else
	{
		lgr_log_text("Connection closed!");
		close(sock);
	}

	return res;
}


