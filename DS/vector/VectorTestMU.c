#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "vector.h"

typedef int Item;


UNIT(vector_create)
	Item item = 0;
	Vector* vector = VectorCreate(20,4);
	ASSERT_THAT(vector);
	ASSERT_THAT(ERR_OK == VectorAdd(vector, item));
	VectorDestroy (vector);
END_UNIT

UNIT(vector_destroy)
	Item item = 1;
	Vector* vector = VectorCreate(20,4);
	VectorDestroy (vector);
	vector = NULL;
	VectorDestroy (vector);
	ASSERT_THAT(ERR_NOT_INITIALIZED == VectorAdd(vector, item));	
END_UNIT

UNIT(vector_add)
	int i;
	Vector* vector = VectorCreate(4,2);
	for (i=0; i<5; i++)
	{
		VectorAdd(vector, i);
	}
	ASSERT_THAT(ERR_OK == VectorAdd(vector, i));
	VectorDestroy (vector);
END_UNIT

UNIT(vector_add_overflow)
	int i;
	Vector* vector = VectorCreate(4,0);
	for (i=0; i<4; i++)
	{
		VectorAdd(vector, i);
	}
	ASSERT_THAT(ERR_OVERFLOW == VectorAdd(vector, i));
	VectorDestroy (vector);
END_UNIT

UNIT(vector_add_uninitialized)
	Item item = 1;
	Vector* vector = VectorCreate(4,2);
	VectorDestroy(vector);
	vector = 0;
	ASSERT_THAT(ERR_NOT_INITIALIZED == VectorAdd(vector, item));
END_UNIT

UNIT(vector_delete)
	int i;
	Item item;
	Vector* vector = VectorCreate(4,2);
	for (i=0; i<=4; i++)
	{
		VectorAdd(vector, i);
	}
	ASSERT_THAT(ERR_OK == VectorDelete(vector, &item));
	ASSERT_THAT((i-1) == item);
	VectorDestroy (vector);
END_UNIT

UNIT(vector_delete_uninitialized)
	Item item = 5;
	Vector* vector = VectorCreate(4,2);
	VectorDestroy (vector);
	vector = NULL;
	ASSERT_THAT(ERR_NOT_INITIALIZED == VectorDelete(vector, &item));
END_UNIT

UNIT(vector_delete_underflow)
	Item item;
	Vector* vector = VectorCreate(4,2);
	ASSERT_THAT(ERR_UNDERFLOW == VectorDelete(vector, &item));
	VectorDestroy(vector);
END_UNIT

UNIT(vector_get)
	int i;
	Item item;
	int array[10] = {4,6,2,5,8,6,0,3,7,9};
	Vector* vector = VectorCreate(10,2);
	for (i=0; i<10; i++)
	{
		VectorAdd(vector, array[i]);
	}
	for (i=0; i<10; i++)
	{
		VectorGet(vector, i+1, &item);
		ASSERT_THAT(array[i] == item);
	}
	VectorDestroy(vector);
END_UNIT

UNIT(vector_get_uninitialized)
	Item item;
	Vector* vector = VectorCreate(4,2);
	VectorDestroy(vector);
	vector = NULL;
	ASSERT_THAT(ERR_NOT_INITIALIZED == VectorGet(vector, 2, &item));
END_UNIT

UNIT(vector_get_bad_index)
	int i;
	int item;
	int array[10] = {4,6,2,5,8,6,0,3,7,9};
	Vector* vector = VectorCreate(10,2);
	for (i=0; i<10; i++)
	{
		VectorAdd(vector, array[i]);
	}
	ASSERT_THAT(ERR_WRONG_INDEX == VectorGet(vector, 12, &item));
	ASSERT_THAT(ERR_WRONG_INDEX == VectorGet(vector, 0, &item));
	VectorDestroy(vector);
END_UNIT

UNIT(vector_set)
	int i;
	Item item;
	int array[10] = {4,6,2,5,8,6,0,3,7,9};
	Vector* vector = VectorCreate(10,2);
	for (i=0; i<10; i++)
	{
		VectorAdd(vector, array[i]);
	}
	VectorSet(vector, 4, array[1]);
	VectorGet(vector, 4, &item);
	ASSERT_THAT(6 == item);
	VectorDestroy(vector);
END_UNIT

UNIT(vector_set_uninitialized)
	Item item = 7;
	Vector* vector = VectorCreate(4,2);
	VectorDestroy(vector);
	vector = NULL;
	ASSERT_THAT(ERR_NOT_INITIALIZED == VectorSet(vector, 2, item));
END_UNIT

UNIT(vector_set_bad_index)
	int i;
	int array[10] = {4,6,2,5,8,6,0,3,7,9};
	Vector* vector = VectorCreate(10,2);
	for (i=0; i<10; i++)
	{
		VectorAdd(vector, array[i]);
	}
	ASSERT_THAT(ERR_WRONG_INDEX == VectorSet(vector, 12, array[1]));
	ASSERT_THAT(ERR_WRONG_INDEX == VectorSet(vector, 0,  array[1]));
	VectorDestroy(vector);
END_UNIT


UNIT(vector_size)
	int i;
	Vector* vector = VectorCreate(10,2);
	for (i=0; i<4; i++)
	{
		VectorAdd(vector, i);
	}
	ASSERT_THAT(4 == VectorGetSize(vector));
	VectorDestroy (vector);
END_UNIT


UNIT(vector_isempty)
	Vector* vector = VectorCreate(10,2);
	ASSERT_THAT(0 != VectorIsEmpty(vector));
	VectorDestroy (vector);
END_UNIT



TEST_SUITE(vector container)
	TEST(vector_create)
	TEST(vector_destroy)
	
	TEST(vector_add)
	TEST(vector_add_overflow)
	TEST(vector_add_uninitialized)

	TEST(vector_delete)
	TEST(vector_delete_uninitialized)
	TEST(vector_delete_underflow)

	TEST(vector_size)

	TEST(vector_get)
	TEST(vector_get_uninitialized)
	TEST(vector_get_bad_index)

	TEST(vector_set)
	TEST(vector_set_uninitialized)
	TEST(vector_set_bad_index)

END_SUITE

