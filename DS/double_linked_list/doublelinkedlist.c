#include <stdio.h>
#include <stdlib.h>

#include "doublelinkedlist.h"
#include "ADTDefs.h"

#define LIST_NOT_EXIST(L) (!((L)) || !((L))-> m_head . m_data || !((L))-> m_tail . m_data)

typedef struct Node Node;

struct Node
{
	int		m_data;
	Node*	m_next;
	Node	*	m_prev;
};

struct List
{
	Node		m_head;  
	Node		m_tail;
};


Node* CreateNode (int _data)
{
	Node* node = NULL;
	
	node = malloc (sizeof(Node));
	if (NULL == node)
	{
		return NULL;
	}
	
	node -> m_data = _data;
	node -> m_next = node -> m_prev = NULL;
	return node;
}


void DestroyNodes (List* _list)
{
	Node* curr = NULL;
	Node* next = NULL;
	
	if (LIST_NOT_EXIST(_list)) return;
	
	for (curr = _list -> m_head . m_next; curr != & _list -> m_tail; curr = curr -> m_next)
	{
		next = curr;
		free (curr);
		curr = next;
	}	
}


List* ListCreate (void)
{
	List* list = NULL;
	
	list = malloc (sizeof (List));
	if (!list)
	{
		return list;
	}

	list -> m_head 	. m_next = &list -> m_tail;
	list -> m_head 	. m_prev = NULL;
	list -> m_head 	. m_data = 1;
	
	list -> m_tail 	. m_next = NULL;
	list -> m_tail 	. m_prev = &list -> m_head;
	list -> m_tail 	. m_data = 1;
	
	return list;
}


void ListDestroy (List* _list)  				/* ------> free to all Nodes */
{
	if (LIST_NOT_EXIST(_list)) return;
	DestroyNodes (_list);
	_list -> m_head 	. m_data = 0;
	_list -> m_tail . m_data = 0;
	free (_list);
}
 

ADTErr ListPushHead (List* _list, int _data)
{
	Node* node = NULL;
	
	if (LIST_NOT_EXIST(_list)) return LINKED_LIST_ERR_NO_LIST;
	
	node = CreateNode (_data);
	if (!node) return LINKED_LIST_ERR_NO_NODE;
	/*TODO make func ADD Node */
	node	-> m_next = _list -> m_head . m_next;
	_list 	-> m_head . m_next -> m_prev 	= node;
	_list 	-> m_head	 . m_next 	= node;
	node	-> m_prev = &_list -> m_head;
	
	return ERR_OK;
	
}


ADTErr ListPushTail (List* _list, int _data)
{
	Node* node = NULL;
	
	if (LIST_NOT_EXIST(_list)) return LINKED_LIST_ERR_NO_LIST;
	
	node = CreateNode (_data);
	if (!node) return LINKED_LIST_ERR_NO_NODE;
	
	node -> m_prev = _list -> m_tail . m_prev;
	_list -> m_tail . m_prev -> m_next = node;
	_list -> m_tail . m_prev = node;
	node -> m_next = &_list -> m_tail;
	
	return ERR_OK;
}


ADTErr ListPopHead (List* _list, int *_data)
{	
	if (LIST_NOT_EXIST(_list)) return LINKED_LIST_ERR_NO_LIST;
	
	if (_list -> m_head . m_next == &_list -> m_tail) return LINKED_LIST_ERR_NO_NODE;
	
	*_data = _list -> m_head . m_next -> m_data;
/*	freeNode = */
	_list -> m_head . m_next -> m_next -> m_prev = & _list -> m_head;
	_list -> m_head . m_next =  _list -> m_head . m_next -> m_next;
	
	return ERR_OK;
}

 

ADTErr ListPopTail (List* _list, int *_data)
{
	if (LIST_NOT_EXIST(_list)) return LINKED_LIST_ERR_NO_LIST;
	
	if (_list -> m_tail . m_prev == &_list -> m_head) return LINKED_LIST_ERR_NO_NODE;
	
	*_data = _list -> m_tail . m_prev -> m_data;
	
	_list -> m_tail . m_prev -> m_prev -> m_next = & _list -> m_tail;
	_list -> m_tail . m_prev =  _list -> m_tail . m_prev -> m_prev;
	
	return ERR_OK;
}

 

int ListCountItems (List* _list)
{
	Node* curr = NULL;
	int counter = 0;
	
	if (LIST_NOT_EXIST(_list)) return -1;
	
	for (curr = _list -> m_head . m_next; curr != & _list -> m_tail; curr = curr -> m_next)
	{
		counter++;
	}
	
	return counter;
}



int ListIsEmpty (List* _list)
{
	if (LIST_NOT_EXIST(_list)) return -1;
	if (_list -> m_head . m_next == &_list -> m_tail) return 1;
	return 0;
}



void ListPrint (List* _list, int _direction)
{
	Node* p = NULL;
	if (LIST_NOT_EXIST(_list)) return;
	
	if (1 == _direction)
	{
		for (p = _list -> m_head . m_next; p != & _list -> m_tail; p = p -> m_next)
		{
			printf ("%d ", p -> m_data);
		}
	}
	else
	{
		for (p = _list -> m_tail . m_prev; p != & _list -> m_head; p = p -> m_prev)
		{
			printf ("%d ", p -> m_data);
		}
	}
}


int ListForEach (List* _list, int (*_action)(int*, int*), int* _context)
{
	int		counter		= 1;
	
	Node*	tempNode	= NULL;
	Node* 	tmp;
	
	if (LIST_NOT_EXIST(_list))	return -1;
	
	if (NULL == _action)			return -2;
	
	tempNode = _list->m_head.m_next;
	
	if (tempNode == & _list->m_tail) return 0;
	
	for (tmp = tempNode; tmp != & _list->m_tail; tmp = tmp->m_next)
	{
		if (_action(&tmp->m_data, _context))
		{
			return counter;
		}
		++counter;
	}
	
	return counter;
}

/*
int ListForEach (List* _list, int (*_action)(int* _item, int* _context), int* _context)
{
	int		counter		= 0;
	int		cond			= 666;
	Node*		tempNode	= NULL;
	int*		temp;
	if (LIST_NOT_EXIST(_list))				return -1;
	
	if (NULL == _action)						return -2;
	
	tempNode = _list->m_head . m_next;
	
	if (tempNode == & _list->m_tail)	return 0;
	
	temp = tempNode->m_data;
	
	while (cond)
	{
		cond = _action(temp, &_context);
		
		++counter;
		
		tempNode = tempNode->m_next;
		
		if(NULL == tempNode->m_next)
		{
			break;
		}
		else if (tempNode == & _list->m_tail)
		{
			break;
		}
	}
	
	return counter;
	
}



*/


