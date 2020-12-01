#include "handle_requests.h"

void handle_connection(int sock)
{
	uint8_t receive_buffer[BUFFER_LENGTH] = {0};

	int res = 0;
	while((res = recv(sock, receive_buffer, BUFFER_LENGTH, 0)) > 0)
	{
		lgr_log_bytes(receive_buffer, res);
		const char* data = "Test data.";

		send(sock, data, strlen(data), 0);
		lgr_log_text("Sent bytes to client.");
	}

	lgr_log_text("Connection closed!");
	close(sock);
}
