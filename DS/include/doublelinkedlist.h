/********************************************************************************************************************************************
    Author :						Ben Velt
    Creation date :    		    17.06.18
    Date last modified :
    Description : 				Doubly Linked List creation, destruction, head/tail push/pop, is LL empty & how many elements
********************************************************************************************************************************************/

#ifndef		__LINKEDLIST_H__
#define		__LINKEDLIST_H__

#include "ADTDefs.h"		/* ADTErr */

typedef struct List List;

/*
typedef enum 
{
	DIR_PRINT_FORWARD 	=  0,	
	DIR_PRINT_BACKWARD 	= 1

}	e_ListDir;
*/


/* 	*	Description: 	creating head & tail of Doubly LL.
	*	Input: 			
	*	Output: 						
	*	Errors: 			NULL if no allocation				*/
List* ListCreate (void);

/* 	*	Description:	destruction of list
	*	Input: 				
	*	Output: 						
	*	Errors: 		*/
void ListDestroy (List* _list); 				

/* 	*	Description: 	insert element right after head	
	*	Input: 			
	*	Output: 						
	*	Errors: 			LINKED_LIST_ERR_NO_LIST	
							LINKED_LIST_ERR_NO_NODE
							ERR_OK if pushed					*/
ADTErr ListPushHead (List* _list, int _data);
 
/* 	*	Description: 	insert element right before tail	
	*	Input: 			
	*	Output: 						
	*	Errors: 			LINKED_LIST_ERR_NO_LIST	
							LINKED_LIST_ERR_NO_NODE
							ERR_OK if pushed					*/
ADTErr ListPushTail (List* _list, int _data);

/* 	*	Description: 	
	*	Input: 			
	*	Output: 						
	*	Errors: 		*/
ADTErr ListPopHead (List* _list, int *_data);
 
/* 	*	Description: 	
	*	Input: 			
	*	Output: 						
	*	Errors: 		*/
ADTErr ListPopTail (List* _list, int *_data);
 
/* 	*	Description: 	counts the ammount of elements in _list without head & tail
	*	Input: 			
	*	Output: 	ammount of items					
	*	Errors: 		-1 if no list			*/
int 	ListCountItems (List* _list);
 
/* 	*	Description: 	
	*	Input: 			
	*	Output: 						
	*	Errors: 		*/
int ListIsEmpty (List* _list);
	
/******************** 
	Unit Test
********************/
/* 	*	Description: 	
	*	Input: 			
	*	Output: 						
	*	Errors: 		*/
void ListPrint (List* _list, int _direction); 

/************************************ 
	Linked List Data Action
************************************/
/* 	*	Description: 	
	*	Input: 			
	*	Output: 						
	*	Errors: 		*/
int ListForEach (List* _list, int (*_action)(int*, int*), int* _context);


#endif





