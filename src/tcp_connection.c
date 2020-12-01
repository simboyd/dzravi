#include "tcp_connection.h"

static int accept_connection(int);
static void* connection_multiplexer(void*);
void handle_connection(int);

pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
queue_t* queue = NULL;

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

	int l;
	if((l = listen(sock, 1024)) < 0)
	{
		int err = errno;
		lgr_log_error("Error while trying to socket for accepting connections!", err);
		close(sock);
		exit(EXIT_FAILURE);
	}

	return sock;
}

void handle_socket(int sock)
{
	for(int i = 0; i < THREAD_POOL_SIZE; i++)
	{
		pthread_create(&thread_pool[i], NULL, connection_multiplexer, NULL);
	}


	lgr_log_text("Waiting for connections...");
	while(1)
	{
		int client = accept_connection(sock);

		if(client == -1)
			continue;

		pthread_mutex_lock(&queue_mutex);

		enqueue(&queue, client);
		pthread_cond_signal(&cond);
		
		pthread_mutex_unlock(&queue_mutex);
	}
}

static int accept_connection(int sock)
{
	int res;
	if((res = accept(sock, NULL, NULL)) < 0)
	{
		int err = errno;
		lgr_log_error("Could not accept connection!", err);
		return -1;
	}
	lgr_log_text("Accepted connection!");
	return res;
}

static void* connection_multiplexer(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&queue_mutex);

		int sockfd;
	   	if((sockfd = dequeue(&queue)) == -1)
		{
			pthread_cond_wait(&cond, &queue_mutex);
			sockfd = dequeue(&queue);
		}
		
		pthread_mutex_unlock(&queue_mutex);

		if(sockfd != -1)
		{
			handle_connection(sockfd);
			usleep(1);			
		}
	}

	return NULL;
}

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
