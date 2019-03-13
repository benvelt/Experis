/**************************************************************************************
    Author :             Dudi Kahana
    Creation date :      1.9.10
    Date last modified : 24.6.12
    Description : Stack Implementation. Using dynamic vector ADT.
***************************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include "vector.h"

typedef struct Stack Stack;

/* size      - The initial allocation size.
   blockSize - The extention block size.    */
Stack*		StackCreate (size_t _size, size_t _blockSize);
void			StackDestroy(Stack* _stack);
ADTErr		StackPush   (Stack* _stack, int  _item);
ADTErr		StackPop    (Stack* _stack, int* _item);
ADTErr		StackTop    (Stack* _stack, int* _item);
int			StackIsEmpty(Stack* _stack);

/*  Unit-Test functions  */
void			StackPrint   (Stack *_stack);

#endif /*__STACK_H__*/
