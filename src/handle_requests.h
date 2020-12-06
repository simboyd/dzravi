#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"
#include "log.h"

#define BUFFER_LENGTH 8192

typedef struct http_request_t
{
	char verb[64];
	char uri[2048];
	char protocol[16];
	char host[1024];
} http_request_t;

void handle_connection(int);
http_request_t parse_request(uint8_t[]);
uint8_t* get_response(http_request_t*);

void get_protocol(char*, char*);
void get_host(char*, char*);
uint8_t* get_file(char*, int*);
