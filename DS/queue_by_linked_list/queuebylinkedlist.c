#include <stdlib.h>

#include "queue.h"
#include "doublelinkedlist.h"

Queue* QueueCreate (size_t _capacity)
{
	return (Queue*) ListCreate (NULL);
}

void QueueDestroy(Queue *_queue)
{
	return ListDestroy ((Queue*) _queue);
}

ADTErr QueueInsert(Queue *_queue,int  _item)
{
	return ListPushTail ((Queue*) _queue, _item);;
}

ADTErr QueueRemove(Queue *_queue,int* _item)
{
	return ListPopHead (List* _list, int *_data);
}

int IsQueueEmpty(Queue *_queue)
{
	return ListCountItems ((Queue*) _queue);
}

void QueuePrint(Queue *_queue)
{
	ListPrint ((Queue*) _queue, 1); 
}
