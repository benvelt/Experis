/**************************************************************************************************
    Author :					Yair neeman
    Creation date :    		      2.7.18
    Date last modified :
    Description : Linked List creation.
**************************************************************************************************/
#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>			/* size_t */
#include "ADTDefs.h"		/* ADTErr */


typedef size_t (*HashFunc)(int key);
typedef struct HashSet HashSet;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Create ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief 			Create and initialize HashSet struct. create 2 arrays in size of 'size'. 
 * @param[in] 		receive integer for the array size.
 * @return Errors	Non.
 * @warning if 		Non.
 */

HashSet* HashSetCreate(size_t _size, float _loadFactor,size_t (*_hashFunction)(size_t));


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief 			free the arrays in HashSet struct and then free the HashSet struct itself.
 * @param[in] 		receive pointer to HashSet struct.
 * @return Errors 	Non.
 * @warning if 		Non.
 */
 
 void HashSetDestroy(HashSet* _set);
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Insert ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
/**  
 * @brief 
 * @param[in] 
 * @return Errors 
 *
 * @warning if 
 */

 ADTErr HashSetInsert(HashSet* _set, size_t _data);
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Remove ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
/**  
 * @brief 
 * @param[in] 
 * @return Errors 
 *
 * @warning if 
 */
 
 ADTErr HashSetRemove(HashSet* _set, size_t _data);
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Contains ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
/**  
 * @brief 
 * @param[in] 
 * @return Errors 
 *
 * @warning if 
 */
 
 int HashSetContains(HashSet* _set, size_t _data);
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Num Items ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
/**  
 * @brief 
 * @param[in] 
 * @return Errors 
 *
 * @warning if 
 */

 size_t HashSetSize(const HashSet* _set);
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Statistics ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
/**  
 * @brief 
 * @param[in] 
 * @return Errors 		, size_t *_maxCollisionsEvere, float* _aveargeCoolisions
 *
 * @warning if 
 */
 
 ADTErr HashSetStatistics(const HashSet* _set, size_t *_maxCollisionsEver, float *_averageCollisions);
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set For Each ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
/**  
 * @brief 
 * @param[in] 
 * @return Errors 
 *
 * @warning if 
 */
 
 void HashSetForEach(const HashSet* _hash, void (*_userFunction)(size_t _data));
 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Hash Set Max Rehash ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/  
 /**  
 * @brief 
 * @param[in] 
 * @return Errors 
 *
 * @warning if 
 */
 size_t HashSetMaxRehash(const HashSet* _hs);
 
 
 
#endif /*__HASH_H__*/
