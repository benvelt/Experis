#include <stdlib.h> /* malloc(), */
#include <stdio.h>

#include "queue.h"

#define MAGIC 0xBEEFBEEF


struct Queue
{
	size_t	m_magic;					/* indicator of if free		*/
	int*		m_items;  					/* vector of integers		*/
	size_t	m_capacity;				/* capacity						*/
	size_t	m_noe;						/* num of elem				*/
	size_t	m_head;					/* index of head				*/
	size_t	m_tail;						/* index of tail				*/
};


Queue* QueueCreate (size_t _capacity) 
{
	Queue* queue;
	
	if(!_capacity)
	{
		return NULL;
	}
	
	queue = malloc(sizeof(Queue));
	if(!queue)
	{
		return NULL;
	}
	
	queue->m_magic = MAGIC;
	
	queue->m_items= malloc(_capacity * sizeof(int));
	if(!queue->m_items)
	{
		return NULL;
	}
	
	queue->m_capacity = _capacity;
	queue->m_noe = 0;
	queue->m_head = 0;
	queue->m_tail = 0;
	
	return queue;
}


void QueueDestroy(Queue* _queue) 
{
	if(_queue && _queue->m_magic == MAGIC)
	{
		_queue->m_magic = -1;
		free(_queue->m_items);
		free(_queue);
	}
	return;
}


ADTErr QueueInsert(Queue* _queue, int _item)
{
	if(!_queue || MAGIC != _queue->m_magic)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_queue->m_head == _queue->m_tail && _queue->m_noe != 0)
	{
		return ERR_OVERFLOW;
	}
	
	_queue->m_items[_queue->m_tail] = _item;
	_queue->m_tail = (_queue->m_tail + 1) % _queue->m_capacity;
	_queue->m_noe += 1;
	
	return ERR_OK;
}


ADTErr QueueRemove(Queue *_queue, int* _item)
{
	if(!_queue || QUEUE_MAGIC != _queue->m_magic)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_queue->m_head == _queue->m_tail && _queue->m_noe == 0)
	{
		return ERR_UNDERFLOW;
	}
	
	*_item = _queue->m_items[_queue->m_head];
	_queue->m_head = (_queue->m_head + 1) % _queue->m_capacity;
	_queue->m_noe -= 1;
	
	return ERR_OK;
}

int QueueIsEmpty(Queue *_queue)
{
	if(NULL == _queue || QUEUE_MAGIC == _queue->m_magic)
	{
		return -1;
	}

	return 0 == _queue->m_nitems; 

}

void QueuePrint(Queue *_queue) {
	int i = 0;
	
	if(!(_queue && _queue->m_magic == MAGIC))
	{
		printf("\nNOT INITIALIZED\n");
	}
	for (i = 0; i < (_queue -> m_capacity); ++i) 
	{
		printf ("%d ", _queue -> m_items[i]);
	}
	printf("\n");
}










