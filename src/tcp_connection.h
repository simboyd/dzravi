#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include "log.h"

int make_socket(uint16_t);
void start_listening(int);
int accept_connection(int);
int receive_data(int, uint8_t*, int);
void kill_all(int);
