/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			26.07.18
 * Date last modified :
 * Description : 			Heap build, destroy, insert, max, extract max, items num, for each functions.
******************************************************************************************************************/

# include <stdio.h>
# include <stdlib.h>

#include "generic_heap.h"

/*
 * macros definitions *
 */

#define MAGIC 0xDEADDEAB

#define HEAP_MGC(H)		((H))->m_magic
#define HEAP(H)			((H))->m_vec
#define HEAP_SZE(H)		((H))->m_heapSize
#define HEAP_FUNC(H)	((H))->m_compFunc

#define IS_VALID(H)					((H) && HEAP_MGC((H)) == MAGIC)

#define PARENT_INDEX				i
#define LEFT_CHILD_INDEX			(2 * i)
#define RIGHT_CHILD_INDEX			(2 * i + 1)
#define LAST_PARENT_INDEX(H)		((H)->m_heapSize / 2)

#define FIRST_INDEX	1

/*
 * structs & variables decleration *
 */
struct Heap
{
	int					m_magic;
	Vector*				m_vec;
	size_t				m_heapSize;
	HeapItemCompare		m_compFunc;
};

static const Heap_Result s_hStatConv[VECTOR_MAX_NUMBER_ERROR] = {
	HEAP_SUCCESS
	,HEAP_UNINITIALIZED_ERROR
	,HEAP_ALLOCATION_ERROR
	,HEAP_ALLOCATION_ERROR
	,HEAP_UNINITIALIZED_ERROR
	,HEAP_OVERFLOW_ERROR
	,HEAP_UNDERFLOW_ERROR
};

/*
 * static functions *
 */
static void Heapify(Heap* _heap);
static void HeapMaxSort(Heap* _heap, int _index);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap_Build ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Heap* Heap_Build(Vector* _vector, HeapItemCompare _func)
{
	Heap* heap;
	
	if(!_vector || !_func) return NULL;
	
	heap = (Heap*) malloc(sizeof(Heap));
	
	if(!heap) return heap;
	
	HEAP_MGC(heap) = MAGIC;
	HEAP(heap) = _vector;
	HEAP_SZE(heap) = Vector_Size(_vector);
	HEAP_FUNC(heap) = _func;
	
	if(!heap->m_heapSize) return heap;
	
	Heapify(heap);
	
	return heap;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Heap_Destroy(Heap* *_heap)
{
	if(_heap && IS_VALID(*_heap))
	{
		HEAP_MGC(*_heap) = -1;
		free(*_heap);
		*_heap = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap_Insert ~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Heap_Result Heap_Insert(Heap* _heap, void* _data)
{
	Vector_Result vectorRes;
	
	if(!IS_VALID(_heap) || !_data) return HEAP_UNINITIALIZED_ERROR;
	
	vectorRes = Vector_Append(HEAP(_heap), _data);
	
	if(VECTOR_SUCCESS != vectorRes) return s_hStatConv[vectorRes];
	
	HEAP_SZE(_heap) = Vector_Size(HEAP(_heap));
	
	Heapify(_heap);
	
	return s_hStatConv[vectorRes];
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap_Max ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Heap_Result Heap_Max(Heap* _heap, void** _data)
{
	void* item = NULL;
	Vector_Result vectorRes;
	
	if(!IS_VALID(_heap) || !_data) return HEAP_UNINITIALIZED_ERROR;
	
	vectorRes = Vector_Get(HEAP(_heap), FIRST_INDEX, &item);
	
	*_data = item;
	
	return s_hStatConv[vectorRes];
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap_ExtractMax ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Heap_Result Heap_ExtractMax(Heap* _heap, void** _data)
{
	void* item = 0;
	void* lastItem = 0;
	
	if(!IS_VALID(_heap) || !_data) return HEAP_UNINITIALIZED_ERROR;
	
	Vector_Get(HEAP(_heap), FIRST_INDEX, &item);
	
	*_data = item;
	
	if(VECTOR_UNDERFLOW_ERROR == Vector_Remove(HEAP(_heap), &lastItem)) return  s_hStatConv[VECTOR_UNDERFLOW_ERROR];
	Vector_Set(HEAP(_heap), FIRST_INDEX, lastItem);
	HEAP_SZE(_heap) = Vector_Size(HEAP(_heap));
	Heapify(_heap);
	
	return HEAP_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Heap_ItemsNum ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Heap_ItemsNum(Heap* _heap)
{
	return IS_VALID(_heap) ? Vector_Size(HEAP(_heap)) : -1;
}

/*~~~~~~~~~~~~~~~~~~~~~~ Heap_ForEach ~~~~~~~~~~~~~~~~~~~~~~*/
size_t Heap_ForEach(const Heap* _heap, HeapElementAction _action, void* _context)
{
	return _heap ? Vector_ForEach(HEAP(_heap), _action, _context) : -1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Heapify ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* parent > left && parent > right */
static void Heapify(Heap* _heap)
{
	int i = LAST_PARENT_INDEX(_heap);
	void *parent = NULL;
	void *left = NULL;
	void *right = NULL;
	
	while(0 < i)
	{
		Vector_Get(HEAP(_heap), PARENT_INDEX, &parent);
		Vector_Get(HEAP(_heap), LEFT_CHILD_INDEX, &left);
		if(RIGHT_CHILD_INDEX <= HEAP_SZE(_heap))
			Vector_Get(HEAP(_heap), RIGHT_CHILD_INDEX, &right);
		
		if(HEAP_FUNC(_heap)(parent,left) || (RIGHT_CHILD_INDEX <= HEAP_SZE(_heap) && HEAP_FUNC(_heap)(parent,right)))
			HeapMaxSort(_heap, i);
			
		--i;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static HeapMaxSort ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void HeapMaxSort(Heap* _heap, int _index)
{
	void* parent;
	void* left;
	void* right;
	int i = _index;
	
	while (i <= LAST_PARENT_INDEX(_heap))
	{
		Vector_Get(HEAP(_heap), PARENT_INDEX, &parent);
		Vector_Get(HEAP(_heap), LEFT_CHILD_INDEX, &left);
		
		if(HEAP_FUNC(_heap)(parent, left))
		{
			Vector_Set(HEAP(_heap), PARENT_INDEX, left);
			Vector_Set(HEAP(_heap), LEFT_CHILD_INDEX, parent);
			parent = left;
		}
		
		if(RIGHT_CHILD_INDEX <= (_heap->m_heapSize))
			Vector_Get(HEAP(_heap), RIGHT_CHILD_INDEX, &right);
		
		if(RIGHT_CHILD_INDEX <= HEAP_SZE(_heap) && HEAP_FUNC(_heap)(parent, right))
		{
			Vector_Set(HEAP(_heap), PARENT_INDEX, right);
			Vector_Set(HEAP(_heap), RIGHT_CHILD_INDEX, parent);
			parent = right;
		}
		++i;
	}
}



