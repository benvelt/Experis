/**************************************************************************************************
    Author :				Ben Velt
    Creation date :     13.6.18
    Date last modified :
    Description : 
**************************************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>			/* size_t */
#include "ADTDefs.h"		/* ADTErr */

typedef struct Queue Queue;

/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
Queue* QueueCreate (size_t _capacity);
	
/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
void QueueDestroy(Queue *_queue);

/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
ADTErr QueueInsert(Queue *_queue,int  _item);

/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
ADTErr QueueRemove(Queue *_queue,int* _item);

/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
int QueueIsEmpty(Queue *_queue);


/*  Unit-Test functions  */

/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
void QueuePrint(Queue *_queue);


#endif
