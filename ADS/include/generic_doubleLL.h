#ifndef __GENERIC_LIST_H__
#define __GENERIC_LIST_H__

/** 
 *  @file list.h
 *  @brief Create a Generic Double Linked List data type
 * 
 *  @details Implemented as double linked list using head and tail sentinels.
 *  Nodes are allocated from heap an store pointer to user proveded element.
 * 
 *  @author Author Ben Velt (ben.velt@gmail.com) 
 * 
 *  @bug No known bugs.
 */ 

#include <stddef.h>  /* size_t */

typedef struct List List;
typedef void (*ElementDestroy)(void* _item);

typedef enum List_Result {
	LIST_SUCCESS,
	LIST_UNINITIALIZED_ERROR,			/**< Uninitialized list 					 	*/
	LIST_ALLOCATION_ERROR,				/**< Node allocation failed due to heap error   */
	LIST_EMPTY_ERROR,
	LIST_NULL_INPUT,
	
	LIST_MAX_NUMBER_ERROR
} List_Result;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Dynamically create a list.
 * @returns a pointer to the created list.
 * @retval NULL on failure due to allocation failure
 */
List* List_Create(void);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Destroy list.
 * @details Destroys the _pList completely. optionally destroys elements using user provided function.
 * @params[in] _pList : A pointer to previously created List returned via List_Create. on completion *_pList will be null.
 * @params[in] _elementDestroy : A function pointer to be used to destroy elements inserted into the list or a null if no such destroy is required.
 */
void List_Destroy(List** _pList, ElementDestroy _elementDestroy);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PushHead ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Add element to head of list
 * @details time complexity: O(1).
 * @params[in] _list A previously created List via List_Create.
 * @params[in] _item An item to add to the list.
 * @returns success or error code.
 * @retval LIST_SUCCESS on success;
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized;
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure.
 */
List_Result List_PushHead(List* _list, void* _item);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PushTail ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Add element to tail of list
 * @details time complexity: O(1).
 * @params[in] _list A previously created List via List_Create.
 * @params[in] _item An item to add to the list.
 * @returns success or error code.
 * @retval LIST_SUCCESS on success;
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized;
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure.
 */
List_Result List_PushTail(List* _list, void* _item);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PopHead ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** @brief Remove element from list's head.
 *  @details if successfull, stores a pointer to the removed item in _item
 *  			time complexity O(1).
 * @params[in] _list : A previously created List via List_Create
 * @params[in] _pItem: To store a pointer to the removed item in
 * @returns success or error code.
 * @retval LIST_SUCCESS on success;
 * @retval LIST_NULL_INPUT if _pItem is null;
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized.
 */
List_Result List_PopHead(List* _list, void** _pItem);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PopTail ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** @brief Remove element from list's tail.
 *  @details if successfull, stores a pointer to the removed item in _item
 *  			time complexity O(1).
 * @params[in] _list : A previously created List via List_Create
 * @params[in] _pItem: To store a pointer to the removed item in
 * @returns success or error code.
 * @retval LIST_SUCCESS on success;
 * @retval LIST_NULL_INPUT if _pItem is null;
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized.
 */
List_Result List_PopTail(List* _list, void** _pItem);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_Size ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** @brief Get number of elements in the list
 * Average time complexity O(n).
 *
 * @params[in] _list : A previously created List ADT returned via ListCreate.
 * @returns _list ammount of elements.
 * @warning if _list is null function will return -1.
 */
int List_Size(const List* _list);


#endif /* __GENERIC_LIST_H__ */
