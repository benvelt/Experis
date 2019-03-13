#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mu_test.h"
#include "generic_hashmap.h"
#include "generic_doubleLL_itr.h"
#include "color.h"

/*
MACROS DEFINITIONS
*/
#define CAPACITY 10
#define LENGTH 5

/*
VARIABLE DECLARATIONS
*/
HashMap* hashmap = NULL;
Map_Result mapRes = MAP_SUCCESS;
int keyArr[LENGTH] = {0};
int valArr[LENGTH] = {0};
int* keyArrPtr[LENGTH] = {NULL};
int* valArrPtr[LENGTH] = {NULL};
int i = 0;



/*
USER FUNCTIONS DECLARATIONS
*/
size_t HashFunctionPtr(const int* _key)
{
	size_t newKey = 0;
	
	newKey = *_key;
	
	return newKey;
}

int EqualityFunctionPtr(const int* _ptr1,const int* _ptr2)
{
	return *_ptr1 == *_ptr2;
}

/*
STATIC FUNCTIONS DECLARATIONS
*/


/*
UNIT TESTS
*/

/*~~~~~~~~~~~~~~ hashmap_create ~~~~~~~~~~~~~~*/
UNIT(hashmap_create)
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	 
	ASSERT_THAT(hashmap);
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_create_no_capacity ~~~~~~~~~~~~~~*/
UNIT(hashmap_create_no_capacity)
	hashmap = NULL;
	
	hashmap = HashMap_Create(0,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);

	ASSERT_THAT(!hashmap);
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_create_no_user_functions ~~~~~~~~~~~~~~*/
UNIT(hashmap_create_no_user_functions)
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)NULL, (EqualityFunction)NULL);

	ASSERT_THAT(!hashmap);
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_destroy ~~~~~~~~~~~~~~*/
UNIT(hashmap_destroy)
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);

	ASSERT_THAT(hashmap);
	HashMap_Destroy(&hashmap, NULL, NULL);
	ASSERT_THAT(!hashmap);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_destroy_uninitialized ~~~~~~~~~~~~~~*/
UNIT(hashmap_destroy_uninitialized)
	hashmap = NULL;
	
	HashMap_Destroy(&hashmap, NULL, NULL);
	ASSERT_THAT(!hashmap);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_insert ~~~~~~~~~~~~~~*/
UNIT(hashmap_insert)
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		mapRes = HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
		ASSERT_THAT(MAP_SUCCESS == mapRes);
	}
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_insert_uninitialized ~~~~~~~~~~~~~~*/
UNIT(hashmap_insert_uninitialized)
	hashmap = NULL;
	
	keyArr[0] = LENGTH;
	valArr[0] = LENGTH;
	keyArrPtr[0] = &keyArr[0];
	valArrPtr[0] = &valArr[0];
	
	mapRes = HashMap_Insert(hashmap, keyArrPtr[0], valArrPtr[0]);
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == mapRes);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_insert_null_key ~~~~~~~~~~~~~~*/
UNIT(hashmap_insert_null_key)
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	mapRes = HashMap_Insert(hashmap, NULL, NULL);
	ASSERT_THAT(MAP_KEY_NULL_ERROR == mapRes);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_insert_duplicate_key ~~~~~~~~~~~~~~*/
UNIT(hashmap_insert_duplicate_key)
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		mapRes = HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
		ASSERT_THAT(MAP_KEY_DUPLICATE_ERROR == mapRes);
	}
	
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_remove ~~~~~~~~~~~~~~*/
UNIT(hashmap_remove)
	int* keyPtr = NULL;
	int* valPtr = NULL;
	hashmap = NULL;
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	ASSERT_THAT(!keyPtr && !valPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	mapRes = HashMap_Remove(hashmap, keyArrPtr[LENGTH - 1], (void*)&keyPtr, (void*)&valPtr);
	
	
	ASSERT_THAT(keyPtr && valPtr);
	ASSERT_THAT(MAP_SUCCESS == mapRes);
	ASSERT_THAT(*keyPtr == *keyArrPtr[LENGTH - 1]);
	ASSERT_THAT(keyPtr == keyArrPtr[LENGTH - 1]);
	ASSERT_THAT(*valPtr == *valArrPtr[LENGTH - 1]);
	ASSERT_THAT(valPtr == valArrPtr[LENGTH - 1]);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_remove_uninitialized ~~~~~~~~~~~~~~*/
UNIT(hashmap_remove_uninitialized)
	int* keyPtr = NULL;
	int* valPtr = NULL;
	hashmap = NULL;
	
	mapRes = HashMap_Remove(hashmap, keyArrPtr[LENGTH - 1], (void*)&keyPtr, (void*)&valPtr);
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == mapRes);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_remove_null_key ~~~~~~~~~~~~~~*/
UNIT(hashmap_remove_null_key)
	int* keyPtr = NULL;
	int* valPtr = NULL;
	int* ksPtr = NULL;
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	mapRes = HashMap_Remove(hashmap, ksPtr, (void*)&keyPtr, (void*)&valPtr);
	ASSERT_THAT(!keyPtr && !valPtr);
	ASSERT_THAT(MAP_KEY_NULL_ERROR == mapRes);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_remove_key_not_found ~~~~~~~~~~~~~~*/
UNIT(hashmap_remove_key_not_found)
	int* keyPtr = NULL;
	int* valPtr = NULL;
	int ks = 800;
	int* ksPtr = &ks;
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	mapRes = HashMap_Remove(hashmap, ksPtr, (void*)&keyPtr, (void*)&valPtr);
	ASSERT_THAT(!keyPtr && !valPtr);
	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == mapRes);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_find ~~~~~~~~~~~~~~*/
UNIT(hashmap_find)
	int* valPtr = NULL;
	hashmap = NULL;
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	mapRes = HashMap_Find(hashmap, keyArrPtr[LENGTH - 1], (void**)&valPtr);
	ASSERT_THAT(valPtr);
	ASSERT_THAT(MAP_SUCCESS == mapRes);
	ASSERT_THAT(*valPtr == *valArrPtr[LENGTH - 1]);
	ASSERT_THAT(valPtr == valArrPtr[LENGTH - 1]);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_find_uninitialized ~~~~~~~~~~~~~~*/
UNIT(hashmap_find_uninitialized)
	int* keyPtr = NULL;
	int* valPtr = NULL;
	hashmap = NULL;
	
	mapRes = HashMap_Remove(hashmap, keyArrPtr[LENGTH - 1], (void*)&keyPtr, (void*)&valPtr);
	
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_find_null_key ~~~~~~~~~~~~~~*/
UNIT(hashmap_find_null_key)
	int* valPtr = NULL;
	int* ksPtr = NULL;
	hashmap = NULL;
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	mapRes = HashMap_Find(hashmap, ksPtr, (void**)&valPtr);
	ASSERT_THAT(!valPtr);
	ASSERT_THAT(MAP_KEY_NULL_ERROR == mapRes);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_find_key_not_found ~~~~~~~~~~~~~~*/
UNIT(hashmap_find_key_not_found)
	int* valPtr = NULL;
	int ks = 800;
	int* ksPtr = &ks;
	hashmap = NULL;
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	mapRes = HashMap_Find(hashmap, ksPtr, (void**)&valPtr);
	ASSERT_THAT(MAP_KEY_NOT_FOUND_ERROR == mapRes);
	ASSERT_THAT(!valPtr);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_size ~~~~~~~~~~~~~~*/
UNIT(hashmap_size)
	size_t hashSize = 0;
	hashmap = NULL;
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	hashSize = HashMap_Size(hashmap);
	
	ASSERT_THAT(LENGTH == hashSize);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_size_uninitialized ~~~~~~~~~~~~~~*/
UNIT(hashmap_size_uninitialized)
	size_t hashSize = 0;
	hashmap = NULL;
	
	hashSize = HashMap_Size(hashmap);
	
	ASSERT_THAT(!hashSize);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_size_zero ~~~~~~~~~~~~~~*/
UNIT(hashmap_size_zero)
	size_t hashSize = 0;
	hashmap = NULL;
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	
	hashSize = HashMap_Size(hashmap);
	
	ASSERT_THAT(0 == hashSize);
	
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ hashmap_rehash ~~~~~~~~~~~~~~*/
UNIT(hashmap_rehash)
	int* valPtr = NULL;
	hashmap = NULL;
	
	ASSERT_THAT(!valPtr);
	
	hashmap = HashMap_Create(CAPACITY,(HashFunction)HashFunctionPtr, (EqualityFunction)EqualityFunctionPtr);
	for(i = 0; i < LENGTH; ++i)
	{
		keyArr[i] = i;
		valArr[i] = i * LENGTH;
		keyArrPtr[i] = &keyArr[i];
		valArrPtr[i] = &valArr[i];
		mapRes = HashMap_Insert(hashmap, keyArrPtr[i], valArrPtr[i]);
	}
	
	mapRes = HashMap_Rehash(hashmap, CAPACITY * CAPACITY);
	ASSERT_THAT(MAP_SUCCESS == mapRes);
	
	mapRes = HashMap_Find(hashmap, keyArrPtr[0], (void**)&valPtr);
	ASSERT_THAT(valPtr);
	ASSERT_THAT(MAP_SUCCESS == mapRes);
	ASSERT_THAT(*valPtr == *valArrPtr[0]);
	ASSERT_THAT(valPtr == valArrPtr[0]);
	
	mapRes = HashMap_Find(hashmap, keyArrPtr[1], (void**)&valPtr);
	ASSERT_THAT(valPtr);
	ASSERT_THAT(MAP_SUCCESS == mapRes);
	ASSERT_THAT(*valPtr == *valArrPtr[1]);
	ASSERT_THAT(valPtr == valArrPtr[1]);
	HashMap_Destroy(&hashmap, NULL, NULL);
END_UNIT


/*
GAL TESTS
*/

#define HASH_CAPACITY 10

size_t HashFunc(const void* _key)
{
	return ((size_t)_key);
}


int EqualityFunc(const void* _firstKey, const void* _secondKey)
{
	return ((size_t)_firstKey == (size_t)_secondKey);
}

/********************** hashMap_create **********************/
UNIT(hashMap_create)
	HashMap* hashMap = NULL;
	int item = 10;
	int item2 = 50;
	int* key = &item;
	int* value = &item2;
	puts(BOLDMAGENTA "\n\tGAL TESTS" RESET);
	ASSERT_THAT(value && key);
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(hashMap);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,key,value));
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT

/********************** hashMap_destroy **********************/
UNIT(hashMap_destroy)

	HashMap* hashMap = NULL;
	int* key = NULL;
	int* value = NULL;
	
	key = malloc(sizeof(int));
	value = malloc(sizeof(int));
	*key = 9;
	*value = 21;
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(hashMap);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,key,value));
	HashMap_Destroy(&hashMap,free,free);
	ASSERT_THAT(!hashMap);
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Insert(hashMap,key,value));
END_UNIT

/********************** hashMap_insert_int **********************/
UNIT(hashMap_insert_int)
	HashMap* hashMap = NULL;
	int i;
	int array[]={1,13,4,25,2};
	
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(hashMap);
	for(i=0;i<5;i++)
		ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + i),(array + i)));
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT

/********************** hashMap_insert_char **********************/

UNIT(hashMap_insert_char)
	HashMap* hashMap = NULL;
	int i;
	char string[]="Value";
	int array[]={1,13,4,25,2};
	
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(hashMap);
	for(i=0;i<3;i++)
		ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + i),(string)));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(string + 3),(array + i)));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(string + 4),(string)));
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT

/********************** hashMap_insert_uninitialized **********************/

UNIT(hashMap_insert_uninitialized)

	HashMap* hashMap = NULL;
	char string[]="Value";
	int array[]={1,13,4,25,2};
	
	ASSERT_THAT(MAP_UNINITIALIZED_ERROR == HashMap_Insert(hashMap,(array + 1),(string + 2)));
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(MAP_KEY_NULL_ERROR == HashMap_Insert(hashMap,NULL,(string + 2)));
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 2),NULL));
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT

/********************** hashMap_insert_duplicate **********************/

UNIT(hashMap_insert_duplicate)
	HashMap* hashMap = NULL;
	char string[]="Value";
	int array[]={1,13,4,25,2};
	
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 1),(string +1)));
	ASSERT_THAT(MAP_KEY_DUPLICATE_ERROR == HashMap_Insert(hashMap,(array + 1),(string + 1)));
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT

/********************** hashMap_remove **********************/

UNIT(hashMap_remove)

	HashMap* hashMap = NULL;
	int i;
	int result;
	int* pKey;
	char* pValue;
	char string[]="Value";
	int array[]={1,13,4,25,2};
	
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(hashMap);
	for(i=0;i<5;i++)
		ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + i),(string)));
	result = HashMap_Remove(hashMap,(array + 2),(void**)&pKey,(void**)&pValue);
	ASSERT_THAT(result == MAP_SUCCESS);
	ASSERT_THAT(*pKey == array[2]);
	ASSERT_THAT(strcmp(pValue,string) == 0);
	result = HashMap_Remove(hashMap,(array + 4),(void**)&pKey,(void**)&pValue);
	ASSERT_THAT(result == MAP_SUCCESS);
	ASSERT_THAT(*pKey == array[4]);
	ASSERT_THAT(strcmp(pValue,string) == 0);
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT

/********************** hashMap_remove_uninitialized **********************/

UNIT(hashMap_remove_uninitialized)
	HashMap* hashMap = NULL;
	int result;
	int* pKey;
	char* pValue;
	int array[]={1,13,4,25,2};
	
	result = HashMap_Remove(hashMap,(array + 2),(void**)&pKey,(void**)&pValue);
	ASSERT_THAT(result == MAP_UNINITIALIZED_ERROR);
	
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(hashMap);
	
	result = HashMap_Remove(hashMap,NULL,(void**)&pKey,(void**)&pValue);
	ASSERT_THAT(result == MAP_KEY_NULL_ERROR);
	
	result = HashMap_Remove(hashMap,(array + 3),NULL,(void**)&pValue);
	ASSERT_THAT(result == MAP_KEY_NULL_ERROR);
	
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT

/********************** hashMap_remove_key_not_found **********************/

UNIT(hashMap_remove_key_not_found)

    HashMap* hashMap = NULL;
    int result;
    int* pKey;
    char* pValue;
    char string[]="Value";
    int array[]={1,13,4,25,2};


    hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
    ASSERT_THAT(hashMap);

    ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 2),(string)));
    ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 3),(array + 1)));

    result=HashMap_Remove(hashMap,(array + 1),(void**)&pKey,(void**)&pValue);
    ASSERT_THAT(result == MAP_KEY_NOT_FOUND_ERROR);

    HashMap_Destroy(&hashMap,NULL,NULL);

END_UNIT

/********************** hashMap_remove_key_not_found **********************/

UNIT(hashMap_find)

    HashMap* hashMap = NULL;
    int result;
    char* pValue;
    char string[]="Value";
    int array[]={1,13,4,25,2};

    hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
    ASSERT_THAT(hashMap);

    ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 2),(string)));
    ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 3),(string + 1)));

    result = HashMap_Find(hashMap,(array + 2),(void**)&pValue);
    ASSERT_THAT(result == MAP_SUCCESS);
    ASSERT_THAT(strcmp(pValue,string) == 0);

    result = HashMap_Find(hashMap,(array + 3),(void**)&pValue);
    ASSERT_THAT(result == MAP_SUCCESS);
    ASSERT_THAT(strcmp(pValue,string + 1) == 0);

    HashMap_Destroy(&hashMap,NULL,NULL);

END_UNIT

/********************** hashMap_find_not_found **********************/

UNIT(hashMap_find_not_found)

    HashMap* hashMap = NULL;
    int result;
    char* pValue;
    char string[]="Value";
    int array[]={1,13,4,25,2};


    hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
    ASSERT_THAT(hashMap);

    ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 2),(string)));
    ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + 3),(array + 1)));

    result=HashMap_Find(hashMap,(array + 1),(void**)&pValue);
    ASSERT_THAT(result == MAP_KEY_NOT_FOUND_ERROR);

    HashMap_Destroy(&hashMap,NULL,NULL);

END_UNIT

/********************** hashMap_find_uninitialized **********************/

UNIT(hashMap_find_uninitialized)

    HashMap* hashMap = NULL;
    int result;
    char* pValue;
    int array[]={1,13,4,25,2};

    result=HashMap_Find(hashMap,(array + 1),(void**)&pValue);
    ASSERT_THAT(result == MAP_UNINITIALIZED_ERROR);

    hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
    ASSERT_THAT(hashMap);

    result=HashMap_Find(hashMap,NULL,(void**)&pValue);
    ASSERT_THAT(result == MAP_KEY_NULL_ERROR);



    HashMap_Destroy(&hashMap,NULL,NULL);

END_UNIT

/********************** hashMap_size **********************/
UNIT(hashMap_size)
	HashMap* hashMap = NULL;
	int i;
	int* pKey = NULL;
	char* pValue = NULL;
	char string[]="Value";
	int array[]={1,13,4,25,2};
	
	ASSERT_THAT(!pKey && !pValue);
	hashMap = HashMap_Create(HASH_CAPACITY,HashFunc,EqualityFunc);
	ASSERT_THAT(hashMap);
	
	ASSERT_THAT(0 == HashMap_Size(hashMap));
	
	for(i=0;i<3;i++)
		ASSERT_THAT(MAP_SUCCESS == HashMap_Insert(hashMap,(array + i),(string)));
	
	ASSERT_THAT(3 == HashMap_Size(hashMap));
	
	HashMap_Remove(hashMap,(array + 1),(void**)&pKey,(void**)&pValue);
	ASSERT_THAT(2 == HashMap_Size(hashMap));
	
	HashMap_Destroy(&hashMap,NULL,NULL);
END_UNIT
/*
*/

/*
TEST SUITE
*/

TEST_SUITE(generic hashmap)
	TEST(hashmap_create)
	TEST(hashmap_create_no_capacity)
	TEST(hashmap_create_no_user_functions)
	
	TEST(hashmap_destroy)
	TEST(hashmap_destroy_uninitialized)
	
	TEST(hashmap_insert)
	TEST(hashmap_insert_uninitialized)
	TEST(hashmap_insert_null_key)
	TEST(hashmap_insert_duplicate_key)
	
	TEST(hashmap_remove)
	TEST(hashmap_remove_uninitialized)
	TEST(hashmap_remove_null_key)
	TEST(hashmap_remove_key_not_found)
	
	TEST(hashmap_find)
	TEST(hashmap_find_uninitialized)
	TEST(hashmap_find_null_key)
	TEST(hashmap_find_key_not_found)
	
	TEST(hashmap_size)
	TEST(hashmap_size_uninitialized)
	TEST(hashmap_size_zero)
	
	TEST(hashmap_rehash)
	
	
	/*
	GAL TESTS
	*/
	
	TEST(hashMap_create)
	
	TEST(hashMap_destroy)
	
	TEST(hashMap_insert_int)
	TEST(hashMap_insert_char)
	TEST(hashMap_insert_uninitialized)
	TEST(hashMap_insert_duplicate)
	
	TEST(hashMap_remove)
	TEST(hashMap_remove_uninitialized)
	TEST(hashMap_remove_key_not_found)
	
	TEST(hashMap_find)
	TEST(hashMap_find_not_found)
	TEST(hashMap_find_uninitialized)
	TEST(hashMap_size)
	/*
	*/
END_SUITE

