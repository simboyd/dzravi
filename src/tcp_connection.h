#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>

#include "log.h"

int make_socket(uint16_t);
void start_listening(int);
int accept_connection(int);
int receive_data(int, uint8_t*, int);
void kill_all(int);
