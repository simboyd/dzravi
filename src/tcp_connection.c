#include "tcp_connection.h"

int make_socket(uint16_t port)
{
	int sock;
	if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		int err = errno;
		lgr_log_error("Could not open socket!", err);
		exit(EXIT_FAILURE);
	}


	int option = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	struct sockaddr_in name;
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	int b;
	if((b = bind(sock, (struct sockaddr*)&name, sizeof(name))) < 0)
	{
		int err = errno;
		lgr_log_error("Could not bind to address!", err);
		close(sock);
		exit(EXIT_FAILURE);
	}

	return sock;
}

void start_listening(int sock)
{
	int ret;
	if((ret = listen(sock, 1024)) < 0)
	{
		int err = errno;
		lgr_log_error("Error while attempting to run 'listen()'!", err);
		close(sock);
		exit(EXIT_FAILURE);
	}
}

int accept_connection(int sock)
{
	lgr_log_text("Waiting for connection...");

	int res;
	if((res = accept(sock, NULL, NULL)) < 0)
	{
		int err = errno;
		lgr_log_error("Could not accept connection!", err);
		close(sock);
		exit(EXIT_FAILURE);
	}
	lgr_log_text("Accepted connection!");
	return res;
}

int receive_data(int sock, uint8_t* buffer, int buf_len)
{
	int res;
	if((res = recv(sock, (char*)buffer, buf_len, 0)) > 0)
	{
		lgr_log_bytes(buffer, res);
		return res;
	}
	lgr_log_text("Connection closed!");
	return 0;
}

void kill_all(int sock)
{
	close(sock);
	exit(EXIT_SUCCESS);
}
