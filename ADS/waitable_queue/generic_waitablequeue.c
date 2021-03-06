/* TODO title */

#include <stdlib.h>  /* size_t */
#include <semaphore.h>
#include <pthread.h>

#include "generic_queue.h"

#define MAGIC				0xBEEFBEEE
#define IS_VALID(Q)		((Q) && ((Q))->m_magic == MAGIC)


#define ITEMS(Q)			(((Q))->m_items)
#define CAPACITY(Q)		(((Q))->m_capacity)
#define NOE(Q)				(((Q))->m_noe)
#define HEAD(Q)			(((Q))->m_head)
#define TAIL(Q)				(((Q))->m_tail)

struct Queue
{
	size_t	m_magic;		/* indicator of if free */
	void*	*m_items;		/* vector of integers */
	size_t	m_capacity;		/* capacity */
	size_t	m_noe;			/* num of elem */
	size_t	m_head;			/* index of head */
	size_t	m_tail;			/* index of tail */
	sem_t	m_full;
	sem_t	m_empty;
	pthread_mutex_t m_lock;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Queue_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* TODO first create mutex and only then do allocate */
/* TODO when initiate the queue struct members so maybe there should e lock */
Queue* Queue_Create(size_t _maxSize)
{
	Queue* queue;
	
	if(!_maxSize)
	{
		return NULL;
	}
	
	queue = malloc(sizeof(Queue));
	
	if(!queue)
	{
		return NULL;
	}
	
	if(sem_init(&queue->m_full,0,0) == -1)
	{
		free(queue);
		return NULL;
	}
	if(sem_init(&queue->m_empty,0,_maxSize) == -1)
	{
		free(queue);
		return NULL;
	}
		if(pthread_mutex_init(&queue->m_lock, NULL) != 0)
	{
		free(queue);
		return NULL;
	}
	
	queue->m_items= (void**)malloc(_maxSize * sizeof(void*));
	
	if(!queue->m_items)
	{
		free(queue);
		return NULL;
	}
	
	queue->m_capacity = _maxSize;
	queue->m_noe = 0;
	queue->m_head = 0;
	queue->m_tail = 0;
	
	queue->m_magic = MAGIC;
	
	return queue;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Queue_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Queue_Destroy(Queue** _queue, void (*_elementDestroy)(void* _item))
{
	int i = 0;
	
	if(_queue && *_queue &&(*_queue)->m_magic == MAGIC)
	{
		(*_queue)->m_magic = -1;
		if(_elementDestroy)
		{
			for(i = HEAD(*_queue); i != TAIL(*_queue);  i = (i + 1) % NOE(*_queue))
			{
				_elementDestroy(ITEMS(*_queue)[i]);
			}
		}
		
		pthread_mutex_destroy(&(*_queue)->m_lock);
		sem_destroy(&(*_queue)->m_empty);
		sem_destroy(&(*_queue)->m_full);
		free((*_queue)->m_items);
		free(*_queue);
		*_queue = NULL;
	}
	return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Queue_Enqueue ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Queue_Result Queue_Enqueue(Queue* _queue, void* _item)
{
	if(!IS_VALID(_queue))
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	
	if(!_item)
	{
		return QUEUE_NULL_INPUT;
	}
	
	if(-1 == sem_wait(&_queue->m_empty))
	{
		return QUEUE_SEM_ERROR;
	}
	pthread_mutex_lock(&_queue->m_lock);
	
	ITEMS(_queue)[TAIL(_queue)] = _item;
	TAIL(_queue) = (TAIL(_queue) + 1) % CAPACITY(_queue);
	NOE(_queue) += 1;
	
	pthread_mutex_unlock(&_queue->m_lock);
	
	if(-1 == sem_post(&_queue->m_full))
	{
		return QUEUE_SEM_ERROR;
	}
	
	return QUEUE_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Queue_Dequeue ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Queue_Result Queue_Dequeue(Queue* _queue, void** _pValue)
{
	if(!IS_VALID(_queue))
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	
	if(-1 == sem_wait(&_queue->m_empty))
	{
		return QUEUE_SEM_ERROR;
	}
	pthread_mutex_lock(&_queue->m_lock);
	
	*_pValue = ITEMS(_queue)[HEAD(_queue)];
	HEAD(_queue) = (HEAD(_queue) + 1) % CAPACITY(_queue);
	NOE(_queue) -= 1;
	
	pthread_mutex_unlock(&_queue->m_lock);
	
	if(sem_post(&_queue->m_full) == -1)
	{
		return QUEUE_SEM_ERROR;
	}
	
	return QUEUE_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Queue_IsEmpty ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Queue_IsEmpty(const Queue* _queue)
{
	if(!IS_VALID(_queue))
	{
		return -1;
	}
	
	return 0 == NOE(_queue);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Queue_ForEach ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
size_t Queue_ForEach(const Queue* _queue, QueueElementAction _action, void* _context)
{
	int i = 0;
	int counter = 0;
	int flag = 0;
	
	if(!IS_VALID(_queue) && !_action)
	{
		return 0;
	}
	
	for(i = HEAD(_queue); i != TAIL(_queue) || flag == 0;  i = (i + 1) % NOE(_queue))
	{
		if(!flag)
		{
			flag = 1;
		}
		if(_action(ITEMS(_queue)[i], i, _context) == 0)
		{
			break;
		}
		++counter;
	}
	
	return counter;
}






