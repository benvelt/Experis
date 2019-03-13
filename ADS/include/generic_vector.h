/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			23.07.18
 * Date last modified :
 * Description : 			main program to check zlog4c file.
******************************************************************************************************************/


#ifndef __GENERIC_VECTOR_H__
#define __GENERIC_VECTOR_H__

/** 
 * @brief Create a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
 * 
 * @author Author MuhammadZ (muhammadz@experis.co.il) 
 */ 

#include <stddef.h>  /* size_t */

typedef struct Vector Vector;
typedef int(*VectorElementAction)(void* _element, size_t _index, void* _context);

typedef enum
{
	VECTOR_SUCCESS,
	VECTOR_UNINITIALIZED_ERROR,								/**< Uninitialized vector error */
	VECTOR_ALLOCATION_ERROR,								/**< alloc error on grow/shrink */
	VECTOR_REALLOCATION_ERROR,							/**< realloc error on grow/shrink */
	VECTOR_INDEX_OUT_OF_BOUNDS_ERROR,				/**< index exceeds the vector elements */
	VECTOR_OVERFLOW_ERROR,									/**< cannot allocate vector */
	VECTOR_UNDERFLOW_ERROR,								/**< when reaching index lower than 1 */

	VECTOR_MAX_NUMBER_ERROR
} Vector_Result;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Dynamically create a new vector object of given capacity and  
 * @param[in] _initialCapacity - initial capacity, number of elements that can be stored initially
 * @param[in] _blockSize - the vector will grow or shrink on demand by this size 
 * @return Vector * - on success / NULL on fail 
 *
 * @warning if _blockSize is 0 the vector will be of fixed size. 
 * @warning if both _initialCapacity and _blockSize are zero function will return NULL.
 */
Vector* Vector_Create(size_t _initialCapacity, size_t _blockSize);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Dynamically deallocate a previously allocated vector  
 * @param[in] _vector - Vector to be deallocated.
 * @params[in] _elementDestroy : A function pointer to be used to destroy all elements in the vector
 *             or a null if no such destroy is required
 * @return void
 */
void Vector_Destroy(Vector* *_vector, void (*_elementDestroy)(void* _item));

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Append ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Add an Item to the back of the Vector.  
 * @param[in] _vector - Vector to append integer to.
 * @param[in] _item - Item to add.
 * @return success or error code 
 * @retval VECTOR_SUCCESS on success;
 * @retval VECTOR_UNINITIALIZED_ERROR if _vector uninitialized;
 * @retval VECTOR_REALLOCATION_ERROR if _vector couldnt reallocate;
 * @retval VECTOR_OVERFLOW_ERROR if _blockSize is zero.
 */
Vector_Result Vector_Append(Vector* _vector, void* _item);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Remove ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Delete an Element from the back of the Vector.  
 * @param[in] _vector - Vector to delete integer from.
 * @param[out] _pValue - pointer to variable that will receive deleted item value
 * @return success or error code 
 * @retval VECTOR_SUCCESS on success;
 * @retval VECTOR_UNINITIALIZED_ERROR if _vector uninitialized;
 * @retval VECTOR_UNDERFLOW_ERROR if trying to remove when _vector is empty;
 * @retval VECTOR_REALLOCATION_ERROR when reallocation failed.
 */
Vector_Result Vector_Remove(Vector* _vector, void** _pValue);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Get ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Get value of item at specific index from the the Vector 
 * @param[in] _vector - Vector to use.
 * @param[in] _index - index of item to get value from. the index of first elemnt is 1
 * @param[out] _pValue - pointer to variable that will recieve the item's value.
 * @return success or error code 
 * @retval VECTOR_SUCCESS on success;
 * @retval VECTOR_UNINITIALIZED_ERROR if _vector uninitialized;
 * @retval VECTOR_INDEX_OUT_OF_BOUNDS_ERROR when _index does not exist at _vector;
 * @warning Index starts from 1.
 */
Vector_Result Vector_Get(const Vector* _vector, size_t _index, void** _pValue);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Set ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Set an item at specific index to a new value.
 * @param[in] _vector - Vector to use.
 * @param[in] _index - index of an existing item.
 * @param[in] _value - new value to set.
 * @return success or error code 
 * @retval VECTOR_SUCCESS on success;
 * @retval VECTOR_UNINITIALIZED_ERROR if _vector uninitialized;
 * @retval VECTOR_INDEX_OUT_OF_BOUNDS_ERROR when _index does not exist at _vector;
 * @warning Index starts from 1.
 * @warning Index starts from 1.
 */
Vector_Result Vector_Set(Vector* _vector, size_t _index, void*  _value);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Size ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Get the number of actual items currently in the vector.
 * @param[in] _vector - Vector to use.
 * @return  number of items on success, 0 if vector is empty or invalid.
 */
size_t Vector_Size(const Vector* _vector);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Capacity ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Get the current capacity of the  vector.
 * @param[in] _vector - Vector to use.
 * @return  capacity of vector on success, 0 if vector is empty or invalid.
 */
size_t Vector_Capacity(const Vector* _vector);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_ForEach ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**  
 * @brief Iterate over all elements in the vector.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.  
 * @param[in] _vector - vector to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided context, will be sent to _action
 * @returns number of times the user functions was invoked
 * equivallent to:
 *      for(i = 1; i < Vector_Size(v); ++i){
 *             Vector_Get(v, i, &elem);
 *             if(_action(elem, i, _context) == 0)
 *					break;	
 *      }
 *		return i;
 */
size_t Vector_ForEach(const Vector* _vector, VectorElementAction _action, void* _context);

#endif /* __GENERIC_VECTOR_H__ */

