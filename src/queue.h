#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct queue_t 
{
	struct queue_t* next;
	int data;
} queue_t;

void enqueue(queue_t**, int);
int dequeue(queue_t**);
