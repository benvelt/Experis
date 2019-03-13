#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "heap.h"

#define VEC_INIT_SIZE		20
#define VEC_EXTD_SIZE		0
#define ARRAY_LENGTH		14

typedef int Item;
const static int array[ARRAY_LENGTH] = {14,8,13,11,6,15,9,5,25,12,17,36,19,100};
const static int revArray[ARRAY_LENGTH] = {100,19,36,17,12,25,5,9,15,6,11,13,8,14};

/*~~~~~~~~~~~~~~~~~~~~~ UNIT TESTS ~~~~~~~~~~~~~~~~~~~~~*/
UNIT(heap_build)
	int i = 0;
	Heap* heap = NULL;
	Vector* vector = NULL;
	
	vector = VectorCreate(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	for(i = 0; i < ARRAY_LENGTH; ++i)
		VectorAdd(vector, array[i]);
		
	heap = HeapBuild(vector);
	ASSERT_THAT(heap);
	
	VectorDestroy(vector);
	HeapDestroy(heap);
END_UNIT

UNIT(heap_destroy)
	Vector* vector = NULL;
	Heap* heap = NULL;
	
	vector = VectorCreate(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	heap = HeapBuild(vector);
	HeapDestroy(heap);
	heap = NULL;
	HeapDestroy(heap);
	ASSERT_THAT(!heap);

	VectorDestroy(vector);
END_UNIT

UNIT(heap_insert)
	int i = 0;
	ADTErr err = 0;
	Vector* vector = NULL;
	Heap* heap = NULL;
	
	vector = VectorCreate(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
		VectorAdd(vector, array[i]);
	
	heap = HeapBuild(vector);
	
	err = HeapInsert(heap, 1);
	ASSERT_THAT(ERR_OK == err);
	
	err = HeapInsert(heap, 112);
	ASSERT_THAT(ERR_OK == err);
	
	err = HeapInsert(heap, 1122);
	ASSERT_THAT(ERR_OK == err);
	
	HeapDestroy(heap);
	VectorDestroy(vector);
END_UNIT

UNIT(heap_max)
	Vector* vector = NULL;
	Heap* heap = NULL;
	int i = 0;
	int data = 0;
	ADTErr err = 0;
	
	vector = VectorCreate(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	for(i = 0; i < ARRAY_LENGTH; ++i)
		VectorAdd(vector, array[i]);
	heap = HeapBuild(vector);
	
	err = HeapMax(heap, &data);
	ASSERT_THAT(ERR_OK == err);
	ASSERT_THAT(100 == data);
	
	err = HeapInsert(heap, 500);
	ASSERT_THAT(ERR_OK == err);
	
	err = HeapMax(heap, &data);
	ASSERT_THAT(ERR_OK == err);
	ASSERT_THAT(500 == data);
	
	HeapDestroy(heap);
	VectorDestroy(vector);
END_UNIT

UNIT(heap_extract_max)
	Vector* vector = NULL;
	Heap* heap = NULL;
	ADTErr err;
	int i = 0;
	int data = 0;
	
	vector = VectorCreate(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
		VectorAdd(vector, array[i]);
	heap = HeapBuild(vector);
	
	err = HeapExtractMax(heap, &data);
	ASSERT_THAT(ERR_OK == err);
	ASSERT_THAT(100 == data);
	
	HeapInsert(heap, 500);
	err = HeapExtractMax(heap, &data);
	ASSERT_THAT(ERR_OK == err);
	ASSERT_THAT(500 == data);
	
		HeapInsert(heap, 5000);
	err = HeapExtractMax(heap, &data);
	ASSERT_THAT(ERR_OK == err);
	ASSERT_THAT(5000 == data);
	
	HeapDestroy(heap);
	VectorDestroy(vector);
END_UNIT

UNIT(heap_items_number)
	Vector* vector = NULL;
	Heap* heap = NULL;
	int i = 0;
	int length = 0;
	
	vector = VectorCreate(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	VectorAdd(vector, array[i]);
	heap = HeapBuild(vector);
	
	length = HeapItemsNum(heap);
	ASSERT_THAT(ARRAY_LENGTH == length);
END_UNIT

/*~~~~~~~~~~~~~~~~~~~~~ SUITE TESTS ~~~~~~~~~~~~~~~~~~~~~*/
TEST_SUITE(heap container)
	TEST(heap_build)
	TEST(heap_destroy)
	TEST(heap_insert)
	TEST(heap_max)
	TEST(heap_extract_max)
	TEST(heap_items_number)

END_SUITE




