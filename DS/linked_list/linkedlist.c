#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */

#include "linkedlist.h"

struct Person
{
	size_t		m_id;						/* Primary Key 	*/
	char			m_name[128];
	size_t		m_age;
	Person*	 	m_next;					/* head Pointer 	*/
};

Person* NewPerson (Person* _person, size_t _id, char* _name, size_t _age)
{
	_person = malloc (sizeof(Person));
	
	if (NULL == _person)
	{
		return NULL;
	}
	
	_person -> m_id = _id;
	strcpy (_person -> m_name, _name);
	_person -> m_age = _age;
	_person -> m_next = NULL;
	return _person;
}

Person* ListInsertHead (Person* _head, Person* _p)
{
	if (NULL == _p)
	{
		return NULL;
	}
	else 
	{
		if (NULL == _head)
		{
			_p -> m_next = NULL;
			return _p;
		}
		else 
		{
			_p -> m_next = _head;
			return _p;
		}
	}	
}


Person* ListRemoveHead (Person* _head, Person** _item)
{
	if (NULL == _head)
	{
		return NULL;
	}
	else
	{
		if (NULL != _item)
		{
			*_item = _head;
			return _head -> m_next;	
		}
		else 
		{
			return NULL;
		}
	}
}

Person* ListInsertByKey (Person* _head, int _key, Person* _p)
{
	Person* temp = NULL;

	if (NULL == _head)
	{
		if (NULL == _p)
		{
			return NULL;		
		}
		else
		{
			return _p;
		}
	}
	
	if (_head -> m_id < _p -> m_id)
	{
		_p -> m_next = _head;
		return _p;		
	}
	
	temp = _head;

	while (1)
	{
		if (NULL != temp -> m_next) 
		{
			if ((temp -> m_next -> m_id) < _p -> m_id)
			{
				_p -> m_next = (temp -> m_next);		
				temp -> m_next = _p;
				return _head;			
			}
		}
		else if (NULL == temp -> m_next)
		{
			temp -> m_next = _p;
			return _head;
		}
		temp = temp -> m_next;
	}
}

Person* LIstRemoveByKey (Person* _head, int _key, Person** _item)
{
	Person* temp = NULL;
	
	if (_head -> m_id == _key)
	{
		*_item = _head;
		_head = _head -> m_next;
		return _head;
	}
	
	temp = _head;
	
	while (1)
	{
		if (NULL != temp -> m_next) 
		{
			if ((temp -> m_next)-> m_id == _key)
			{
				*_item = temp -> m_next;
				temp -> m_next = temp -> m_next -> m_next;
				return _head;
			}
		}
		else 
		{
			return _head;
		}
		temp = temp -> m_next;
	}	
}

Person* ListInsertByKeyRec (Person* _head, int _key, Person* _p)
{
	Person* temp = NULL;
	
	if (NULL == _head)
	{
		return _head = _p;
	}
	
	if (NULL == _head -> m_next)
	{
		if (_head -> m_id > _p -> m_id)
		{
			_head -> m_next = _p;
			return _head;
		}
		else 
		{
			_p -> m_next = _head;
			return _p;
		}
	}
	
	if ((_head -> m_next -> m_id) < (_p -> m_id))
	{
		temp = _head -> m_next;
		_head -> m_next = _p;
		_p -> m_next = temp;
		return _head;
	}
	else
	{
		ListInsertByKeyRec (_head -> m_next, 1, _p);
	}
	return _head;
}

Person* LIstRemoveByRec (Person* _head, int _key, Person** _item)
{
	if (NULL == _head)
	{
		return _head = _p;
	}
	
	if (_head -> m_next -> m_id == _key)
	{
		_head = _head -> m_next;
		
		return
	}
	else
	{
		LIstRemoveByRec (_head -> m_next, _key, _item)
	}
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


















