#include <stdio.h>
#include <stdlib.h>

#include "generic_doubleLL.h"
#include "generic_doubleLL_itr.h"

#define MAGIC 0xBEEFBEEF
#define LIST_EXIST(L) (((L)) && ((L))->m_head.m_data == (void*)MAGIC && ((L))->m_tail.m_data == (void*)MAGIC)
#define TO_HEAD 0
#define TO_TAIL 1

#define HEAD(L)				(((L))->m_head)
#define TAIL(L)					(((L))->m_tail)
#define LIST_FIRST(L)		(HEAD(L).m_next)
#define LIST_LAST(L)			(TAIL(L).m_prev)

/*internal structure */
typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
};

/*~~~ STATIC FUNCTIONS DECLARATIONS ~~~*/
static Node* CreateNode(List* _list, void* _data, int _where);
static void* DestroyNode(Node* _node);

/*~~~ __GENERIC_LIST_H__ ~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
List* List_Create(void)
{
	List* list = NULL;
	
	list = (List*)malloc(sizeof(List));
	
	if(!list)
	{
		return list;
	}
	
	HEAD(list).m_next = &list->m_tail;
	HEAD(list).m_prev = NULL;
	HEAD(list).m_data = (void*)MAGIC;
	
	TAIL(list).m_prev = &list->m_head;
	TAIL(list).m_next = NULL;
	TAIL(list).m_data = (void*)MAGIC;
	
	return list;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void List_Destroy(List* *_list, ElementDestroy _elementDestroy)
{
	Node* currNode = NULL;
	void* data = NULL;
	if(_list && *_list && (*_list)->m_head.m_data == (void*)MAGIC && (*_list)->m_tail.m_data == (void*)MAGIC)
	{
		(*_list)->m_head.m_data = (void*)-1;
		(*_list)->m_tail.m_data = (void*)-1;
		for(currNode = HEAD(*_list).m_next; currNode != &TAIL(*_list); currNode = currNode->m_next)
		{
			data = DestroyNode(currNode);
			if(_elementDestroy) _elementDestroy(data);
		}
		free(*_list);
		*_list = NULL;
	}
	return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PushHead ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
List_Result List_PushHead(List* _list, void* _item)
{
	if(!LIST_EXIST(_list))
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if(!_item)
	{
		return LIST_NULL_INPUT;
	}
	
	return (CreateNode(_list, _item, TO_HEAD)) ? LIST_SUCCESS : LIST_ALLOCATION_ERROR;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PushTail ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
List_Result List_PushTail(List* _list, void* _item)
{
	if(!LIST_EXIST(_list))
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	if(!_item)
	{
		return LIST_NULL_INPUT;
	}
	
	return (CreateNode(_list, _item, TO_TAIL)) ? LIST_SUCCESS : LIST_ALLOCATION_ERROR;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PopHead ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
List_Result List_PopHead(List* _list, void* *_pItem)
{
	if(!LIST_EXIST(_list) && !_pItem)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	
	*_pItem = DestroyNode(HEAD(_list).m_next);
	
	return LIST_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_PopTail ~~~~~~~~~~~~~~~~~~~~~~~~~~*/

List_Result List_PopTail(List* _list, void* *_pItem)
{
	if(!LIST_EXIST(_list) && !_pItem)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
	*_pItem = DestroyNode(TAIL(_list).m_prev);
	
	return LIST_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ List_Size ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int List_Size(const List* _list)
{
	size_t counter = 0;
	Node* currNode = NULL;
	
	if(!LIST_EXIST(_list))
	{
		return -1;
	}
	
	for(currNode = HEAD(_list).m_next; currNode != &TAIL(_list); currNode = currNode->m_next)
	{
		++counter;
	}
	return counter;
}

/*~~~ __LIST_ITERATORS_H__ ~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_Begin ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Get itertator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element or at the end if list is empty.
 * @return iterator pointing at the list's beginning
 */
ListItr ListItr_Begin(const List* _list)
{
	if(!LIST_EXIST(_list))
	{
		return NULL;
	}
	
	return (ListItr)LIST_FIRST(_list);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_End ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Get itertator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 */
ListItr ListItr_End(const List* _list)
{
	if(!LIST_EXIST(_list))
	{
		return NULL;
	}
	
	if(_list->m_head.m_next == &_list->m_head)
	{
		return (ListItr)&TAIL(_list);
	}
	return (ListItr)LIST_LAST(_list);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_Equals ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	return _a == _b;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_Next ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ListItr ListItr_Next(ListItr _itr)
{
	Node* itrNode = (Node*)_itr;
	
	return (ListItr)((itrNode) ? ((itrNode->m_next) ? itrNode->m_next : itrNode) : NULL);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_Prev ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ListItr ListItr_Prev(ListItr _itr)
{
	Node* itrNode = (Node*)_itr;
	
	return (ListItr)((itrNode) ? ((itrNode->m_prev->m_prev) ? itrNode->m_prev : itrNode) : NULL);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_Get ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void* ListItr_Get(ListItr _itr)
{
	Node* itrNode = (Node*)_itr;
	
	return ((itrNode) ? ((itrNode->m_next) ? itrNode->m_data : NULL) : NULL);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_Set ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 */
void* ListItr_Set(ListItr _itr, void* _element)
{
	Node* itrNode = (Node*)_itr;
	void* data = NULL;
	
	if(itrNode && _element)
	{
		data = itrNode->m_data;
		itrNode->m_data = _element;
	}
	return data;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_InsertBefore ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	Node* itrNode = (Node*)_itr;
	Node* elemNode = NULL;
	
	if(_itr && _element)
	{
		elemNode = malloc(sizeof(Node));
		if(elemNode)
		{
			elemNode->m_data = _element;
			elemNode->m_next = itrNode;
			elemNode->m_prev = itrNode->m_prev;
			itrNode->m_prev->m_next = elemNode;
			itrNode->m_prev = elemNode;
			return (ListItr)elemNode;
		}
	}
	return _itr;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ ListItr_Remove ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 */
void* ListItr_Remove(ListItr _itr)
{
	Node* itrNode = (Node*)_itr;
	
	return itrNode ? DestroyNode(itrNode) : NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ STATIC FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
CreateNode.
Note: in this function the _list always exist, so there is no tests.
*/
static Node* CreateNode(List* _list, void* _data, int _where)
{
	Node* newNode = NULL;
	newNode = (Node*)malloc(sizeof(Node));
	
	if(!newNode)
	{
		return NULL;
	}
	
	if(0 == _where) /* push to head */
	{
		newNode->m_next = HEAD(_list).m_next;
		newNode->m_prev = &HEAD(_list);
		newNode->m_data = _data;
		HEAD(_list).m_next->m_prev = newNode;
		HEAD(_list).m_next = newNode;
	}
	else if(1 == _where) /* push to tail */
	{
		newNode->m_prev = TAIL(_list).m_prev;
		newNode->m_next = &TAIL(_list);
		newNode->m_data = _data;
		TAIL(_list).m_prev->m_next = newNode;
		TAIL(_list).m_prev = newNode;
	}
	
	return newNode;
}

/*
DestroyNode.
Note: in this function the _list always exist, so there is no tests.
*/
static void* DestroyNode(Node* _node)
{
	void* data = _node->m_data;
	
	_node->m_prev->m_next = _node->m_next;
	_node->m_next->m_prev = _node->m_prev;
	
	free(_node);
	return data;
}


