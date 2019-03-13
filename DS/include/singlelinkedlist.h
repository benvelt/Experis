/**************************************************************************************************
    Author :			
    Creation date :      15.06.18
    Date last modified :
    Description : Linked List creation.
**************************************************************************************************/

#ifndef 		__LINKEDLIST_H__
#define	 	__LINKEDLIST_H__

#include <stdio.h>

typedef struct Person Person;

/******************** 
	List Insert
********************/

/* 	Description: 	creating _person Node;
	Input: 			
	Output: 		_person Node. _person -> m_next points to NULL.							
	Errors: 				*/
Person* NewPerson (size_t _id, char* _name, size_t m_age);

/* 	Description: 	makes _p new head to linked list.
	Input: 			_head of linked list, _p new Node.
	Output: 		if _head is NULL so _p is immediately returned as the new _head;
						if _head isn't NULL so _p points to _head data and returned as new _head;							
	Errors: 				*/
	
Person* ListInsertHead (Person* _head, Person* _p);

/* 	Description: 	insert in a sorted way (by primary key) to linked list.
	Input:			_key which the linked list is sorted by.
	Output: 		_head.
	Errors: 				*/
Person* ListInsertByKey (Person* _head, int _key, Person* _p);

/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
Person* ListInsertByKeyRec (Person* _head, int _key, Person* _p);



/******************** 
	List Remove
********************/

/* 	Description: 	removes _head of linked list.
	Input:  			Person* _head, Person* _p that will receive _head.
	Output: 		_head pointer if _head isn't NULL
	Errors: 				*/

Person* ListRemoveHead (Person* _head, Person** _item);

/* 	Description: 	removes Node from linked list by desired _key.
	Input:			_item that will contain the removed Node.
	Output: 		
	Errors: 				*/
Person* LIstRemoveByKey (Person* _head, int _key, Person** _item);


/* 	Description: 
	Input:
	Output: 
	Errors: 				*/
Person* ListRemoveByKeyRec (Person* _head, int _key, Person** _item);

	
/******************** 
	Unit-Test
********************/

/* 	Description: 	Prints _head list.
	Input:			
	Output: 
	Errors: 				*/
void ListPrint (Person* _head);

#endif





