# include <stdio.h>
# include <stdlib.h>

#include "heap.h"
#include "vector.h"
#include "ADTDefs.h"

#define MAGIC 0xDEADDEAB

#define PARENT_INDEX					i
#define LEFT_CHILD_INDEX			(2 * i)
#define RIGHT_CHILD_INDEX			(2 * i + 1)
#define LAST_PARENT_INDEX(H)	((H)->m_heapSize / 2)
#define IS_VALID(H)						((H) && ((H))->m_magic == MAGIC)

/* struct decleration */

struct Heap
{
	int			m_magic;
	Vector*		m_vec;
	size_t		m_heapSize;
};


/*~~~~~~~~~~~~~~~~~~~~~~ MAX HEAP SORT ~~~~~~~~~~~~~~~~~~~~~~*/
static void MaxHeapSort(Heap* _heap, int _index)
{
	int i = 0;
	int parent;
	int left;
	int right;
	
	i = _index;
	
	if(!IS_VALID(_heap)) return;
	
	while(i <= LAST_PARENT_INDEX(_heap))
	{
		VectorGet(_heap->m_vec, PARENT_INDEX,&parent);
		VectorGet(_heap->m_vec, LEFT_CHILD_INDEX,&left);
		VectorGet(_heap->m_vec, RIGHT_CHILD_INDEX,&right);
		
		if(parent < left)
		{
			VectorSet(_heap->m_vec, PARENT_INDEX, left);
			VectorSet(_heap->m_vec, LEFT_CHILD_INDEX, parent);
			parent=left;
		}
		
		if(parent < right)
		{
			VectorSet(_heap->m_vec, PARENT_INDEX, right);
			VectorSet(_heap->m_vec, RIGHT_CHILD_INDEX, parent);
			parent=right;
		}
		++i;
	}
	return;
}

/*~~~~~~~~~~~~~~~~~~~~~~ HEAPIFY ~~~~~~~~~~~~~~~~~~~~~~*/
static void Heapify (Heap* _heap, int _index)
{
	int i = _index;
	int left;
	int right;
	int parent;
	
	if(!IS_VALID(_heap)) return;
	
	if(_index > LAST_PARENT_INDEX(_heap)) return;
	
	VectorGet(_heap->m_vec, PARENT_INDEX, &parent);
	VectorGet(_heap->m_vec, LEFT_CHILD_INDEX, &left);
	VectorGet(_heap->m_vec, RIGHT_CHILD_INDEX, &right);
	
	if(parent < left || parent < right) MaxHeapSort(_heap, i);
	
	return;
}




/*~~~~~~~~~~~~~~~~~~~~~~ HEAP BUILD ~~~~~~~~~~~~~~~~~~~~~~*/
Heap* HeapBuild(Vector* _vector)
{
	Heap* heap;
	int i = 0;
	
	if(!_vector) return NULL;
	
	heap = (Heap*) malloc(sizeof(Heap));
	
	if(!heap) return heap;
	
	heap->m_magic = MAGIC;
	heap->m_vec = _vector;
	heap->m_heapSize = VectorGetSize (_vector);
	
	if(!heap->m_heapSize) return heap;
	
	for(i = LAST_PARENT_INDEX(heap); i > 0; --i)
	{
		Heapify(heap, i);
	}
	
	return heap;
}

/*~~~~~~~~~~~~~~~~~~~~~~ HEAP DESTROY ~~~~~~~~~~~~~~~~~~~~~~*/
void HeapDestroy(Heap* _heap)
{
	if(!IS_VALID(_heap)) return;
	
	_heap->m_magic = -1;
	free(_heap);
}

/*~~~~~~~~~~~~~~~~~~~~~~ HEAP INSERT ~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr HeapInsert(Heap* _heap, int _data)
{
	int i = 0;
	ADTErr err;
	
	if(!IS_VALID(_heap)) return HEAP_ERR_NOT_INITIALIZED;
	
	err = VectorAdd(_heap->m_vec, _data);
	
	if(ERR_NOT_INITIALIZED == err) return ERR_NOT_INITIALIZED;
	else if(ERR_REALLOCATION_FAILED == err) return HEAP_ERR_ROALLOCATION_FAILED;
	else if(ERR_OVERFLOW == err) return HEAP_ERR_OVERFLOW;
	
	_heap->m_heapSize = VectorGetSize (_heap->m_vec);
	
	for(i = LAST_PARENT_INDEX(_heap); i > 0; --i)
	{
		Heapify(_heap, i);
	}
	return ERR_OK;
}

/*~~~~~~~~~~~~~~~~~~~~~~ HEAP MAX ~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr HeapMax(Heap* _heap, int* _data)
{
	ADTErr err;
	int item = 0;
	
	if(!IS_VALID(_heap)) return HEAP_ERR_NOT_INITIALIZED;
	
	err = VectorGet(_heap->m_vec, 1, &item);  /* Index from 1 */
	
	if(ERR_NOT_INITIALIZED == err) return ERR_NOT_INITIALIZED;
	
	*_data = item;
	
	return ERR_OK;
}

/*~~~~~~~~~~~~~~~~~~~~~~ Heap Extract Max ~~~~~~~~~~~~~~~~~~~~~~*/
ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
	int i = 0;
	int item = 0;
	int lastElement = 0;
	
	if(!IS_VALID(_heap)) return HEAP_ERR_NOT_INITIALIZED;
	
	VectorGet(_heap->m_vec, 1, &item);  /* Index from 1 */
	*_data = item;
	
	VectorDelete(_heap->m_vec, &lastElement);
	
	VectorSet(_heap->m_vec, 1, lastElement);
	
	_heap->m_heapSize = VectorGetSize (_heap->m_vec);
	
	for(i = LAST_PARENT_INDEX(_heap); i > 0; --i)
	{
		Heapify(_heap, i);
	}
	printf("for it to work");
	return ERR_OK;
}

/*~~~~~~~~~~~~~~~~~~~ Heap Items Number ~~~~~~~~~~~~~~~~~~~~~~*/
int HeapItemsNum(Heap* _heap)
{
	if(!IS_VALID(_heap)) return -1;
	
	return VectorGetSize (_heap->m_vec);
}

/*~~~~~~~~~~~~~~~~~~~~~~ HEAP PRINT ~~~~~~~~~~~~~~~~~~~~~~*/
void HeapPrint(Heap* _heap)
{
	if(!IS_VALID(_heap)) return;
	
	VectorPrint (_heap->m_vec);
	
	return;
}









