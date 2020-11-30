#include "tcp_connection.h"

static int accept_connection(int);
static void* connection_multiplexer(void*);
void printQueue(); //test
int isInQueue(int);//test

pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_mutex_t fdset_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
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
	fd_set current, ready;
	FD_ZERO(&current);
	FD_SET(sock, &current);


	for(int i = 0; i < THREAD_POOL_SIZE; i++)
	{
		pthread_create(&thread_pool[i], NULL, connection_multiplexer, &current);
	}


	lgr_log_text("Waiting for connections...");
	while(1)
	{
		pthread_mutex_lock(&fdset_mutex);
		ready = current;
		pthread_mutex_unlock(&fdset_mutex);
		
		if(select(FD_SETSIZE, &ready, NULL, NULL, NULL) < 0)
		{
			int err = errno;
			lgr_log_error("Select() encountered an error!", err);
			close(sock);
			exit(EXIT_FAILURE);
		}
	
		pthread_mutex_lock(&fdset_mutex);	
		for(int fd = 0; fd < FD_SETSIZE; fd++)
		{
				
			//pthread_mutex_lock(&fdset_mutex);
			int fd_is_set = FD_ISSET(fd, &ready);
			//pthread_mutex_unlock(&fdset_mutex);

			if(fd_is_set)
			{
				if(fd == sock)
				{
					int client = accept_connection(sock);
					if(client != -1)
					{
						//pthread_mutex_lock(&fdset_mutex);
						FD_SET(client, &current);
						//pthread_mutex_unlock(&fdset_mutex);
					}
				}
				else
				{
					pthread_mutex_lock(&queue_mutex);
					if(!isInQueue(fd)) enqueue(&queue, fd);
					pthread_mutex_unlock(&queue_mutex);
				}
			}

		}
		pthread_mutex_unlock(&fdset_mutex);
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

void printQueue() // test
{
	queue_t* tmp = queue;
	int idx = 0;
	while(tmp != NULL)
	{
		printf("tmp=%d, thread=%ld, idx=%d\n", tmp->data, pthread_self(), idx++);
		tmp = tmp->next;
	}
}

int isInQueue(int num) // test
{
	queue_t* tmp = queue;
	int res = 0;
	while(tmp != NULL)
	{
		if(tmp->data == num)
		{
			res = 1;
			break;
		}
		tmp = tmp->next;
	}
	return res;
}

static void* connection_multiplexer(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&queue_mutex);
		printQueue();
		int sockfd = dequeue(&queue);
		pthread_mutex_unlock(&queue_mutex);

		if(sockfd != -1)
		{
			pthread_mutex_lock(&fdset_mutex);
			int b = handle_connection(sockfd);

			if(b <= 0)
			{
				FD_CLR(sockfd, (fd_set*)arg);
			}
			pthread_mutex_unlock(&fdset_mutex);
		}
	}

	return NULL;
}

