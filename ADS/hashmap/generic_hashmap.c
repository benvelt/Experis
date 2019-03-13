/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			18.07.18
 * Date last modified :
 * Description : 			Hash Map create, destroy, rehash, insert, remove, find, size and for each functions.
******************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "generic_hashmap.h"
#include "generic_doubleLL.h"
#include "generic_doubleLL_itr.h"

/*
MACROS DEFINITIONS
*/
#define MAGIC					0xDDDDDDDD
#define HASH_CAP(HM)			((HM))->m_capacity
#define HASH_NOB(HM)			((HM))->m_nBuckets
#define HASH_BUCKETS(HM)		((HM))->m_arrOfBuckets
#define HASH_FUNC(HM)			((HM))->m_hashFunc
#define HASH_EQUA_FUNC(HM)		((HM))->m_keysEqualFunc
#define HASH_STATS(HM)			((HM))->m_stats

#define PAIR_KEY(P)		((P))->m_key
#define PAIR_VAL(P)		((P))->m_value

#define BEGIN(L)		ListItr_Begin((L))
#define NEXT(L)			ListItr_Next((L))

#define IS_VALID(HM)	(((HM))) && MAGIC == (((HM)))->m_magic
#define TRUE 1
#define FALSE 0

/*
STRUCTURES DECLARATIONS
*/
struct HashMap
{
	size_t					m_magic;
	size_t					m_capacity;
	size_t					m_nBuckets;
	List**					m_arrOfBuckets;
	HashFunction			m_hashFunc;
	EqualityFunction		m_keysEqualFunc;
#ifndef NDEBUG
	Map_Stats				m_stats;
#endif /* NDEBUG */
};

struct Pair
{
	void*		m_key;
	void*		m_value;
};

/*
STATIC FUNCTIONS DECLARATIONS
*/
static size_t NextPrimeNum(const size_t _capacity);

static Pair* PairCreate(const void* _key, const void* _value);
static void PairDestroy(Pair* pair, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));

static List**	BucketsCreate(HashMap* _map);
static void		BucketsDestroy(List** _arrBucket, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value), size_t _nob);
static Pair*	BucketsFindKey(List** _arrBucket, const size_t _hashKey,const void* _key, EqualityFunction _keysEqualFunc);
static int		BucketRemovePair(List** _arrBucket, const size_t _hashKey,const void* _key, void** _pKey, void** _pValue, EqualityFunction _keysEqualFunc);
static int		BucketsInsert(List** _arrBucket, const size_t _hashKey, const void* _key, const void* _value);


							static int BucketsTransfer(HashMap* _map, List** _oldBuckets, List** _newBuckets, size_t _oldNOB);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Create a new hash map with given capcity and key characteristics.
 * @param[in] _capacity - Expected max capacity 
 * 						  actuall capacity will be equal to nearest larger prime number.
 * @param[in] _hashFunc - hashing function for keys
 * @param[in] _keysEqualFunc - equality check function for keys. 
 * @return newly created map or null on failure
 */
/* NOTE: all the buckets are initialized to an empy lists */
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	HashMap* hashmap = NULL;
	
	if(!_capacity || !_hashFunc || !_keysEqualFunc) return NULL;
	
	hashmap = malloc(sizeof(HashMap));
	
	if(!hashmap) return hashmap;
	
	hashmap->m_magic = MAGIC;
	HASH_CAP(hashmap) = NextPrimeNum(_capacity);
	HASH_NOB(hashmap) = HASH_CAP(hashmap);
	
	HASH_BUCKETS(hashmap) = BucketsCreate(hashmap);
	
	if(!HASH_BUCKETS(hashmap))
	{
		hashmap->m_magic = -1;
		free(hashmap);
		return hashmap;
	}
	
	HASH_FUNC(hashmap) = _hashFunc;
	HASH_EQUA_FUNC(hashmap) = _keysEqualFunc;
#ifndef NDEBUG
	/* initiate the statistics */
	HASH_STATS(hashmap).pairs = 0;
	HASH_STATS(hashmap).collisions = 0;
	HASH_STATS(hashmap).buckets = 0;
	HASH_STATS(hashmap).chains = 0;
	HASH_STATS(hashmap).maxChainLength = 0;
	HASH_STATS(hashmap).averageChainLength = 0;
#endif /* NDEBUG */
	
	return hashmap;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief destroy hash map and set *_map to null
 * @param[in] _map : map to be destroyed
 * @param[optional] _keyDestroy : pointer to function to destroy keys
 * @param[optional] _valDestroy : pointer to function to destroy values 
 * @details optionally destroy all keys and values using user provided functions
 */
void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	if(_map && IS_VALID(*_map))
	{
		BucketsDestroy(HASH_BUCKETS(*_map), _keyDestroy, _valDestroy, HASH_NOB(*_map));
		free(*_map);
		*_map = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_Rehash ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Adjust map capacity and rehash all key/value pairs
 * @param[in] _map - exisiting map
 * @param[in] _newCapacity - new capacity shall be rounded to nearest larger prime number.
 * @return MAP_SUCCESS or MAP_ALLOCATION_ERROR
 */
/* TODO IN ORDER TO AVOID ALL THE NEW ALLOCATIONS, ONE CAN JUST TRANSFER POINTERS FROM THE OLD LIST TO THE NEW LIST */
Map_Result HashMap_Rehash(HashMap *_map, size_t _newCapacity)
{
	List** newBuckets = NULL;
	Map_Result mapRes = MAP_UNINITIALIZED_ERROR;
	int trnsRes = FALSE;
	size_t oldCap = HASH_CAP(_map);
	
	if(IS_VALID(_map))
	{
		if(_newCapacity == HASH_CAP(_map)) return MAP_SUCCESS;
		mapRes = MAP_ALLOCATION_ERROR;
		oldCap = HASH_CAP(_map);
		HASH_CAP(_map) = NextPrimeNum(_newCapacity);
		HASH_NOB(_map) = HASH_CAP(_map);
		
		newBuckets = BucketsCreate(_map);
		if(newBuckets)
		{
			mapRes = MAP_SUCCESS;
			
			trnsRes = BucketsTransfer(_map, HASH_BUCKETS(_map), newBuckets, oldCap);
			if(FALSE == trnsRes)
			{
				mapRes = MAP_ALLOCATION_ERROR;
				BucketsDestroy(newBuckets, NULL, NULL, HASH_NOB(_map));
				HASH_CAP(_map) = oldCap;
				HASH_NOB(_map) = HASH_CAP(_map);
				return mapRes;
			}
			BucketsDestroy(HASH_BUCKETS(_map), NULL, NULL, oldCap);
			HASH_BUCKETS(_map) = newBuckets;
		}
	}
	return mapRes;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_Insert ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Insert a key-value pair into the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index 
 * @param[in] _value - the value to associate with the key 
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_DUPLICATE_ERROR	if key alread present in the map
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_ALLOCATION_ERROR on failer to allocate key-value pair
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
	size_t newKey = 0;
	Map_Result mapRes = MAP_UNINITIALIZED_ERROR;
	int insRes;
	
	if(IS_VALID(_map))
	{
		mapRes = MAP_KEY_NULL_ERROR;
		if(_key)
		{
			newKey = HASH_FUNC(_map)(_key);
			newKey = newKey % HASH_CAP(_map);
			if(BucketsFindKey(HASH_BUCKETS(_map), newKey, _key, HASH_EQUA_FUNC(_map))) return MAP_KEY_DUPLICATE_ERROR;
			
			insRes = BucketsInsert(HASH_BUCKETS(_map), newKey, _key, _value);
			switch(insRes)
			{
				case TRUE :
					mapRes = MAP_SUCCESS;
					break;
				case FALSE :
					mapRes = MAP_ALLOCATION_ERROR;
					break;
			}
		}
	}
	return mapRes;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_Remove ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Remove a key-value pair from the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the map
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to found key
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	Map_Result mapRes = MAP_UNINITIALIZED_ERROR;
	size_t newKey = 0;
	int remRes = 0;
	
	if(IS_VALID(_map))
	{
		mapRes = MAP_KEY_NULL_ERROR;
		
		if(_searchKey && _pKey)
		{
			mapRes = MAP_KEY_NOT_FOUND_ERROR;
			
			newKey = HASH_FUNC(_map)(_searchKey);
			newKey = newKey % HASH_CAP(_map);
			
			remRes = BucketRemovePair(HASH_BUCKETS(_map), newKey, _searchKey, _pKey, _pValue, HASH_EQUA_FUNC(_map));
			
			if(!remRes) return mapRes;
			
			mapRes = MAP_SUCCESS;
		}
	}
	return mapRes;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_Find ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Find a value by key
 * complexty(?)
 * @param[in] _map - Hash map to use, must be initialized
 * @param[in] _searchKey - key to serve as index for search
 * @param[out] _pValue - pointer to variable that will get the value assoiciated with the search key.
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	Map_Result mapRes = MAP_UNINITIALIZED_ERROR;
	Pair* srcPair = NULL;
	size_t newKey = 0;
	
	if(IS_VALID(_map))
	{
		mapRes = MAP_KEY_NULL_ERROR;
		if(_searchKey)
		{
			mapRes = MAP_KEY_NOT_FOUND_ERROR;
			
			newKey = HASH_FUNC(_map)(_searchKey);
			newKey = newKey % HASH_CAP(_map);
			
			srcPair = BucketsFindKey(HASH_BUCKETS(_map), newKey,_searchKey, HASH_EQUA_FUNC(_map));
			if(!srcPair) return mapRes;
		
			*_pValue = PAIR_VAL(srcPair);
		
			mapRes = MAP_SUCCESS;
		}
	}
	
	return mapRes;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_Size ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(?)
 */
size_t HashMap_Size(const HashMap* _map)
{
	size_t pairsNum = 0;
	int i = 0;
	
	if(IS_VALID(_map))
	{
		for(i = 0; i < HASH_NOB(_map); ++i)
		{
			pairsNum += List_Size(HASH_BUCKETS(_map)[i]);
		}
	}
	
	return pairsNum;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ HashMap_ForEach ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * This method is optional in the homework 
 * @brief Iterate over all key-value pairs in the map and call a function for each pair
 * The user provided KeyValueActionFunction will be called for each element.  
 * Iteration will stop if the called function returns a zero for a given pair
 * 
 * @param[in] _map - Hash map to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
 */
size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC NextPrimeNum ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static size_t NextPrimeNum(const size_t _capacity)
{
	size_t j, nextPrimeNum = _capacity + 1;
	
	while(1)
	{
		for(j = 2; j < nextPrimeNum; ++j)
			if(nextPrimeNum % j == 0) break;
		if(j == nextPrimeNum)
			break;
		++nextPrimeNum;
	}
	return nextPrimeNum;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC PairCreate ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static Pair* PairCreate(const void* _key, const void* _value)
{
	Pair* newPair = NULL;
	
	newPair = malloc(sizeof(Pair));
	if(!newPair) return newPair;
	
	PAIR_KEY(newPair) = (void*)_key;
	PAIR_VAL(newPair) = (void*)_value;
	
	return newPair;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC PairDestroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void PairDestroy(Pair* pair, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	if(_keyDestroy) _keyDestroy(pair->m_key);
	if(_valDestroy) _valDestroy(pair->m_value);
	free(pair);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC BucketsCreate ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static List** BucketsCreate(HashMap* _map)
{	
	int i, j;
	List** arrBucket;
	arrBucket = malloc(HASH_NOB(_map) * sizeof(List*));
	
	if(!arrBucket) return arrBucket;
	
	for(i = 0; i < HASH_NOB(_map); ++i)
	{
		arrBucket[i] = List_Create();
		if(!arrBucket[i])
		{
			for(j = 0; j <= i; ++i) List_Destroy(&arrBucket[j], NULL);
			free(arrBucket);
			return NULL;
		}
	}
	return arrBucket;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC BucketsDestroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void BucketsDestroy(List** _arrBucket, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value), size_t _nob)
{
	int i = 0;
	Pair* pair = NULL;
	
	for(i = 0; i < _nob; ++i)
	{
		while(List_Size(_arrBucket[i]))
		{
			List_PopTail(_arrBucket[i], (void**)&pair);
			PairDestroy(pair, _keyDestroy, _valDestroy);
		}
		List_Destroy(&_arrBucket[i], NULL);
	}
	free(_arrBucket);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC BucketsFindKey ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static Pair* BucketsFindKey(List** _arrBucket, const size_t _hashKey,const void* _key, EqualityFunction _keysEqualFunc)
{
	ListItr itrCurr = NULL;
	ListItr itrEnd = NULL;
	Pair* pairCurr = NULL;
	
	if(List_Size(_arrBucket[_hashKey]))
	{
		itrEnd = ListItr_Next(ListItr_End(_arrBucket[_hashKey]));
		
		for(itrCurr = BEGIN(_arrBucket[_hashKey]); TRUE != ListItr_Equals(itrCurr, itrEnd); itrCurr = NEXT(itrCurr))
		{
			pairCurr = (Pair*)ListItr_Get(itrCurr);
			
			if(_keysEqualFunc(_key, PAIR_KEY(pairCurr))) return pairCurr;
		}
	}
	return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC BucketRemovePair ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int BucketRemovePair(List** _arrBucket, const size_t _hashKey,const void* _key, void** _pKey, void** _pValue, EqualityFunction _keysEqualFunc)
{
	ListItr itrCurr = NULL;
	ListItr itrEnd = NULL;
	Pair* pairCurr = NULL;
	
	if(List_Size(_arrBucket[_hashKey]))
	{
		itrEnd = ListItr_Next(ListItr_End(_arrBucket[_hashKey]));
		
		for(itrCurr = BEGIN(_arrBucket[_hashKey]); TRUE != ListItr_Equals(itrCurr, itrEnd); itrCurr = NEXT(itrCurr))
		{
			pairCurr = (Pair*)ListItr_Get(itrCurr);
			
			if(_keysEqualFunc(_key, PAIR_KEY(pairCurr))) 
			{
				*_pKey = PAIR_KEY(pairCurr);
				*_pValue = PAIR_VAL(pairCurr);
				ListItr_Remove(itrCurr);
				PairDestroy(pairCurr, NULL, NULL);
				return 1;
			}
		}
	}
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC BucketsKeyInsert ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int BucketsInsert(List** _arrBucket, const size_t _hashKey, const void* _key, const void* _value)
{
	Pair* newPair = NULL;
	
	newPair = PairCreate(_key, _value);
	if(!newPair) return FALSE;
	
	if(LIST_ALLOCATION_ERROR == List_PushTail(_arrBucket[_hashKey], newPair)) return FALSE;
	
	return TRUE;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC BucketsTransfer ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int BucketsTransfer(HashMap* _map, List** _oldBuckets, List** _newBuckets, size_t _oldNOB)
{
	int i = 0;
	int insertRes = 0;
	size_t hashKey = 0;
	ListItr itrCurr = NULL;
	ListItr itrEnd = NULL;
	Pair* pairCurr = NULL;
	
	for(i = 0; i < _oldNOB; ++i)
	{
		itrEnd = ListItr_Next(ListItr_End(HASH_BUCKETS(_map)[i]));
		for(itrCurr = BEGIN(_oldBuckets[i]); TRUE != ListItr_Equals(itrCurr, itrEnd); itrCurr = NEXT(itrCurr))
		{
			pairCurr = (Pair*)ListItr_Get(itrCurr);
			hashKey = HASH_FUNC(_map)(PAIR_KEY(pairCurr));
			hashKey = hashKey % HASH_CAP(_map);
			insertRes = BucketsInsert(_newBuckets, hashKey, PAIR_KEY(pairCurr), PAIR_VAL(pairCurr));
			if(TRUE != insertRes) return FALSE;
		}
	}
	return TRUE;
}


