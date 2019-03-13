/**************************************************************************************
    Author :
    Creation date :			26.6.18
    Date last modified :
    Description : ADT General definitions.
***************************************************************************************/
#ifndef __ADTDEFS_H__
#define __ADTDEFS_H__


#define TRUE  1
#define FALSE 0

typedef enum
{
    /* General ADT Errors */
    ERR_OK=0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_WRONG_INDEX,

    /* Vector Errors */

    /* Stack  Errors */
	QUEUE_ERR_GENERAL,
	QUEUE_ERR_TAIL_OVERFLOW,
	QUEUE_ERR_HEAD_OVERFLOW,
	QUEUE_ERR_NO_ITEM,
	
    /* Queue  Errors */

    /* LinkedList  Errors */
	LINKED_LIST_ERR_GENERAL,
	LINKED_LIST_ERR_NO_LIST,
	LINKED_LIST_ERR_NO_NODE,
	
    /* Tree Vector*/
	BST_ERR_OK,
	BST_ERR_NODE_INSERTED,
	BST_ERR_NO_TREE,
	BST_ERR_NODE_ALLOCATION_FAILED,
	BST_ERR_DATA_EXIST_ALREADY,
	BST_ERR_DATA_INSERT,
	
    /* Heap Vector*/
	HEAP_ERR_OK,
	HEAP_ERR_NOT_INITIALIZED,
	HEAP_ERR_ROALLOCATION_FAILED,
	HEAP_ERR_OVERFLOW,
	
    /* maximum number of error returned by ADT implementations */
    ERR_ADT_MAX
    
} ADTErr;

#endif /*__ADTDEFS_H__*/


