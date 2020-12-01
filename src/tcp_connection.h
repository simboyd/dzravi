#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/select.h>
#include <pthread.h>
#include <time.h>
#include "log.h"
#include "queue.h"

#define THREAD_POOL_SIZE 7
#define BUFFER_LENGTH 4096

int make_socket(uint16_t);
void handle_socket(int);
