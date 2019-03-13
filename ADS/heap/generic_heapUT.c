/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			26.07.18
 * Date last modified :
 * Description : 			main program to test Generic Heap.
******************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "mu_test.h"
#include "generic_vector.h"
#include "generic_heap.h"

/*
MACROS DEFINITIONS
*/

#define VEC_INIT_SIZE		14
#define VEC_EXTD_SIZE		5
#define ARRAY_LENGTH		14

#define INITIAL_VEC_CAPACITY 2
#define VEC_BLOCK_SIZE 2

/*
VARIABLES DECLARATIONS
*/

static Heap* heap = NULL;
static Vector* vector = NULL;
static int i = 0;
/*
const static int c_array[ARRAY_LENGTH] = {14,8,13,11,6,15,9,5,25,12,17,36,19,100};
const static int revArray[ARRAY_LENGTH] = {100,25,36,11,17,19,14,5,8,6,12,13,15,9};
*/
static int array[ARRAY_LENGTH] = {14,8,13,11,6,15,100,5,25,12,17,36,19,9};
static int* arrayPtr[ARRAY_LENGTH] = {NULL};

/*
FUNCTIONS DECLARATIONS
*/
static int PtrCompare(int* _item1, int* _item2);
static int PrintVector(int* _item);

/*
UNIT TESTS
*/

/*~~~~~~~~~~~~~~ heap_build ~~~~~~~~~~~~~~*/
UNIT(heap_build)
	heap = NULL;
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Vector_Append(vector, (void*)arrayPtr[i]);
	}
	
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	ASSERT_THAT(heap);
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_build_null_vector ~~~~~~~~~~~~~~*/
UNIT(heap_build_null_vector)
	heap = NULL;
	
	heap = Heap_Build(NULL, (HeapItemCompare)PtrCompare);
	ASSERT_THAT(!heap);
END_UNIT

/*~~~~~~~~~~~~~~ heap_build_null_func ~~~~~~~~~~~~~~*/
UNIT(heap_build_null_func)
	heap = NULL;
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	heap = Heap_Build(vector, NULL);
	ASSERT_THAT(!heap);
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_destroy ~~~~~~~~~~~~~~*/
UNIT(heap_destroy)
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	heap = Heap_Build(vector, NULL);
	ASSERT_THAT(!heap);
	
	Vector_Destroy(&vector, NULL);
	Heap_Destroy(&heap);
	ASSERT_THAT(!heap);
END_UNIT

/*~~~~~~~~~~~~~~ heap_destroy_uninitialized ~~~~~~~~~~~~~~*/
UNIT(heap_destroy_uninitialized)
	heap = NULL;
	
	Heap_Destroy(&heap);
	ASSERT_THAT(!heap);
END_UNIT

/*~~~~~~~~~~~~~~ heap_insert_with_non_empty_vector ~~~~~~~~~~~~~~*/
UNIT(heap_insert_with_non_empty_vector)
	int ins = 10;
	int* insP = &ins;
	
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Vector_Append(vector, (void*)arrayPtr[i]);
	}
	
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	ASSERT_THAT(HEAP_SUCCESS == Heap_Insert(heap, (void*)insP));
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_insert_with_empty_vector ~~~~~~~~~~~~~~*/
UNIT(heap_insert_with_empty_vector)
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		ASSERT_THAT(HEAP_SUCCESS == Heap_Insert(heap, (void*)arrayPtr[i]));
	}
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_insert_with_null_heap ~~~~~~~~~~~~~~*/
UNIT(heap_insert_with_null_heap)
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		ASSERT_THAT(HEAP_UNINITIALIZED_ERROR == Heap_Insert(NULL, (void*)arrayPtr[i]));
	}
END_UNIT

/*~~~~~~~~~~~~~~ heap_insert_null_data ~~~~~~~~~~~~~~*/
UNIT(heap_insert_null_data)
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	ASSERT_THAT(HEAP_UNINITIALIZED_ERROR == Heap_Insert(heap, NULL));
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_insert_overflow ~~~~~~~~~~~~~~*/
UNIT(heap_insert_overflow)
	int ins = 10;
	int* insP = &ins;
	
	vector = Vector_Create(VEC_INIT_SIZE, 0);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Vector_Append(vector, (void*)arrayPtr[i]);
	}
	
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	ASSERT_THAT(HEAP_OVERFLOW_ERROR == Heap_Insert(heap, (void*)insP));
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_max ~~~~~~~~~~~~~~*/
UNIT(heap_max)
	int* maxP = NULL;
	vector = Vector_Create(VEC_INIT_SIZE, 0);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Vector_Append(vector, (void*)arrayPtr[i]);
	}
	
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	ASSERT_THAT(HEAP_SUCCESS == Heap_Max(heap, (void**)&maxP));
	ASSERT_THAT(100 == *maxP);
	ASSERT_THAT(HEAP_SUCCESS == Heap_Max(heap, (void**)&maxP));
	ASSERT_THAT(100 == *maxP);
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_max_after_ins_max ~~~~~~~~~~~~~~*/
UNIT(heap_max_after_ins_max)
	int max = 999;
	int* maxP = &max;
	int* tstP = NULL;
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Vector_Append(vector, (void*)arrayPtr[i]);
	}
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	ASSERT_THAT(HEAP_SUCCESS == Heap_Max(heap, (void**)&tstP));
	ASSERT_THAT(100 == *tstP);
	
	Heap_Insert(heap, maxP);
	ASSERT_THAT(HEAP_SUCCESS == Heap_Max(heap, (void**)&tstP));
	ASSERT_THAT(max == *tstP);
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_max_uninitialized ~~~~~~~~~~~~~~*/
UNIT(heap_max_uninitialized)
	int* tstP = NULL;
	
	ASSERT_THAT(HEAP_UNINITIALIZED_ERROR == Heap_Max(NULL, (void**)&tstP));
	ASSERT_THAT(!tstP);
END_UNIT

/*~~~~~~~~~~~~~~ heap_max_null_item ~~~~~~~~~~~~~~*/
UNIT(heap_max_null_item)
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Vector_Append(vector, (void*)arrayPtr[i]);
	}
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	ASSERT_THAT(HEAP_UNINITIALIZED_ERROR == Heap_Max(heap, NULL));
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_max_empty_vector ~~~~~~~~~~~~~~*/
UNIT(heap_max_empty_vector)
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	ASSERT_THAT(HEAP_UNINITIALIZED_ERROR == Heap_Max(heap, NULL));
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_extract_max ~~~~~~~~~~~~~~*/
UNIT(heap_extract_max)
	int* maxP = NULL;
	vector = Vector_Create(VEC_INIT_SIZE, 0);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Vector_Append(vector, (void*)arrayPtr[i]);
	}
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	ASSERT_THAT(HEAP_SUCCESS == Heap_ExtractMax(heap, (void**)&maxP));
	ASSERT_THAT(100 == *maxP);
	
	ASSERT_THAT(HEAP_SUCCESS == Heap_ExtractMax(heap, (void**)&maxP));
		ASSERT_THAT(36 == *maxP);
	ASSERT_THAT(HEAP_SUCCESS == Heap_ExtractMax(heap, (void**)&maxP));
			ASSERT_THAT(25 == *maxP);
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_extract_max_uninitialized ~~~~~~~~~~~~~~*/
UNIT(heap_extract_max_uninitialized)
	int* maxP = NULL;
	
	ASSERT_THAT(HEAP_UNINITIALIZED_ERROR == Heap_ExtractMax(heap, (void**)&maxP));
	ASSERT_THAT(!maxP);
END_UNIT

/*~~~~~~~~~~~~~~ heap_extract_max_empty_vector ~~~~~~~~~~~~~~*/
UNIT(heap_extract_max_empty_vector)
	int* maxP = NULL;
	vector = Vector_Create(VEC_INIT_SIZE, 0);
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	ASSERT_THAT(HEAP_UNDERFLOW_ERROR == Heap_ExtractMax(heap, (void**)&maxP));
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_items_num ~~~~~~~~~~~~~~*/
UNIT(heap_items_num)
	int* maxP = NULL;
	
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	ASSERT_THAT(0 == Heap_ItemsNum(heap));
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Heap_Insert(heap, (void*)arrayPtr[i]);
	}
	
	ASSERT_THAT(ARRAY_LENGTH == Heap_ItemsNum(heap));
	Heap_ExtractMax(heap, (void**)&maxP);
	ASSERT_THAT(ARRAY_LENGTH - 1 == Heap_ItemsNum(heap));
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ heap_items_num_uninitialized ~~~~~~~~~~~~~~*/
UNIT(heap_items_num_uninitialized)
	heap = NULL;
	ASSERT_THAT(-1 == Heap_ItemsNum(heap));
END_UNIT

/*~~~~~~~~~~~~~~ heap_for_each ~~~~~~~~~~~~~~*/
int HeapAdd(int* _data, int _index, int _context)
{
	return *_data = *_data + _context;
}

UNIT(heap_for_each)
	vector = Vector_Create(VEC_INIT_SIZE, VEC_EXTD_SIZE);
	heap = Heap_Build(vector, (HeapItemCompare)PtrCompare);
	
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		arrayPtr[i] = &array[i];
		Heap_Insert(heap, (void*)arrayPtr[i]);
	}
	puts("\nBefore add 5:");
	Vector_ForEach(vector, (VectorElementAction)PrintVector, (void*)5);
	
	ASSERT_THAT(ARRAY_LENGTH == Heap_ForEach(heap, (HeapElementAction)HeapAdd, (void*)5));
	
	puts("\nAfter add 5:");
	Vector_ForEach(vector, (VectorElementAction)PrintVector, (void*)5);
	puts("\n");
	
	Heap_Destroy(&heap);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Vector* CreateSampleVector()
{
	int i;
	static int arr[] = {4,5,6,8,3,1,7};
	static size_t arrSize = sizeof(arr)/sizeof(arr[0]);

	Vector* vec = Vector_Create(4,4);
	for (i=0; i< arrSize; ++i)
	{
		Vector_Append(vec, &arr[i]);
	}

	return vec;

}


int LessComparatorIntFunc(void* _itemA, void* _itemB)
{
	if (*(int*)_itemA<*(int*)_itemB)
	{
		return (*(int*)_itemA - *(int*)_itemB);
	}

	return 0;
}


/*need to add test that do extract max for the entire array (do for 2 arrays) and test that the max everytime is the max we expected */
  
UNIT(Heap__Build)
	Vector* vector = NULL;
	Heap* heap;
	int data=6;

	vector = Vector_Create(INITIAL_VEC_CAPACITY,VEC_BLOCK_SIZE);
    heap = Heap_Build(vector, LessComparatorIntFunc);
    ASSERT_THAT(heap);
    ASSERT_THAT(HEAP_SUCCESS == Heap_Insert(heap, &data));
    Heap_Destroy(&heap);
END_UNIT


UNIT(Heap__Destroy)
	Vector* vector = NULL;
	Heap* heap;
	int data=6;

	vector = Vector_Create(INITIAL_VEC_CAPACITY,VEC_BLOCK_SIZE);
    heap = Heap_Build(vector, LessComparatorIntFunc);
    ASSERT_THAT(heap);
    ASSERT_THAT(HEAP_SUCCESS == Heap_Insert(heap, &data));
    Heap_Destroy(&heap);
    Heap_Destroy(&heap);
    ASSERT_THAT(HEAP_SUCCESS != Heap_Insert(heap, &data));
END_UNIT

UNIT(Heap__Insert)
	Vector* vector = NULL;
	Heap* heap;
	int data=6;
	
	vector = CreateSampleVector();
    heap = Heap_Build(vector, LessComparatorIntFunc);
	ASSERT_THAT(7==Heap_ItemsNum(heap));
    ASSERT_THAT(HEAP_SUCCESS == Heap_Insert(heap, &data));
	ASSERT_THAT(8==Heap_ItemsNum(heap));
    Heap_Destroy(&heap);
END_UNIT


UNIT(Heap__Max)
	Vector* vector = NULL;
	Heap* heap;
	int* pdata;
	
	vector = CreateSampleVector();
    heap = Heap_Build(vector, LessComparatorIntFunc);
	ASSERT_THAT(7==Heap_ItemsNum(heap));
    ASSERT_THAT(HEAP_SUCCESS == Heap_Max(heap, (void**)&pdata));
    ASSERT_THAT(8 == *pdata);
	ASSERT_THAT(7==Heap_ItemsNum(heap));
    Heap_Destroy(&heap);
END_UNIT

UNIT(Heap__ExtractMax)
	Vector* vector = NULL;
	Heap* heap;
	int* pdata;
	
	vector = CreateSampleVector();
    heap = Heap_Build(vector, LessComparatorIntFunc);
	ASSERT_THAT(7==Heap_ItemsNum(heap));
    ASSERT_THAT(HEAP_SUCCESS == Heap_ExtractMax(heap, (void**)&pdata));
    ASSERT_THAT(8 == *pdata);
	ASSERT_THAT(6==Heap_ItemsNum(heap));
    Heap_Destroy(&heap);
END_UNIT

UNIT(Heap__ItemsNum)
	Vector* vector = NULL;
	Heap* heap;
	
	vector = CreateSampleVector();
    heap = Heap_Build(vector, LessComparatorIntFunc);
	ASSERT_THAT(7==Heap_ItemsNum(heap));
    Heap_Destroy(&heap);
END_UNIT




/*
TEST SUITE
*/

TEST_SUITE(generic heap)
	TEST(heap_build)
	TEST(heap_build_null_vector)
	TEST(heap_build_null_func)
	
	TEST(heap_destroy)
	TEST(heap_destroy_uninitialized)
	
	TEST(heap_insert_with_non_empty_vector)
	TEST(heap_insert_with_empty_vector)
	TEST(heap_insert_with_null_heap)
	TEST(heap_insert_null_data)
	TEST(heap_insert_overflow)
	
	TEST(heap_max)
	TEST(heap_max_after_ins_max)
	TEST(heap_max_uninitialized)
	TEST(heap_max_null_item)
	TEST(heap_max_empty_vector)
	
	TEST(heap_extract_max)
	TEST(heap_extract_max_uninitialized)
	TEST(heap_extract_max_empty_vector)
	
	TEST(heap_items_num)
	TEST(heap_items_num_uninitialized)
	
	TEST(heap_for_each)
	
    TEST(Heap__Build)
    TEST(Heap__Destroy)
    TEST(Heap__Insert)
    TEST(Heap__Max)
    TEST(Heap__ExtractMax)
    TEST(Heap__ItemsNum)
END_SUITE

/*~~~~~~~~~~~~~~ function PtrCompare ~~~~~~~~~~~~~~*/
static int PtrCompare(int* _item1, int* _item2)
{
	return *_item1 < *_item2;
}

/*~~~~~~~~~~~~~~ function PrintVector ~~~~~~~~~~~~~~*/

static int PrintVector(int* _item)
{
	printf("%d ",*_item);
	
	return 1;
}
















