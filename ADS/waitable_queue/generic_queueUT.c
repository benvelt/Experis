#include <stdlib.h>
#include <stdio.h>

#include "mu_test.h"
#include "generic_queue.h"

#define CAPACITY 20

static int AddToElement(int* _element, size_t _index, int* _context);
static int PrintElement(int* _element, size_t _index, void* _context);

/*
UNIT TESTS
*/

/*~~~~~~~~~~~~~~ queue_create ~~~~~~~~~~~~~~*/
UNIT(queue_create)
	Queue* queue = NULL;
	
	ASSERT_THAT(!queue);
	queue = Queue_Create(CAPACITY);
	ASSERT_THAT(queue);
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_create_capacity_zero ~~~~~~~~~~~~~~*/
UNIT(queue_create_capacity_zero)
	Queue* queue = NULL;
	
	ASSERT_THAT(!queue);
	queue = Queue_Create(0);
	ASSERT_THAT(!queue);
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_destroy ~~~~~~~~~~~~~~*/
UNIT(queue_destroy)
	Queue* queue = NULL;
	
	ASSERT_THAT(!queue);
	queue = Queue_Create(CAPACITY);
	
	ASSERT_THAT(queue);
	
	Queue_Destroy(&queue, NULL);
	
	ASSERT_THAT(!queue);
END_UNIT

/*~~~~~~~~~~~~~~ queue_destroy_unintialized ~~~~~~~~~~~~~~*/
UNIT(queue_destroy_unintialized)
	Queue* queue = NULL;
	
	ASSERT_THAT(!queue);
	
	Queue_Destroy(&queue, NULL);
	
	ASSERT_THAT(!queue);
END_UNIT

/*~~~~~~~~~~~~~~ queue_destroy_twice ~~~~~~~~~~~~~~*/
UNIT(queue_destroy_twice)
	Queue* queue = NULL;
	
	ASSERT_THAT(!queue);
	queue = Queue_Create(CAPACITY);
	
	ASSERT_THAT(queue);
	
	Queue_Destroy(&queue, NULL);
	
	ASSERT_THAT(!queue);
END_UNIT

/*~~~~~~~~~~~~~~ queue_enqueue_int_pointer ~~~~~~~~~~~~~~*/
UNIT(queue_enqueue_int_pointer)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	
	queue = Queue_Create(CAPACITY);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_enqueue_overflow_int_pointer ~~~~~~~~~~~~~~*/
UNIT(queue_enqueue_overflow_int_pointer)
	Queue* queue = NULL;
	int array[CAPACITY + 1] = {0};
	int* arrayPtr[CAPACITY + 1] = {NULL};
	int i = 0;
	
	queue = Queue_Create(CAPACITY);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	array[i] = i;
	arrayPtr[i] = &array[i];
	ASSERT_THAT(QUEUE_OVERFLOW == Queue_Enqueue(queue, arrayPtr[i]));
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_enqueue_uninitialized_int_pointer ~~~~~~~~~~~~~~*/
UNIT(queue_enqueue_uninitialized_int_pointer)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_UNINITIALIZED_ERROR == Queue_Enqueue(queue, arrayPtr[i]));
	}
END_UNIT

/*~~~~~~~~~~~~~~ queue_dequeue_int_pointer ~~~~~~~~~~~~~~*/
UNIT(queue_dequeue_int_pointer)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	int* pValue = NULL;
	
	queue = Queue_Create(CAPACITY);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	ASSERT_THAT(!pValue);
	
	ASSERT_THAT(QUEUE_SUCCESS == Queue_Dequeue(queue, (void**)&pValue));
	ASSERT_THAT(arrayPtr[0] == pValue);
	ASSERT_THAT(array[0] == *pValue);
	
	ASSERT_THAT(QUEUE_SUCCESS == Queue_Dequeue(queue, (void**)&pValue));
	ASSERT_THAT(arrayPtr[1] == pValue);
	ASSERT_THAT(array[1] == *pValue);
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_dequeue_uninitialized_int_pointer ~~~~~~~~~~~~~~*/
UNIT(queue_dequeue_uninitialized_int_pointer)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	int* pValue = NULL;
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_UNINITIALIZED_ERROR == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	ASSERT_THAT(!pValue);
	
	ASSERT_THAT(QUEUE_UNINITIALIZED_ERROR == Queue_Dequeue(queue, (void**)&pValue));
	ASSERT_THAT(arrayPtr[0] != pValue);
	ASSERT_THAT(!pValue);
END_UNIT

/*~~~~~~~~~~~~~~ queue_dequeue_underflow_int_pointer ~~~~~~~~~~~~~~*/
UNIT(queue_dequeue_underflow_int_pointer)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	int* pValue = NULL;
	
	queue = Queue_Create(CAPACITY);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	for(i = 0; i < CAPACITY; ++i)
	{
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Dequeue(queue, (void**)&pValue));
		ASSERT_THAT(arrayPtr[i] == pValue);
		ASSERT_THAT(array[i] == *pValue);
	}
	
	ASSERT_THAT(QUEUE_UNDERFLOW == Queue_Dequeue(queue, (void**)&pValue));
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_is_empty ~~~~~~~~~~~~~~*/
UNIT(queue_is_empty)
	Queue* queue = NULL;
	
	queue = Queue_Create(CAPACITY);
	
	ASSERT_THAT(1 == Queue_IsEmpty(queue));
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_is_empty_uninitialized ~~~~~~~~~~~~~~*/
UNIT(queue_is_empty_uninitialized)
	Queue* queue = NULL;
	
	ASSERT_THAT(-1 == Queue_IsEmpty(queue));
END_UNIT

/*~~~~~~~~~~~~~~ queue_is_empty_after_enqueue ~~~~~~~~~~~~~~*/
UNIT(queue_is_empty_after_enqueue)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	
	queue = Queue_Create(CAPACITY);
	
	ASSERT_THAT(1 == Queue_IsEmpty(queue));
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	ASSERT_THAT(0 == Queue_IsEmpty(queue));
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_is_empty_after_enqueue_and_dequeue ~~~~~~~~~~~~~~*/
UNIT(queue_is_empty_after_enqueue_and_dequeue)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	int* pValue = NULL;
	
	queue = Queue_Create(CAPACITY);
	
	ASSERT_THAT(1 == Queue_IsEmpty(queue));
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	ASSERT_THAT(0 == Queue_IsEmpty(queue));
	
	for(i = 0; i < CAPACITY; ++i)
	{
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Dequeue(queue, (void**)&pValue));
	}
	
	ASSERT_THAT(1 == Queue_IsEmpty(queue));
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_for_each_print ~~~~~~~~~~~~~~*/
UNIT(queue_for_each_print)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	size_t counter = 0;
	
	queue = Queue_Create(CAPACITY);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	counter = Queue_ForEach(queue, (QueueElementAction) PrintElement, NULL);
	printf("\n");
	ASSERT_THAT(CAPACITY == counter);
	
	Queue_Destroy(&queue, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ queue_for_each_add_5 ~~~~~~~~~~~~~~*/
UNIT(queue_for_each_add_5)
	Queue* queue = NULL;
	int array[CAPACITY] = {0};
	int* arrayPtr[CAPACITY] = {NULL};
	int i = 0;
	size_t counter = 0;
	int context = 5;
	int* contextPtr = NULL;
	
	contextPtr = &context;
	
	queue = Queue_Create(CAPACITY);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		array[i] = i;
		arrayPtr[i] = &array[i];
		ASSERT_THAT(QUEUE_SUCCESS == Queue_Enqueue(queue, arrayPtr[i]));
	}
	
	counter = Queue_ForEach(queue, (QueueElementAction) AddToElement, (void*)contextPtr);
	ASSERT_THAT(CAPACITY == counter);
	
	for(i = 0; i < CAPACITY; ++i)
	{
		ASSERT_THAT(array[i] == i + context);
	}
	
	Queue_Destroy(&queue, NULL);
END_UNIT
/*
TEST SUITE
*/

TEST_SUITE(generic queue container)
	TEST(queue_create)
	TEST(queue_create_capacity_zero)
	
	TEST(queue_destroy)
	TEST(queue_destroy_unintialized)
	TEST(queue_destroy_twice)
	
	TEST(queue_enqueue_int_pointer)
	TEST(queue_enqueue_overflow_int_pointer)
	TEST(queue_enqueue_uninitialized_int_pointer)
	
	TEST(queue_dequeue_int_pointer)
	TEST(queue_dequeue_uninitialized_int_pointer)
	TEST(queue_dequeue_underflow_int_pointer)
	
	TEST(queue_is_empty)
	TEST(queue_is_empty_uninitialized)
	TEST(queue_is_empty_after_enqueue)
	TEST(queue_is_empty_after_enqueue_and_dequeue)
	
	TEST(queue_for_each_print)
	TEST(queue_for_each_add_5)
END_SUITE

/*
print elements in queue from head to tail.
*/
static int PrintElement(int* _element, size_t _index, void* _context)
{
	printf("%d ", *_element);
	
	return 1;
}

/*
print elements in queue from head to tail.
*/
static int AddToElement(int* _element, size_t _index, int* _context)
{
	*_element += *_context;
	
	return 1;
}
