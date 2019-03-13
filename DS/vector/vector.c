#include <stdlib.h> /* malloc(), realloc(), free() */
#include <stdio.h> /* print() */
#include <stddef.h> /* size_t */
#include "vector.h"

#define VECTOR_MAGIC 0xBEEFBEEF
#define REALLOC_REDUCE_FACTOR 2

struct Vector
{
	size_t 	m_magic;					/* indicator of if free	 	*/	
	int*		m_items;  					/* vector of integers 		*/
	size_t 	m_size;						/* number of elements 	*/
	size_t 	m_capacity;				/* current capacity 		*/
	size_t 	m_extendSize;			/* 	size of growth			*/
	size_t 	m_initialSize;				/* minimum capacity	 	*/

};

/* vector creating. 
	1. if _initialSize equals zero, there is no allocation.
	2. if _initialSize and _extendSize equals zero so return ERR_NOT_INITIALIZED
	3.   */
	
	Vector*	VectorCreate (size_t _initialSize, size_t _extendSize) {
		Vector* structVector;
	
		if (0 == _initialSize && 0 == _extendSize) 
		{
			return NULL;
		}
	
		structVector = malloc (sizeof (Vector));
	
		if (structVector == NULL) 
		{
			return NULL;
		}
		
		structVector -> m_capacity = _initialSize;
		structVector -> m_extendSize = _extendSize;
		structVector -> m_initialSize = _initialSize;
		structVector -> m_size = 0;
		structVector -> m_magic = VECTOR_MAGIC;
		
		if (_initialSize != 0)
		{
			structVector -> m_items = malloc ((structVector -> m_capacity) * sizeof (int));
			if (structVector -> m_items == NULL) 
			{
				free (structVector);
				return NULL;	
			}
		} 
		else 
		{
			structVector -> m_items = NULL;
		} 
		
		return structVector;	
	}

/* m_items vector destroy */
	void VectorDestroy (Vector *_vector) {
		
		if (_vector != NULL) 
		{
			_vector -> m_magic = -1;
			free (_vector -> m_items);
			free(_vector);
		}
	}

/* adding int to m_items[i] */
	ADTErr VectorAdd(Vector *_vector, int _item)
	{
		int* tempAddress = NULL; 
		
		if (_vector == NULL || _vector -> m_magic != VECTOR_MAGIC) 
		{
			return ERR_NOT_INITIALIZED;		
		} 
		
		if (_vector -> m_size == _vector -> m_capacity) 
		{
			if (_vector -> m_extendSize != 0) 
			{
				tempAddress = realloc (_vector -> m_items, ((_vector -> m_capacity) +  (_vector -> m_extendSize)) * sizeof (int));
				if (tempAddress == NULL) 
				{
					return ERR_REALLOCATION_FAILED;
				} 
				else 
				{
					_vector -> m_items = tempAddress;
					_vector -> m_capacity = (_vector -> m_capacity) + (_vector -> m_extendSize);
					_vector -> m_items[_vector -> m_size] = _item;
					_vector -> m_size = (_vector -> m_size) + 1;
				}
			}
			else
			{
					return ERR_OVERFLOW;
			}
		} 
		else 
		{
			_vector -> m_items[_vector -> m_size] = _item;
			_vector -> m_size = (_vector -> m_size) + 1;

		}
		
		return ERR_OK;
	}

/* delete the m_items[m_size] element */
	ADTErr VectorDelete (Vector *_vector,  int* _item) {
		int tempCapacity = 0;
		
		int* tempAddress;
		
		if (_vector == NULL || _vector -> m_magic != VECTOR_MAGIC) 
		{
			return ERR_NOT_INITIALIZED;
		} 
		else if (_item == NULL) 
		{
			return ERR_GENERAL;
		}
		
		if (_vector -> m_size > 0)  							/* check if there is elements */
		{
			_vector -> m_size = _vector -> m_size - 1;
			*_item = _vector -> m_items[_vector -> m_size];
		}
		else
		{
			return ERR_UNDERFLOW;
		}
			
		if ((_vector -> m_capacity - _vector -> m_size == REALLOC_REDUCE_FACTOR * (_vector -> m_extendSize)))
		{
			if ((_vector -> m_capacity) > ((_vector -> m_initialSize + REALLOC_REDUCE_FACTOR * (_vector -> m_extendSize)))) 
			{
				tempCapacity = _vector -> m_capacity - REALLOC_REDUCE_FACTOR * (_vector -> m_extendSize);

				tempAddress = realloc (_vector -> m_items, tempCapacity * sizeof(int));
				if (tempAddress == NULL) 
				{
					return ERR_REALLOCATION_FAILED;
				} 
				else 
				{
					_vector -> m_items = tempAddress;
					_vector -> m_capacity = tempCapacity;
				}
			}
		}
			
		return ERR_OK;
	}

/* make pointer to the m_items[_index - 1] */
	ADTErr	VectorGet (Vector *_vector, size_t _index, int *_item) {  /* Index from 1 */
		
		if (_vector == NULL || _vector -> m_magic != VECTOR_MAGIC) 
		{
			return ERR_NOT_INITIALIZED;
		}
		
		if 
		(_item == NULL) {
			return ERR_NOT_INITIALIZED;
		} 
		
		if (_index > (_vector -> m_size)) 
		{
			return ERR_WRONG_INDEX;
		}
		else if (1 > _index)
		{
			return ERR_WRONG_INDEX;
		}
		
		*_item = _vector -> m_items[_index - 1];
		
		return ERR_OK;
	}

/* set int _item in m_items[_index - 1] */
	ADTErr	VectorSet (Vector *_vector, size_t _index, int  _item) {  /* Index from 1 */
		
		if (_vector == NULL || _vector -> m_magic != VECTOR_MAGIC) 
		{
			return ERR_NOT_INITIALIZED;
		} 
		
		if (_index > _vector->m_size) 
		{
			return ERR_WRONG_INDEX;
		}
		else if (_index < 1) 
		{
			return ERR_WRONG_INDEX;
		}
		
		_vector -> m_items[_index - 1] = _item;
		
		return ERR_OK;
	}

/* get the m_size */
	int VectorGetSize (Vector *_vector) {
		
		if (_vector == NULL || _vector -> m_magic != VECTOR_MAGIC) 
		{
			return -1;
		}

		if (_vector == NULL && _vector -> m_magic != VECTOR_MAGIC) 
		{
			return 0;
		}		 
		
		return _vector -> m_size;
	}
	
/* know if there is no m_size 
	if size == 0 so return 1
	if size > 0 so return 0*/
	
	int VectorIsEmpty (Vector *_vector) {
	
		if(_vector == NULL || _vector -> m_magic != VECTOR_MAGIC)
		{
			return -1;
		}
		
		if((_vector -> m_size) == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

/* print the _vector -> m_items[i] */	
	void	VectorPrint (Vector *_vector) {
		int i = 0;
		
		if (_vector == NULL || _vector -> m_magic != VECTOR_MAGIC) 
		{
			printf("NOT INITIALIZED\n");
			return;
		}
		
		for (i = 0; i < (_vector -> m_size); ++i) {
			printf("%d ", _vector -> m_items[i]);
		}
	}
	
void PrintData (Vector *_vector) {
		if (_vector == NULL || _vector -> m_magic != VECTOR_MAGIC) 
		{
			printf("NOT INITIALIZED\n");
		}
		
		printf ("\nsize is: %lu, capacity is: %lu, extend size is: %lu, initial size is: %lu", _vector -> m_size, _vector -> m_capacity, _vector -> m_extendSize, _vector -> m_initialSize);
	}
	
	
	
	
	
	
	
	
	
