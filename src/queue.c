#include "queue.h"

void enqueue(queue_t** head, int newdata)
{
	queue_t* newnode = malloc(sizeof(queue_t));
	newnode->next = NULL;
	newnode->data = newdata;
	
	if(*head == NULL)
	{
		*head = newnode;
		return;
	}
	
	queue_t* tmp = *head;
	while(tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = newnode;

}

int dequeue(queue_t** head)
{
	if(*head == NULL)
		return -1;

	int res = (*head)->data;
	queue_t* tmp = *head;
	*head = (*head)->next;
	free(tmp);

	return res;
}

