#ifndef __PROTECTED_HASH_H__
#define __PROTECTED_HASH_H__

typedef struct ProtectedHash ProtectedHash;

typedef size_t (*HashFunction)(const void* _key);
typedef size_t (*LockFunction)(const void* _key);
typedef size_t (*EqualityFunction)(const void* _firstKey, const void* _secondKey);
typedef int (*KeyValueActionFunction)(const void* _key, void* _value, void* _context);
typedef void (*ValueUpdateFuncion)(void* _value, const void* _update);


typedef enum Map_Result {
        MAP_SUCCESS = 0,
        MAP_UNINITIALIZED_ERROR, /**< Uninitialized map error  */
        MAP_KEY_NULL_ERROR, /**< Key was null     */
        MAP_KEY_DUPLICATE_ERROR, /**< Duplicate key error   */
        MAP_KEY_NOT_FOUND_ERROR, /**< Key not found     */
        MAP_ALLOCATION_ERROR, /**< Allocation error     */
        MAP_LOCK_ERROR,
        MAP_UPSERT_INSERT,
        MAP_UPSERT_UPDATE
} Map_Result;

/**********************************************************************************************/

/**
 * @brief create Protected hash
 *
 * @return newly created protected hash
 */
ProtectedHash* ProtectedHash_Create(size_t _capacity,size_t _numOfLocks, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);

/**********************************************************************************************/

/**
 * @brief destroy protected hash
 *
 * @param[in] _protectH : pointer to the protect hash to destroy
 */
void ProtectedHash_Destroy(ProtectedHash** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));

/**********************************************************************************************/

/**
 * @brief Adjust map capacity and rehash all key/value pairs
 * @param[in] _map - exisiting map
 * @param[in] _newCapacity - new capacity shall be rounded to nearest larger prime number.
 * @return MAP_SUCCESS or MAP_ALLOCATION_ERROR
 */
Map_Result ProtectedHash_Rehash(ProtectedHash *_map, size_t newCapacity);

/**********************************************************************************************/

/**
 * @brief upsert to protect hash
 *
 * @param[in] _proHash : pointer to the protect hash
 * @param[in] _key : a key to search in the protect hash
 * @param[in] _value : a value to check if exict in protect hash
 * @param[in] _updateSub : a call back function to update new data in the protect hash
 */
Map_Result ProtectedHash_Upsert(ProtectedHash* _map, const void* _key, const void* _value, ValueUpdateFuncion _updateFunc);

/**********************************************************************************************/

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
Map_Result ProtectedHash_Find(const ProtectedHash* _map, const void* _searchKey, void** _pValue);

/**********************************************************************************************/

/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(?)
 */
size_t ProtectedHash_Size(const ProtectedHash* _map);

/**********************************************************************************************/

/**
 * @brief function that do some action on each value in the protected hash
 * @param[in] _proHash : pointer to the protect hash
 * @param[in] _action : action function to do on each value in the protect hash
 * @param[in] _context : optional context to the action function
 */
size_t ProtectedHash_ForEach(const ProtectedHash* _map, KeyValueActionFunction _action, void* _context);

/**********************************************************************************************/

#ifndef NDEBUG

typedef struct Map_Stats {
        size_t pairs;        /* number of pairs stored */
        size_t collisions;   /* total number of collisions encountered */
        size_t buckets;      /* total number of buckets */
        size_t chains;       /* none empty buckets (having non zero length list) */
        size_t maxChainLength; /* length of longest chain */
        size_t averageChainLength; /* average length of none empty chains */
} Map_Stats;

Map_Stats ProtectedHash_GetStatistics(const ProtectedHash* _map);

#endif /* NDEBUG */

/**********************************************************************************************/
size_t ProtectedHash_ForEach(const ProtectedHash* _map, KeyValueActionFunction _action, void* _context);

#endif /*__PROTECTED_HASH_H__*/
