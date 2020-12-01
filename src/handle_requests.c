#include "handle_requests.h"

extern pthread_mutex_t fdset_mutex;

void handle_connection(int sock, fd_set* set)
{
	uint8_t receive_buffer[BUFFER_LENGTH] = {0};

	int res = 0;
	pthread_mutex_lock(&fdset_mutex);
	if((res = recv(sock, receive_buffer, BUFFER_LENGTH, 0)) > 0)
	{
		lgr_log_bytes(receive_buffer, res);
		const char* data = "HELLO NIGGA";
		send(sock, data, strlen(data), 0);
	}
	else if(FD_ISSET(sock, set))
	{
		lgr_log_text("Connection closed!");
		close(sock);
		FD_CLR(sock, set);
	}
	else
	{
		//failed attempt at unset
	}
	pthread_mutex_unlock(&fdset_mutex);
}


