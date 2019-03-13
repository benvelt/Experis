#include <stdlib.h>
#include <stdio.h>

#include "mu_test.h"
#include "generic_vector.h"

#define INITIAL_CAPACITY 20
#define SMALLER_INITIAL_CAPACITY 10
#define BLOCK_SIZE 20
#define LENGTH_1 20
#define LENGTH_2 10

/*
UNIT TESTS
*/

/*~~~~~~~~~~~~~~ vector_create ~~~~~~~~~~~~~~*/
UNIT(vector_create)
	Vector* vector = NULL;
	
	ASSERT_THAT(!vector);
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	ASSERT_THAT(vector);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_create_init_and_block_zero ~~~~~~~~~~~~~~*/
UNIT(vector_create_init_and_block_zero)
	Vector* vector = NULL;
	
	vector = Vector_Create(0, 0);
	ASSERT_THAT(!vector);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_create_init_is_zero ~~~~~~~~~~~~~~*/
UNIT(vector_create_init_is_zero)
	Vector* vector = NULL;
	
	vector = Vector_Create(0, BLOCK_SIZE);
	ASSERT_THAT(vector);
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_destroy ~~~~~~~~~~~~~~*/
UNIT(vector_destroy)
	Vector* vector = NULL;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	Vector_Destroy(&vector, NULL);
	ASSERT_THAT(!vector);
END_UNIT

/*~~~~~~~~~~~~~~ vector_destroy_uninitialized ~~~~~~~~~~~~~~*/
UNIT(vector_destroy_uninitialized)
	Vector* vector = NULL;
	
	Vector_Destroy(&vector, NULL);
	ASSERT_THAT(!vector);
END_UNIT

/*~~~~~~~~~~~~~~ vector_append ~~~~~~~~~~~~~~*/
UNIT(vector_append)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_1] = {0};
	int* itemPtr[LENGTH_1] = {0};
	int i = 0;
	
	for(i = 0; i < LENGTH_1; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
	}
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);

	for(i = 0; i < LENGTH_1; ++i)
	{
		vecErr = Vector_Append(vector, (void*)itemPtr[i]);
		ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	}
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_append_overflow ~~~~~~~~~~~~~~*/
UNIT(vector_append_overflow)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_1] = {0};
	int* itemPtr[LENGTH_1] = {0};
	int i = 0;
	
	for(i = 0; i < LENGTH_1; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
	}
	
	vector = Vector_Create(SMALLER_INITIAL_CAPACITY, 0);
	
	for(i = 0; i < SMALLER_INITIAL_CAPACITY; ++i)
	{
		vecErr = Vector_Append(vector, (void*)itemPtr[i]);
		ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	}
	
	vecErr = Vector_Append(vector, (void*)itemPtr[i]);
	ASSERT_THAT(VECTOR_OVERFLOW_ERROR == vecErr);

	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_append_uninitialized ~~~~~~~~~~~~~~*/
UNIT(vector_append_uninitialized)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item = 1;
	int* itemPtr = NULL;
	
	itemPtr = &item;
	
	vecErr = Vector_Append(vector, (void*)itemPtr);
	ASSERT_THAT(VECTOR_UNINITIALIZED_ERROR == vecErr);
END_UNIT

/*~~~~~~~~~~~~~~ vector_append_realloc ~~~~~~~~~~~~~~*/
UNIT(vector_append_realloc)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_1] = {0};
	int* itemPtr[LENGTH_1] = {0};
	int i = 0;
	
	for(i = 0; i < LENGTH_1; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
	}
	
	vector = Vector_Create(SMALLER_INITIAL_CAPACITY, BLOCK_SIZE);

	for(i = 0; i < SMALLER_INITIAL_CAPACITY; ++i)
	{
		vecErr = Vector_Append(vector, (void*)itemPtr[i]);
		ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	}
	
	for(i = i; i < SMALLER_INITIAL_CAPACITY; ++i)
	{
		vecErr = Vector_Append(vector, (void*)itemPtr[i]);
		ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	}
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_append_init_is_zero ~~~~~~~~~~~~~~*/
UNIT(vector_append_init_is_zero)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_1] = {0};
	int* itemPtr[LENGTH_1] = {0};
	int i = 0;
	
	for(i = 0; i < LENGTH_1; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
	}
	
	vector = Vector_Create(0, BLOCK_SIZE);

	for(i = 0; i < SMALLER_INITIAL_CAPACITY; ++i)
	{
		vecErr = Vector_Append(vector, (void*)itemPtr[i]);
		ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	}
	
	for(i = i; i < SMALLER_INITIAL_CAPACITY; ++i)
	{
		vecErr = Vector_Append(vector, (void*)itemPtr[i]);
		ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	}
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_remove ~~~~~~~~~~~~~~*/
UNIT(vector_remove)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int i = 0;
	int j = 2;
	int* iPtr = NULL;
	int* jPtr = NULL;
	int* pValue = 0;
	
	iPtr = &i;
	jPtr = &j;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	Vector_Append(vector, (void*)iPtr);
	Vector_Append(vector, (void*)jPtr);
	
	vecErr = Vector_Remove(vector, (void**)&pValue);
	ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	ASSERT_THAT(jPtr == pValue);
	ASSERT_THAT(j == *pValue);
	
	vecErr = Vector_Remove(vector, (void**)&pValue);
	ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	ASSERT_THAT(iPtr == pValue);
	ASSERT_THAT(i == *pValue);
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_remove_uninitialized ~~~~~~~~~~~~~~*/
UNIT(vector_remove_uninitialized)
	Vector* vector = NULL;
	Vector_Result vecErr = 0; 
	int* pValue = 0;
	
	vecErr = Vector_Remove(vector, (void**)&pValue);
	ASSERT_THAT(VECTOR_UNINITIALIZED_ERROR == vecErr);
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_remove_underflow ~~~~~~~~~~~~~~*/
UNIT(vector_remove_underflow)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int i = 0;
	int j = 2;
	int* iPtr = NULL;
	int* jPtr = NULL;
	int* pValue = 0;
	
	iPtr = &i;
	jPtr = &j;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	Vector_Append(vector, (void*)iPtr);
	Vector_Append(vector, (void*)jPtr);
	
	vecErr = Vector_Remove(vector, (void**)&pValue);
	ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	ASSERT_THAT(jPtr == pValue);
	ASSERT_THAT(j == *pValue);
	
	vecErr = Vector_Remove(vector, (void**)&pValue);
	ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	ASSERT_THAT(iPtr == pValue);
	ASSERT_THAT(i == *pValue);
	
	vecErr = Vector_Remove(vector, (void**)&pValue);
	ASSERT_THAT(VECTOR_UNDERFLOW_ERROR == vecErr);
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_get ~~~~~~~~~~~~~~*/

UNIT(vector_get)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_2] = {0};
	int* itemPtr[LENGTH_2] = {0};
	int* pValue = NULL;
	int i = 0;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	for(i=0; i < LENGTH_2; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	for(i = 1; i <= LENGTH_2; ++i)
	{
		vecErr = Vector_Get(vector, i, (void**)&pValue);
		ASSERT_THAT(VECTOR_SUCCESS == vecErr);
		ASSERT_THAT(itemPtr[i - 1] == pValue);
		ASSERT_THAT(item[i - 1] == *pValue);
	}
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_get_uninitialized ~~~~~~~~~~~~~~*/
UNIT(vector_get_uninitialized)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int* pValue = NULL;
	
	vecErr = Vector_Get(vector, 1, (void**)&pValue);
	ASSERT_THAT(VECTOR_UNINITIALIZED_ERROR == vecErr);
	ASSERT_THAT(!pValue);
	
END_UNIT

/*~~~~~~~~~~~~~~ vector_get_bad_index ~~~~~~~~~~~~~~*/
UNIT(vector_get_bad_index)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_2] = {0};
	int* itemPtr[LENGTH_2] = {0};
	int* pValue = NULL;
	int i = 0;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	for(i=0; i < LENGTH_2; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	vecErr = Vector_Get(vector, 0, (void**)&pValue);
	ASSERT_THAT(VECTOR_INDEX_OUT_OF_BOUNDS_ERROR == vecErr);
	ASSERT_THAT(!pValue);
	
	vecErr = Vector_Get(vector, i + 1, (void**)&pValue);
	ASSERT_THAT(VECTOR_INDEX_OUT_OF_BOUNDS_ERROR == vecErr);
	ASSERT_THAT(!pValue);
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_set ~~~~~~~~~~~~~~*/
UNIT(vector_set)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_2] = {0};
	int* itemPtr[LENGTH_2] = {0};
	int* pValue = NULL;
	int* value = NULL;
	int val = 15;
	int i = 0;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	value = &val;
	
	for(i=0; i < LENGTH_2; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	Vector_Get(vector, 1, (void**)&pValue);
	ASSERT_THAT(itemPtr[0] == pValue);
	ASSERT_THAT(item[0] == *pValue);
	ASSERT_THAT(value != pValue);
	
	vecErr = Vector_Set(vector, 1, (void*) value);
	ASSERT_THAT(VECTOR_SUCCESS == vecErr);
	Vector_Get(vector, 1, (void**)&pValue);
	ASSERT_THAT(itemPtr[0] != pValue);
	ASSERT_THAT(item[0] != *pValue);
	ASSERT_THAT(value == pValue);
	ASSERT_THAT(val == *pValue);
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_set_uninitialized ~~~~~~~~~~~~~~*/
UNIT(vector_set_uninitialized)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int* value = NULL;
	int val = 15;
	
	value = &val;
	
	vecErr = Vector_Set(vector, 1, (void*)value);
	ASSERT_THAT(VECTOR_UNINITIALIZED_ERROR == vecErr);
END_UNIT

/*~~~~~~~~~~~~~~ vector_set_bad_index ~~~~~~~~~~~~~~*/
UNIT(vector_set_bad_index)
	Vector* vector = NULL;
	Vector_Result vecErr = 0;
	int item[LENGTH_2] = {0};
	int* itemPtr[LENGTH_2] = {0};
	int* value = NULL;
	int val = 15;
	int i = 0;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	value = &val;
	
	for(i=0; i < LENGTH_2; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	vecErr = Vector_Set(vector, 0, (void*)value);
	ASSERT_THAT(VECTOR_INDEX_OUT_OF_BOUNDS_ERROR == vecErr);
	
	vecErr = Vector_Set(vector, i + 1, (void*)value);
	ASSERT_THAT(VECTOR_INDEX_OUT_OF_BOUNDS_ERROR == vecErr);
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_size ~~~~~~~~~~~~~~*/
UNIT(vector_size)
	Vector* vector = NULL;
	int item[LENGTH_2] = {0};
	int* itemPtr[LENGTH_2] = {0};
	int* pValue = NULL;
	int i = 0;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	for(i=0; i < LENGTH_2; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	ASSERT_THAT(LENGTH_2 == Vector_Size(vector));
	
	item[i] = i;
	itemPtr[i] = &item[i];
	Vector_Append(vector, (void*)itemPtr[i]);
	
	ASSERT_THAT(LENGTH_2 + 1 == Vector_Size(vector));
	
	Vector_Remove(vector, (void**)&pValue);
	
	ASSERT_THAT(LENGTH_2 == Vector_Size(vector));
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_capacity ~~~~~~~~~~~~~~*/
UNIT(vector_capacity)
	Vector* vector = NULL;
	int item[LENGTH_2] = {0};
	int* itemPtr[LENGTH_2] = {0};
	int i = 0;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	for(i=0; i < LENGTH_2; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	ASSERT_THAT(LENGTH_2 == Vector_Size(vector));
	
	item[i] = i;
	itemPtr[i] = &item[i];
	Vector_Append(vector, (void*)itemPtr[i]);
	
	ASSERT_THAT(INITIAL_CAPACITY == Vector_Capacity(vector));
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_capacity_and_extend ~~~~~~~~~~~~~~*/
UNIT(vector_capacity_and_extend)
	Vector* vector = NULL;
	int item[LENGTH_2] = {0};
	int* itemPtr[LENGTH_2] = {0};
	int i = 0;
	
	vector = Vector_Create(SMALLER_INITIAL_CAPACITY, BLOCK_SIZE);
	
	for(i=0; i < LENGTH_2; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	ASSERT_THAT(SMALLER_INITIAL_CAPACITY == Vector_Size(vector));
	
	item[i] = i;
	itemPtr[i] = &item[i];
	Vector_Append(vector, (void*)itemPtr[i]);
	
	ASSERT_THAT(SMALLER_INITIAL_CAPACITY + BLOCK_SIZE == Vector_Capacity(vector));
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_capacity_remove_beyond_init_cap ~~~~~~~~~~~~~~*/
UNIT(vector_capacity_remove_beyond_init_cap)
	Vector* vector = NULL;
	int item[LENGTH_1] = {0};
	int* itemPtr[LENGTH_1] = {0};
	int* pValue = NULL;
	int i = 0;
	
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	for(i=0; i < LENGTH_1; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		Vector_Append(vector, (void*)itemPtr[i]);
	}
	
	ASSERT_THAT(INITIAL_CAPACITY == Vector_Capacity(vector));
	
	for(i = 0; i < LENGTH_1; ++i)
	{
		Vector_Remove(vector, (void**)&pValue);
	}
	ASSERT_THAT(!Vector_Size(vector));
	ASSERT_THAT(INITIAL_CAPACITY == Vector_Capacity(vector));
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ vector_for_each_addition ~~~~~~~~~~~~~~*/
static int Addition(int* _element, size_t _index, int _context)
{
	if(!_element)
	{
		return 0;
	}
	
	*_element += _context;
	
	return 1;
}

UNIT(vector_for_each_addition)
	Vector* vector = NULL;
	int item[LENGTH_1] = {0};
	int i = 0;
	size_t counter = 0;
	
	vector = Vector_Create(INITIAL_CAPACITY, BLOCK_SIZE);
	
	for(i=0; i < LENGTH_1; ++i)
	{
		item[i] = i;
		Vector_Append(vector, (void*)&item[i]);
	}
	
	counter = Vector_ForEach(vector, (VectorElementAction)Addition, (void*)1);
	
	ASSERT_THAT(LENGTH_1== counter);
	
	for(i=0; i < LENGTH_1; ++i)
	{
		ASSERT_THAT(item[i] == i + 1);
	}
	
	counter = Vector_ForEach(vector, (VectorElementAction)Addition, (void*)5);
	
	ASSERT_THAT(LENGTH_1== counter);
	
	for(i=0; i < LENGTH_1; ++i)
	{
		ASSERT_THAT(item[i] == i + 6);
	}
	
	Vector_Destroy(&vector, NULL);
END_UNIT

/*
TEST SUITE
*/

TEST_SUITE(generic vector container)
	TEST(vector_create)
	TEST(vector_create_init_and_block_zero)
	TEST(vector_create_init_is_zero)
	
	TEST(vector_destroy)
	TEST(vector_destroy_uninitialized)
	
	TEST(vector_append)
	TEST(vector_append_overflow)
	TEST(vector_append_uninitialized)
	TEST(vector_append_realloc)
	TEST(vector_append_init_is_zero)
	
	TEST(vector_remove)
	TEST(vector_remove_uninitialized)
	TEST(vector_remove_underflow)
	
	TEST(vector_get)
	TEST(vector_get_uninitialized)
	TEST(vector_get_bad_index)
	
	TEST(vector_set)
	TEST(vector_set_uninitialized)
	TEST(vector_set_bad_index)
	
	TEST(vector_size)
	
	TEST(vector_capacity)
	TEST(vector_capacity_and_extend)
	TEST(vector_capacity_remove_beyond_init_cap)
	
	TEST(vector_for_each_addition)
END_SUITE

