#include "tcp_connection.h"

int make_socket(uint16_t port)
{
	WSADATA wsaData;

	int initializeResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(initializeResult != 0)
	{
		lgr_log_error("WSA startup failed!", 0);
		exit(EXIT_FAILURE);
	}


	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		int err = WSAGetLastError();
		lgr_log_error("Could not open socket!", err);
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in name;

	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	int b;
	if(b = bind(sock, (struct sockaddr*)&name, sizeof(name)) < 0)
	{
		int err = WSAGetLastError();
		lgr_log_error("Could not bind to address!", err);
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	return sock;
}

void start_listening(int sock)
{
	if(listen(sock, 1) < 0)
	{
		int err = WSAGetLastError();
		lgr_log_error("Error while attempting to run 'listen()'!", err);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	lgr_log_text("Found connection!");
}

int accept_connection(int sock)
{
	int res = accept(sock, NULL, NULL);
	if(res == INVALID_SOCKET)
	{	
		lgr_log_error("Could not accept connection!", res);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	lgr_log_text("Accepted connection!");
	return res;
}

int receive_data(int sock, uint8_t* buffer, int buf_len)
{
	int res = recv(sock, buffer, buf_len, 0);
	if(res > 0)
	{
		lgr_log_text("Received bytes!");
		lgr_log_bytes(buffer, buf_len);
		return res;
	}

	lgr_log_text("Connection closed!");
	return 0;
}

void kill_all(int sock)
{
	shutdown(sock, SD_SEND);
	WSACleanup();
	exit(EXIT_SUCCESS);
}
