/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			23.07.18
 * Date last modified :
 * Description : 			main program to check zlog4c file.
******************************************************************************************************************/


#include <stdlib.h>  /* size_t */

#include "generic_vector.h"


#define MAGIC						0xBEEFBEEF
#define SIZE(V)						(((V))->m_size)
#define CAPACITY(V)					(((V))->m_capacity)
#define EXTEND(V)					(((V))->m_extendSize)
#define INITIAL(V)					(((V))->m_initialSize)
#define ITEMS(V)					(((V))->m_items)

#define RLC_RDC_FAC	2
#define IS_VALID(V)		((V) && ((V))->m_magic == MAGIC)

struct Vector
{
	size_t m_magic;				/* indicator of if free */
	size_t m_size;				/* number of elements */
	size_t m_capacity;			/* current capacity */
	size_t m_extendSize;		/* 	size of growth */
	size_t m_initialSize;		/* minimum capacity */
	void* *m_items;				/* vector of integers */
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* if _initialCapacity is zero so there is malloc of _blockSize */
Vector* Vector_Create(size_t _initialCapacity, size_t _blockSize)
{
	Vector* vector;
	
	if(!_initialCapacity && !_blockSize)
	{
		return NULL;
	}
	
	vector = malloc(sizeof(Vector));
	
	if(!vector)
	{
		return NULL;
	}
	
	vector->m_size = 0;
	vector->m_capacity = _initialCapacity;
	vector->m_extendSize = _blockSize;
	vector->m_initialSize = _initialCapacity;
	
	if(_initialCapacity)
	{
		vector->m_items = (void**)malloc(vector->m_capacity * sizeof(void*));
		if(!vector->m_items)
		{
			free (vector);
			return NULL;
		}
	}
	else
	{
		vector->m_items = (void**)malloc(vector->m_initialSize * sizeof(void*));
		if(!vector->m_items)
		{
			free (vector);
			return NULL;
		}
	}
	vector->m_magic = MAGIC;
	
	return vector;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Vector_Destroy(Vector* *_vector, void (*_elementDestroy)(void* _item))
{
	int i = 0;
	
	if(_vector && *_vector && (*_vector)->m_magic == MAGIC)
	{
		(*_vector)->m_magic = -1;
		if(_elementDestroy)
		{
			for(i = 0; i < (*_vector)->m_size; ++i)
			{
				_elementDestroy((*_vector)->m_items[i]);
			}
		}
		free((*_vector)->m_items);
		free(*_vector);
		*_vector = NULL;
	}
	return;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Append ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Vector_Result Vector_Append(Vector* _vector, void* _item)
{
	void* tempAddress = NULL; 
	
	if (!IS_VALID(_vector)) 
	{
		return VECTOR_UNINITIALIZED_ERROR;
	} 
	
	if(SIZE(_vector) == CAPACITY(_vector)) 
	{
		if(EXTEND(_vector))
		{
			tempAddress = (void**)realloc(ITEMS(_vector), (CAPACITY(_vector) + EXTEND(_vector)) * sizeof(void*));
			
			if(!tempAddress) 
			{
				return VECTOR_REALLOCATION_ERROR;
			}
			
			ITEMS(_vector) = tempAddress;
			CAPACITY(_vector) = CAPACITY(_vector) + EXTEND(_vector);
			ITEMS(_vector)[SIZE(_vector)] = _item;
		}
		else
		{
			return VECTOR_OVERFLOW_ERROR;
		}
	}
	else 
	{
		ITEMS(_vector)[SIZE(_vector)] = _item;
	}
	
	SIZE(_vector) += 1;
	return VECTOR_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Remove ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Vector_Result Vector_Remove(Vector* _vector, void* *_pValue)
{
	int tempCapacity = 0;
	void* tempAddress;
	
	if(!IS_VALID(_vector)) 
	{
		return VECTOR_UNINITIALIZED_ERROR;
	}
	
	if(!SIZE(_vector))
	{
		return VECTOR_UNDERFLOW_ERROR;
	}
	else
	{
		SIZE(_vector) -= 1;
		*_pValue = ITEMS(_vector)[SIZE(_vector)];
	}
	
	if(CAPACITY(_vector) ==SIZE(_vector) + RLC_RDC_FAC * EXTEND(_vector))
	{
		if(CAPACITY(_vector) > INITIAL(_vector) + RLC_RDC_FAC * EXTEND(_vector))
		{
			tempCapacity = CAPACITY(_vector) - RLC_RDC_FAC * EXTEND(_vector);
			tempAddress = (void**)realloc(ITEMS(_vector), tempCapacity * sizeof(void*));
			
			if(!tempAddress)
			{
				return VECTOR_REALLOCATION_ERROR;
			}
			
			ITEMS(_vector) = tempAddress;
			CAPACITY(_vector) = tempCapacity;
		}
	}
	
	return VECTOR_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Get ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Vector_Result Vector_Get(const Vector* _vector, size_t _index, void* *_pValue)
{
	if(!IS_VALID(_vector)) 
	{
		return VECTOR_UNINITIALIZED_ERROR;
	}
	
	if(SIZE(_vector) < _index || 1 > _index)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	
	*_pValue = ITEMS(_vector)[_index - 1];
	
	return VECTOR_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Set ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Vector_Result Vector_Set(Vector* _vector, size_t _index, void* _value)
{
	if(!IS_VALID(_vector)) 
	{
		return VECTOR_UNINITIALIZED_ERROR;
	}
	
	if(SIZE(_vector) < _index)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	else if (1 > _index)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	
	ITEMS(_vector)[_index - 1] = _value;
	
	return VECTOR_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Size ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
size_t Vector_Size(const Vector* _vector)
{
	return (!IS_VALID(_vector)) ? 0 : SIZE(_vector);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_Capacity ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
size_t Vector_Capacity(const Vector* _vector)
{
	return (!IS_VALID(_vector)) ? 0 : CAPACITY(_vector);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Vector_ForEach ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
size_t Vector_ForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	int i = 0;
	void* elem = NULL;
	
	if(!IS_VALID(_vector) || !_action)
	{
		return 0;
	}
	
	for(i = 1; i <= Vector_Size(_vector); ++i)
	{
		Vector_Get(_vector, i, &elem);
		if(_action(elem, i, _context) == 0) 	break;
	}
	
	return i - 1;
}


