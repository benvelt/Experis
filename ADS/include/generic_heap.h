/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			26.07.18
 * Date last modified :
 * Description : 			Heap build, destroy, insert, max, extract max, items num, for each functions.
******************************************************************************************************************/

#ifndef __GENERIC_HEAP_H__
#define __GENERIC_HEAP_H__

#include "generic_vector.h"

/** 
 * @brief Built a Binary Heap container data type 
 * 
 * @author Author Ben Velt (ben.velt@gmail.com)
 */ 

typedef struct Heap Heap;

typedef int(*HeapItemCompare)(void* _item1, void* _item2);
typedef int(*HeapElementAction)(void* _element, size_t _index, void* _context);

typedef enum
{
	HEAP_SUCCESS
	,HEAP_UNINITIALIZED_ERROR
	,HEAP_ALLOCATION_ERROR
	,HEAP_INDEX_OUT_OF_BOUNDS_ERROR
	,HEAP_OVERFLOW_ERROR
	,HEAP_UNDERFLOW_ERROR
	,HEAP_MAX_NUMBER_ERROR
} Heap_Result;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap_Build ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Build a new Heap from exist vector.
 * @param[in] _heap - 
 * @return Heap* - on success / NULL on fail. The Heap will be sorted by MAX ORDER. 
 * @warning if _vector not exist will return NULL.
 * @warning if allocation of Heap failed will return NULL.
 */
Heap* Heap_Build(Vector* _vector, HeapItemCompare _func);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap_Destroy ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Deallocate a previously allocated _heap.
 * @param[in] _heap - Heap to be deallocated.
 * @note _heap will be equal to null after this function.
 */
void Heap_Destroy(Heap* *_heap);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap_Insert ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief insert an item to an existing _heap.
 * @param[in] _heap - Heap to use.
 * @param[in] _data - new data to insert.
 * @return success or error code 
 * @retval HEAP_SUCCESS on success;
 * @retval HEAP_UNINITIALIZED_ERROR if _heap or _data uninitialized;
 * @retval HEAP_OVERFLOW_ERROR when _heap is full;
 */
Heap_Result Heap_Insert(Heap* _heap, void* _data);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Max ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief get get the max value of an existing _heap.
 * @param[in] _heap - Heap to use.
 * @param[in] _data - data to get the max value.
 * @return success or error code 
 * @retval HEAP_SUCCESS on success;
 * @retval HEAP_UNINITIALIZED_ERROR if _heap or _data uninitialized;
 */
Heap_Result Heap_Max(Heap* _heap, void** _data);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap_ExtractMax ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief remove the max value of an existing _heap.
 * @param[in] _heap - Heap to use.
 * @param[in] _data - data to get the max value.
 * @return success or error code 
 * @retval HEAP_SUCCESS on success;
 * @retval HEAP_UNINITIALIZED_ERROR if _heap or _data uninitialized;
 */
Heap_Result Heap_ExtractMax(Heap* _heap, void** _data);

/*~~~~~~~~~~~~~~~~~~~ Heap_ItemsNum ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief get the number of items in an existing _heap.
 * @param[in] _heap - Heap to use.
 * @return number of items or -1 if _heap not initialized.
 */
int Heap_ItemsNum(Heap* _heap);

/*~~~~~~~~~~~~~~~~~~~~~~ Heap_ForEach ~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Iterate over all elements in the heap.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.  
 * @param[in] _heap - heao to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided context, will be sent to _action
 * @returns number of times the user functions was invoked
 * equivallent to:
 *      for(i = 1; i < Heap_ItemsNum(_heap); ++i){
 *             if(_action(elem, i, _context) == 0)
 *					break;	
 *      }
 *		return i;
 */
size_t Heap_ForEach(const Heap* _heap, HeapElementAction _action, void* _context);


#endif /*__GENERIC_HEAP_H__*/
