#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "log.h"

#define BUFFER_LENGTH 4096

void handle_connection(int, fd_set*);
