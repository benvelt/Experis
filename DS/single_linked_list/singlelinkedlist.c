#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */

#include "singlylinkedlist.h"

struct Person
{
	size_t		m_id;						/* Primary Key 	*/
	size_t		m_age;
	char			m_name[128];
	Person*	 	m_next;					/* head Pointer 	*/
};

Person* NewPerson (size_t _id, char* _name, size_t _age)
{
	Person* person; 
	person = (Person*) malloc (sizeof  (Person));
	
	if (NULL == person)
	{
		return NULL;
	}
	 /* // 	TODO 
	//	if input is NULL, the size of _name if using strcpy */
	

	person -> m_id = _id;
	person -> m_age = _age;
	if (strlen(_name) <= 128) 
	{
		strcpy (person -> m_name, _name);
	}
	person -> m_next = NULL;
	
	return person;
}

Person* ListInsertHead (Person* _head, Person* _p)
{
	if (NULL == _p)
	{
		return _head; 
	}

	_p -> m_next = _head;

	return _p;
}


Person* ListRemoveHead (Person* _head, Person* *_pItem)
{
	if (!_head || !_pItem)  		/* De Morgan --> if (!(_head && _item)) */ 
	{
		return _head;
	}

	*_pItem = _head;
	
	return _head -> m_next;	
}

Person* ListInsertByKey (Person* _head, int _key, Person* _p)
{
	Person* prev = NULL;
	Person* curr = NULL;

	if (NULL == _p)
	{
		return _head;		
	}
	
	if (NULL == _head || _head -> m_id < _key) 
	{	
		/* list is empty OR insert before _head */
		_p -> m_next = _head;
		return _p; 
	}
	
	prev = curr = _head; 
	while (curr && curr -> m_id < _key)
	{
		prev = curr;
		curr = curr -> m_next;
	}
	
	prev -> m_next = _p;
	_p -> m_next = curr;
	
	return _head;
}

Person* LIstRemoveByKey (Person* _head, int _key, Person** _item)
{
	Person* prev = NULL;
	Person* curr = NULL;
	
	if (!_head || !_item)
	{
		return _head;
	}
	
	if (_head -> m_id == _key)
	{
		*_item = _head;
		return _head -> m_next;
	}
	
	prev = curr = _head; 
	while (curr && curr -> m_id == _key)
	{
		prev = curr;
		curr = curr -> m_next;
	}
	
	*_item = curr;
	prev -> m_next = (curr) ? curr -> m_next : curr;
	
	return _head;	
}



Person* ListInsertByKeyRec (Person* _head, int _key, Person* _p)
{	
	if (!_head)
	{
		return _p;
	}
	
	if (_head -> m_id < _key)
	{
		_p -> m_next =_head;
		return _p;
	}
	
	_head -> m_next = ListInsertByKeyRec (_head -> m_next, _key, _p);
	return _head;
}	
	
	
Person* ListRemoveByKeyRec (Person* _head, int _key, Person* *_pItem)
{
	if (!_head)
	{
		return _head;
	}
	
	if (_head -> m_id == _key)
	{
		*_pItem = _head;
		return _head -> m_next;
	}
	
	_head -> m_next = ListRemoveByKeyRec (_head -> m_next, _key, _pItem);
	return _head;
}


void ListPrint (Person* _head) 
{
	Person* temp = NULL;
	int i = 0;
		
	if (NULL == _head)
	{
		printf ("\nNothing to show\n");
		return;
	}
	
	temp = _head;
	
	for (i = 1; temp != NULL; ++i)
	{
		printf("Person %d\n\n\tID: %lu\n\tName: %s\tAge: %lu\n\n", i, temp -> m_id, temp -> m_name, temp -> m_age);
		temp = temp -> m_next;
	}
	
	return;
}


















