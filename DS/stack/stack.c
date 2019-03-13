#include <stddef.h>			/* size_t */

#include "stack.h"
#include "vector.h"

/* stack creating */
	Stack*	StackCreate (size_t _size, size_t _blockSize) {
		return (Stack*) VectorCreate (_size, _blockSize);
	}
	
/* stack destroying */
	void	StackDestroy(Stack* _stack) {
		VectorDestroy ((Vector*) _stack);
	}

/* add item to the last place */
	ADTErr StackPush (Stack* _stack, int _item) {
		return VectorAdd ((Vector*) _stack, _item);
	}
	
/* get the last element and delete it */
	ADTErr StackPop (Stack* _stack, int* _item) {
		return VectorDelete ((Vector*) _stack, _item);		
	}
	
/* get the last element */
	ADTErr StackTop (Stack* _stack, int* _item) {
		int tempLoc = 0;
		
		tempLoc = VectorGetSize ((Vector*) _stack);
		
		return VectorGet ((Vector*) _stack, tempLoc, _item);
	}
	
/* check is stack is empty */
	int StackIsEmpty(Stack* _stack) {
		return IsVectorEmpty ((Vector*) _stack);
	}

/*  */
	void	StackPrint (Stack *_stack) {
		VectorPrint ((Vector*) _stack);
	}


