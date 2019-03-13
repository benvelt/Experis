#include <stdlib.h>
#include <stdio.h>

#include "mu_test.h"
#include "generic_stack.h"
#include "color.h"

#define LENGTH 10

int item[LENGTH] = {0};
int* itemPtr[LENGTH] = {0};
int i = 0;
Stack* stack = NULL;
Stack_Result stcErr;

/*
UNIT TESTS
*/

/*~~~~~~~~~~~~~~ stack_create ~~~~~~~~~~~~~~*/
UNIT(stack_create)
	ASSERT_THAT(!stack);
	stack = Stack_Create();
	ASSERT_THAT(stack);
	
	Stack_Destroy(&stack, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ stack_destroy ~~~~~~~~~~~~~~*/
UNIT(stack_destroy)
	stack = Stack_Create();
	
	ASSERT_THAT(stack);
	Stack_Destroy(&stack, NULL);
	ASSERT_THAT(!stack);
END_UNIT

/*~~~~~~~~~~~~~~ stack_push ~~~~~~~~~~~~~~*/
UNIT(stack_push)
	stack = Stack_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		stcErr = Stack_Push(stack, (void*)itemPtr[i]);
		ASSERT_THAT(STACK_SUCCESS == stcErr);
	}
	
	Stack_Destroy(&stack, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ stack_push_uninitialized ~~~~~~~~~~~~~~*/
UNIT(stack_push_uninitialized)
	item[0] = 1;
	itemPtr[0] = &item[0];
	
	ASSERT_THAT(STACK_UNINITIALIZED_ERROR == Stack_Push(stack, (void*)itemPtr));
END_UNIT

/*~~~~~~~~~~~~~~ stack_push_null_element ~~~~~~~~~~~~~~*/
UNIT(stack_push_null_element)
	stack = Stack_Create();
	
	ASSERT_THAT(STACK_NULL_ELEMENT_ERROR == Stack_Push(stack, NULL));
END_UNIT

/*~~~~~~~~~~~~~~ stack_pop ~~~~~~~~~~~~~~*/
UNIT(stack_pop)
	int* pItem = NULL;
	stack = Stack_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		stcErr = Stack_Push(stack, (void*)i[itemPtr]);
		ASSERT_THAT(STACK_SUCCESS == Stack_Pop(stack, (void**)&pItem));
		ASSERT_THAT(pItem == itemPtr[i]);
		ASSERT_THAT(*pItem == *itemPtr[i]);
		ASSERT_THAT(*pItem == item[i]);
	}
	
	Stack_Destroy(&stack, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ stack_pop_uninitialized ~~~~~~~~~~~~~~*/
UNIT(stack_pop_uninitialized)
	int* pItem = NULL;
	
	stack = Stack_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		stcErr = Stack_Push(stack, (void*)i[itemPtr]);
		ASSERT_THAT(!pItem);
	}
	
	Stack_Destroy(&stack, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ stack_pop_underflow ~~~~~~~~~~~~~~*/
UNIT(stack_pop_underflow)
	int* pItem = NULL;
	
	stack = Stack_Create();
	
	ASSERT_THAT(STACK_UNDERFLOW_ERROR == Stack_Pop(stack, (void**)&pItem));
	
	ASSERT_THAT(!pItem);
	
	for(i = 0; i < LENGTH; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		stcErr = Stack_Push(stack, (void*)i[itemPtr]);
	}
	
	for(i = 0; i < LENGTH; ++i)
	{
		ASSERT_THAT(STACK_SUCCESS == Stack_Pop(stack, (void**)&pItem));
		ASSERT_THAT(pItem);
	}
	
	ASSERT_THAT(STACK_UNDERFLOW_ERROR == Stack_Pop(stack, (void**)&pItem));
	
	Stack_Destroy(&stack, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ stack_top ~~~~~~~~~~~~~~*/
UNIT(stack_top)
	int* pItem = NULL;
	
	stack = Stack_Create();
	
	ASSERT_THAT(STACK_UNDERFLOW_ERROR == Stack_Pop(stack, (void**)&pItem));
	
	for(i = 0; i < LENGTH; ++i)
	{
		item[i] = i;
		itemPtr[i] = &item[i];
		stcErr = Stack_Push(stack, (void*)i[itemPtr]);
	}
	
	ASSERT_THAT(STACK_SUCCESS == Stack_Top(stack, (void**)&pItem));
	ASSERT_THAT(pItem);
	
	Stack_Destroy(&stack, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ stack_top_uninitialized ~~~~~~~~~~~~~~*/
UNIT(stack_top_uninitialized)
	int* pItem = NULL;
	
	ASSERT_THAT(STACK_UNINITIALIZED_ERROR == Stack_Pop(stack, (void**)&pItem));
END_UNIT

/*~~~~~~~~~~~~~~ stack_top_empty ~~~~~~~~~~~~~~*/
UNIT(stack_top_empty)
	int* pItem = NULL;
	
	stack = Stack_Create();
	
	ASSERT_THAT(STACK_UNDERFLOW_ERROR == Stack_Pop(stack, (void**)&pItem));
	
	Stack_Destroy(&stack, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ stack_is_empty ~~~~~~~~~~~~~~*/
UNIT(stack_is_empty)
	stack = Stack_Create();
	
	ASSERT_THAT(Stack_IsEmpty(stack));
	
	Stack_Destroy(&stack, NULL);
END_UNIT


/**/


void DestroyInt(void* _item)
{
	free((int*)_item);
	_item = NULL;
}

UNIT(Creating_Stack)
	int i = 7;
	int* item=&i;
	Stack* stack = NULL;
	stack =  Stack_Create();
	
	ASSERT_THAT(stack);
	ASSERT_THAT(STACK_SUCCESS == Stack_Push(stack, item));
	Stack_Destroy(&stack,NULL);
END_UNIT

											/* YANIV TESTS */
/************************************************************************************/

UNIT(Destroying_Stack)
	int i = 7;
	int* item=&i;
	Stack* stack = NULL;
	puts(BOLDMAGENTA "\n\tYANIV TESTS" RESET);
	stack =  Stack_Create();
	Stack_Push(stack, item);
	
	ASSERT_THAT(stack);
	ASSERT_THAT(STACK_SUCCESS == Stack_Push(stack, item));
	Stack_Destroy(&stack,NULL);
	ASSERT_THAT(STACK_UNINITIALIZED_ERROR == Stack_Push(stack, item));
END_UNIT
/************************************************************************************/
UNIT(Push_Stack)
	int i = 7;
	int* item=&i;
	Stack* stack = NULL;
	stack =  Stack_Create();
	Stack_Push(stack, item);
	
	ASSERT_THAT(stack);
	ASSERT_THAT(STACK_SUCCESS == Stack_Push(stack, item));
END_UNIT
/************************************************************************************/
UNIT(Push_Stack_uninitilaized)
	int i = 7;
	int* item=&i;
	Stack* stack = NULL;

	ASSERT_THAT(STACK_UNINITIALIZED_ERROR == Stack_Push(stack, item));
	
END_UNIT
/************************************************************************************/

UNIT(Pop_Stack_uninitilaized)
	int i = 7;
	void* item=&i;
	Stack* stack = NULL;

	ASSERT_THAT(STACK_UNINITIALIZED_ERROR == Stack_Pop(stack, &item));
	
END_UNIT
/************************************************************************************/
UNIT(Pop_Stack)
	int i = 7;
	int* item=&i;
	Stack* stack = NULL;
	stack =  Stack_Create();
	Stack_Push(stack, item);
	
	ASSERT_THAT(STACK_SUCCESS == Stack_Pop(stack,(void**) &item));
	ASSERT_THAT(i == *item);
	
END_UNIT
/************************************************************************************/
UNIT(TopStack)
	int i = 7;
	int j = 8;
	int* item=&i;
	Stack* stack = NULL;
	stack =  Stack_Create();
	Stack_Push(stack, item);
	item = &j;
	Stack_Push(stack, item);
	
	ASSERT_THAT(STACK_SUCCESS == Stack_Top(stack,(void**)&item));
	ASSERT_THAT(j == *item);
		ASSERT_THAT(STACK_SUCCESS == Stack_Pop(stack,(void**) &item));
	ASSERT_THAT(STACK_SUCCESS == Stack_Top(stack,(void**)&item));
	ASSERT_THAT(i == *item);
END_UNIT
/************************************************************************************/

UNIT(EmptyStack)
	int i = 7;
	int j = 8;
	int* item=&i;
	Stack* stack = NULL;
	stack =  Stack_Create();
	ASSERT_THAT(1 == Stack_IsEmpty(stack));
	Stack_Push(stack, item);
	item = &j;
	Stack_Push(stack, item);
	
	ASSERT_THAT(0 == Stack_IsEmpty(stack));
END_UNIT
/************************************************************************************/

											/* YAIR TESTS */
/*~~~~~~~~~~~~~~ is stuck empty - yes ~~~~~~~~~~~~~~*/
UNIT(is_stuck_empty_yes)
	Stack* stack = NULL;
	int answer = 5;
	puts(BOLDMAGENTA "\n\tYAIR TESTS" RESET);

	stack = Stack_Create();    
	answer = Stack_IsEmpty( stack);
	ASSERT_THAT(answer == 1);
END_UNIT
/*~~~~~~~~~~~~~~ is stuck empty - no ~~~~~~~~~~~~~~*/
UNIT(is_stuck_empty_no)
    Stack* stack = NULL;
    int answer = 5;
    
    stack = Stack_Create(); 
    Stack_Push(stack, (void*)&answer);
    answer = Stack_IsEmpty( stack);
    ASSERT_THAT(answer == 0);
   
END_UNIT
/*~~~~~~~~~~~~~~ is stuck empty uninitialized ~~~~~~~~~~~~~~*/
UNIT(is_stuck_empty_uninitialized)
    Stack* stack = NULL;
    int answer = 5;
    

    answer = Stack_IsEmpty( stack);
    ASSERT_THAT(answer == 1);
   
END_UNIT

/*
TEST SUITE
*/

TEST_SUITE(generic stack container)
	TEST(stack_create)
	
	TEST(stack_destroy)
	
	TEST(stack_push)
	TEST(stack_push_uninitialized)
	TEST(stack_push_null_element)
	
	TEST(stack_pop)
	TEST(stack_pop_uninitialized)
	TEST(stack_pop_underflow)
	
	TEST(stack_top)
	TEST(stack_top_uninitialized)
	TEST(stack_top_empty)
	
	TEST(stack_is_empty)
	
	/* YANIV TESTS */
	TEST(Creating_Stack)
	TEST(Destroying_Stack)
	TEST(Push_Stack)
	TEST(Push_Stack_uninitilaized)
	TEST(Pop_Stack_uninitilaized)
	TEST(Pop_Stack)
	TEST(TopStack)
	TEST(EmptyStack)
	
	/* YAIR TESTS */
	TEST(is_stuck_empty_yes)
	TEST(is_stuck_empty_no)
	TEST(is_stuck_empty_uninitialized)
END_SUITE

