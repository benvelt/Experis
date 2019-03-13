/*
   Title : Hash Map
   Author : Gal Bari

 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "generic_doubleLL_itr.h"
#include "generic_doubleLL.h"
#include "Protected_Hash.h"

#define DEAD_MAGIC 1
#define HASH_MAGIC 0xBEEFBEEF
#define IS_HASH(H)   ((H) && (HASH_MAGIC == (H)->m_magic))
#define ASSERT_SUCCESS(COND,LABEL) do { if (!(COND)) goto LABEL; } while(0)


struct ProtectedHash
{
        pthread_mutex_t* m_lockArr;
        size_t m_magic;
        List* *m_buckets;
        HashFunction m_hashFunc;
        LockFunction m_lockFunc;
        EqualityFunction m_equalityFunc;
        size_t m_noLocks;
        size_t m_capacity;
        size_t m_noItems;
#ifndef NDEBUG
        Map_Stats m_stats;
#endif

};

typedef struct
{
        void* m_key;
        void* m_value;

}Pair;

/**********************************************************************************************
                         STATIC UTILITY FUNCTIONS FOR HASH MAP
                              ------------------------
**********************************************************************************************/

/*******************************************************
        STATIC UTILITY FUNCTION FIND NEXT PRIME
*******************************************************/

static size_t FindNextPrime(size_t _num)
{

        size_t nextPrime,i;
        nextPrime = _num;

        while (1)
        {
                for(i = 2; i < nextPrime; i++)
                {
                        if(nextPrime % i == 0)
                        {
                                break;
                        }
                }

                if(i == nextPrime)
                {
                        return nextPrime;
                }
                nextPrime++;
        }
}

/*******************************************************
      STATIC UTILITY FUNCTION DESTROY PAIR
*******************************************************/

static void DestroyPair(Pair* _pair,void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{

        if(_pair) {

                if(_keyDestroy)
                {
                        _keyDestroy(_pair->m_key);
                }

                if(_valDestroy)
                {
                        _valDestroy(_pair->m_value);
                }

                free(_pair);
        }
}

/*******************************************************
      STATIC UTILITY FUNCTION DESTROY BUCKET
*******************************************************/

static void DestroyBucket(List* _bucket, void (*_keyDestroy)(void* _key),  void (*_valDestroy)(void* _value))
{

        ListItr itr;
        size_t bucketSize;
        Pair* pair;
        int i;

        itr = ListItr_Begin(_bucket);
        bucketSize=List_Size(_bucket);

        for(i=0; i<bucketSize; i++)
        {
                pair=ListItr_Get(itr);
                DestroyPair(pair,_keyDestroy,_valDestroy);
                itr=ListItr_Next(itr);
        }
        List_Destroy(&_bucket,NULL);
}


/*******************************************************
     STATIC UTILITY FUNCTION TRANSFER BUCKETS ARRAY
*******************************************************/

static void TransferBucketsArray(ProtectedHash *_map,List* *_newBuckets,size_t _newCapacity)
{

        ListItr itr;
        Pair* pair;
        size_t bucketSize;
        size_t i,j,hashCode;
        size_t oldHashCapacity=_map->m_capacity;;

        for(i=0; i<oldHashCapacity; i++)
        {
                itr = ListItr_Begin(_map->m_buckets[i]);
                bucketSize=List_Size(_map->m_buckets[i]);

                for(j=0; j<bucketSize; j++)
                {
                        pair=ListItr_Remove(itr);
                        hashCode = _map->m_hashFunc(pair->m_key) % (_newCapacity);
                        List_PushTail(_newBuckets[hashCode],pair);
                        itr=ListItr_Next(itr);
                }
                free(_map->m_buckets[i]);
        }
}

/*******************************************************
      STATIC UTILITY FUNCTION BUCKET FOR EACH
*******************************************************/

static int Bucket_ForEach(List* _bucket, KeyValueActionFunction _action, void* _context)
{
        size_t bucketSize;
        size_t i;
        ListItr listCurrent;
        Pair* currPair;

        bucketSize = List_Size(_bucket);

        listCurrent = ListItr_Begin(_bucket);

        for (i=0; i<bucketSize; i++)
        {
                currPair = ListItr_Get(listCurrent);
                _action(currPair->m_key, currPair->m_value, _context);
                listCurrent = ListItr_Next(listCurrent);
        }

        return i;
}

/*******************************************************
      STATIC UTILITY FUNCTION FIND KEY IN LIST
*******************************************************/

static Pair* FindPairInBucket(List* _bucket,const void* _key,EqualityFunction _keysEqualFunc)
{

        ListItr itr;
        Pair* pair;
        size_t listSize;
        int i;
        if(!_bucket)
        {
                return NULL;
        }
        itr = ListItr_Begin(_bucket);
        listSize = List_Size(_bucket);

        for(i=0; i<listSize; i++)
        {
                pair=ListItr_Get(itr);

                if(_keysEqualFunc(pair->m_key,_key) == 0)
                {
                        return pair;
                }
                itr=ListItr_Next(itr);
        }

        return NULL;
}

/*******************************************************
      STATIC UTILITY FUNCTION DELETE PAIR FROM BUCKET
*******************************************************/
/*
   static Pair* DeletePairFromBucket(List* _bucket, const void* _key,EqualityFunction _keysEqualFunc)
   {
        ListItr itr;
        Pair* pairInBucket;
        size_t listSize;
        int i;

        itr = ListItr_Begin(_bucket);
        listSize = List_Size(_bucket);

        for(i=0; i<listSize; i++)
        {
                pairInBucket=ListItr_Get(itr);

                if(_keysEqualFunc(pairInBucket->m_key,_key)== 0)
                {
                        pairInBucket = ListItr_Remove(itr);
                        return pairInBucket;
                }
                itr=ListItr_Next(itr);
        }

        return NULL;
   }
 */
/*******************************************************
      STATIC UTILITY FUNCTION CREATE PAIR
*******************************************************/

static Pair* CreatePair(void* _key,void* _value)
{

        Pair* pair;
        pair=(Pair*)malloc(sizeof(Pair));

        if(!pair)
        {
                return NULL;
        }

        pair->m_key=_key;
        pair->m_value=_value;

        return pair;
}

/*******************************************************
      STATIC UTILITY FUNCTION INSERT PAIR TO BUCKET
*******************************************************/

static void InsertPairToBucket(List* _bucket, Pair* _newPair)
{
        List_PushTail(_bucket,_newPair);
}


/**********************************************************************************************
          STATISTIC FUNCTIONS FOR HASH STATISTICS  ( USED ONLY IN DEBUGGING MODE )
                              ------------------------
**********************************************************************************************/

#ifndef NDEBUG

/*******************************************************
      STATIC STATISTICS FUNCTION NUMBER OF CHAINS
*******************************************************/
static size_t Stats_NumOfChains(ProtectedHash* _map)
{
        int i;
        size_t nonEmptyChains=0;
        for(i=0; i<_map->m_capacity; i++)
        {
                if(List_Size(_map->m_buckets[i]) > 0)
                {

                        nonEmptyChains+=1;
                }

        }
        return nonEmptyChains;
}

/*******************************************************
     STATIC STATISTICS FUNCTION NUMBER OF COLLISIONS
*******************************************************/

static size_t Stats_NumOfCollisions(List* _bucket,size_t _numOfCollisions)
{
        return List_Size(_bucket) > 1 ? _numOfCollisions++ : _numOfCollisions;

}

/*******************************************************
    STATIC STATISTICS FUNCTION AVERAGE CHAIN LENGTH
*******************************************************/

static size_t Stats_AverageChainLength(ProtectedHash* _map)
{
        size_t totalPairs = 0;
        size_t nonEmptyChains = 0;
        int i;

        for(i = 0; i < _map->m_capacity; i++)
        {
                if(List_Size(_map->m_buckets[i]) > 0 )
                {
                        nonEmptyChains++;
                        totalPairs += List_Size(_map->m_buckets[i]);
                }
        }
        if(nonEmptyChains > 0 )
        {
                return (totalPairs / nonEmptyChains);
        }
        return 0;
}

/*******************************************************
     STATIC STATISTICS FUNCTION MAX CHAIN LENGTH
*******************************************************/

static size_t Stats_MaxChainLength(ProtectedHash* _map)
{
        size_t maxChainLength = 0;
        int i;

        for(i = 0; i < _map->m_capacity; i++)
        {
                if(List_Size(_map->m_buckets[i]) > maxChainLength )
                {

                        maxChainLength = List_Size(_map->m_buckets[i]);
                }
        }

        return maxChainLength;
}

#endif

/**********************************************************************************************
                             API FUNCTIONS FOR HASH MAP
                              ------------------------
**********************************************************************************************/


/*******************************************************
        API FUNCTION CREATE HASH MAP
*******************************************************/

ProtectedHash* ProtectedHash_Create(size_t _capacity,size_t _numOfLocks, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
        ProtectedHash* protectedHash;
        int i;

        ASSERT_SUCCESS(_hashFunc,HASH_MAP_ERROR);
        ASSERT_SUCCESS(_keysEqualFunc,HASH_MAP_ERROR);
        ASSERT_SUCCESS((_capacity > 2),HASH_MAP_ERROR);

        protectedHash = (ProtectedHash*)malloc(sizeof(ProtectedHash));
        ASSERT_SUCCESS(protectedHash,HASH_MAP_ERROR);

        _capacity = FindNextPrime(_capacity);

        protectedHash->m_buckets=malloc(_capacity*sizeof(List*));
        ASSERT_SUCCESS(protectedHash->m_buckets, BUCKETS_ERROR);

        for(i=0; i<_capacity; i++)
        {
                protectedHash->m_buckets[i] = List_Create();
                ASSERT_SUCCESS(protectedHash->m_buckets[i],BUCKET_ERROR);
        }

        protectedHash->m_lockArr=malloc((_numOfLocks)*sizeof(pthread_mutex_t));
        ASSERT_SUCCESS(protectedHash->m_lockArr, BUCKETS_ERROR);

        for(i=0; i<_numOfLocks; i++)
        {
                if(pthread_mutex_init(&protectedHash->m_lockArr[i], NULL) != 0)
                {
                        goto BUCKET_ERROR;
                }
        }

        protectedHash->m_noLocks = _numOfLocks;
        protectedHash->m_capacity = _capacity;
        protectedHash->m_noItems = 0;
        protectedHash->m_hashFunc = _hashFunc;
        protectedHash->m_lockFunc = _hashFunc;
        protectedHash->m_equalityFunc = _keysEqualFunc;

  #ifndef NDEBUG
        protectedHash->m_stats.buckets=protectedHash->m_capacity;
        protectedHash->m_stats.pairs=0;
        protectedHash->m_stats.collisions=0;
        protectedHash->m_stats.chains=0;
        protectedHash->m_stats.maxChainLength=0;
        protectedHash->m_stats.averageChainLength=0;
  #endif

        protectedHash->m_magic=HASH_MAGIC;
        return protectedHash;

BUCKET_ERROR:
        {
                int j;
                for(j=i-1; j>=0; j--)
                {
                        DestroyBucket(protectedHash->m_buckets[j],NULL,NULL);
                }
        }
        free(protectedHash->m_buckets);

BUCKETS_ERROR:
        free(protectedHash);

HASH_MAP_ERROR:
        return NULL;
}

/*******************************************************
        API FUNCTION DESTROY HASH MAP
*******************************************************/

void ProtectedHash_Destroy(ProtectedHash** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
        int i;

        if(!_map || !IS_HASH(*_map))
        {
                return;
        }

        (*_map)->m_magic=DEAD_MAGIC;

        for(i=0; i<(*_map)->m_capacity; i++)
        {
                DestroyBucket((*_map)->m_buckets[i],_keyDestroy,_valDestroy);
        }
        for(i=0; i<(*_map)->m_noLocks; i++)
        {
                pthread_mutex_unlock(&(*_map)->m_lockArr[i]);
                pthread_mutex_destroy(&(*_map)->m_lockArr[i]);
        }
        free((*_map)->m_lockArr);
        free((*_map)->m_buckets);
        free(*_map);
        *_map=NULL;
}


/*******************************************************
     API FUNCTION HASH MAP REHASH
*******************************************************/

Map_Result ProtectedHash_Rehash(ProtectedHash *_map, size_t _newCapacity)
{

        List* *newBuckets;
        size_t newCap;
        int i;

        if(!IS_HASH(_map))
        {

                return MAP_UNINITIALIZED_ERROR;
        }
        for(i=0; i<_map->m_noLocks; i++)
        {
                pthread_mutex_lock(&_map->m_lockArr[i]);
        }
        newCap = FindNextPrime(_newCapacity);
        newBuckets = malloc(newCap*sizeof(List*));

        if(!newBuckets) {

                return MAP_ALLOCATION_ERROR;
        }

        for(i=0; i<newCap; i++)
        {
                newBuckets[i] = List_Create();
                /* Destroy all buckets already created in case creating a new one fails */
                if(!newBuckets[i])
                {
                        {
                                int j;
                                for(j=i-1; j>=0; j--)
                                {
                                        DestroyBucket(_map->m_buckets[j],NULL,NULL);
                                }
                        }
                }
        }

        TransferBucketsArray(_map,newBuckets,newCap);
        _map->m_capacity=newCap;
        _map->m_buckets=newBuckets;

        for(i=0; i<_map->m_noLocks; i++)
        {
                pthread_mutex_unlock(&_map->m_lockArr[i]);
        }
        return MAP_SUCCESS;
}

/*******************************************************
            API FUNCTION HASH MAP UPSERT
*******************************************************/

Map_Result ProtectedHash_Upsert(ProtectedHash* _map, const void* _key, const void* _value, ValueUpdateFuncion _updateFunc)
{
        Pair* newPair;
        Pair* pairInBucket;
        size_t hashCode;

int i = 0;

        if(!IS_HASH(_map))
        {
                return MAP_UNINITIALIZED_ERROR;
        }

        if(!_key)
        {
                return MAP_KEY_NULL_ERROR;
        }

        hashCode = _map->m_hashFunc(_key) % (_map->m_capacity);
		for(i = 0; i < _map->m_noLocks; ++i)
		{
	        pthread_mutex_lock(&_map->m_lockArr[i]);
			
		}


        pairInBucket = FindPairInBucket(_map->m_buckets[hashCode],_key,_map->m_equalityFunc);
        /* If pair in bucket exists then update the value*/

        if(pairInBucket)
        {
                _updateFunc(pairInBucket->m_value,_value);
        for(i = 0; i < _map->m_noLocks; ++i)
		{
                pthread_mutex_unlock(&_map->m_lockArr[i]);
			
		}
                return MAP_UPSERT_UPDATE;
        }

        /* else create a new pair and insert it */
        newPair = CreatePair((void*)_key,(void*)_value);
        if(!newPair)
        {
        for(i = 0; i < _map->m_noLocks; ++i)
		{
                pthread_mutex_unlock(&_map->m_lockArr[i]);
			
		}
                return MAP_ALLOCATION_ERROR;

        }

        InsertPairToBucket(_map->m_buckets[hashCode],newPair);
        _map->m_noItems++;

        for(i = 0; i < _map->m_noLocks; ++i)
		{
                pthread_mutex_unlock(&_map->m_lockArr[i]);
			
		}

 #ifndef NDEBUG

        _map->m_stats.pairs++;
        _map->m_stats.chains = Stats_NumOfChains(_map);
        _map->m_stats.collisions = Stats_NumOfCollisions(_map->m_buckets[hashCode],_map->m_stats.collisions);
        _map->m_stats.averageChainLength = Stats_AverageChainLength(_map);
        _map->m_stats.maxChainLength = Stats_MaxChainLength(_map);

 #endif
        return MAP_UPSERT_INSERT;
}


/*******************************************************
            API FUNCTION HASH MAP FIND
*******************************************************/

Map_Result ProtectedHash_Find(const ProtectedHash* _map, const void* _searchKey, void** _pValue)
{

        size_t hashCode;
        /*size_t lockCode;*/
        Pair* pairFound;

        if(!IS_HASH(_map) || !_pValue )
        {
                return MAP_UNINITIALIZED_ERROR;
        }

        if(!_searchKey)
        {
                return MAP_KEY_NULL_ERROR;
        }

        hashCode = _map->m_hashFunc(_searchKey) % (_map->m_capacity);
        /*lockCode = _map->m_lockFunc(_searchKey) % (_map->m_noLocks);*/
        /*pthread_mutex_lock(&_map->m_lockArr[lockCode]);*/

        pairFound = FindPairInBucket(_map->m_buckets[hashCode],_searchKey,_map->m_equalityFunc);
        if(!pairFound)
        {
                /* pthread_mutex_unlock(&_map->m_lockArr[lockCode]);*/
                return MAP_KEY_NOT_FOUND_ERROR;
        }

        *_pValue=pairFound->m_value;

        /*pthread_mutex_unlock(&_map->m_lockArr[lockCode]);*/

        return MAP_SUCCESS;
}

/*******************************************************
            API FUNCTION HASH MAP SIZE
*******************************************************/

size_t ProtectedHash_Size(const ProtectedHash* _map)
{

        return IS_HASH(_map) ? _map->m_noItems : 0;
}

/*******************************************************
       API FUNCTION HASH MAP FOR EACH
*******************************************************/

size_t ProtectedHash_ForEach(const ProtectedHash* _map, KeyValueActionFunction _action, void* _context)
{
        size_t i;
        int counter=0;
        size_t lockCode;


        if (!IS_HASH(_map))
        {
                return 0;
        }

        for (i=0; i < _map->m_capacity; i++)
        {
                lockCode = _map->m_lockFunc(&i) % (_map->m_noLocks);
                pthread_mutex_lock(&_map->m_lockArr[lockCode]);
                counter += Bucket_ForEach(_map->m_buckets[i],_action,_context);
                pthread_mutex_unlock(&_map->m_lockArr[lockCode]);
        }

        return counter;
}














