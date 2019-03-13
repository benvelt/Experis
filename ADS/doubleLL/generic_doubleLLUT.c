#include <stdio.h>
#include <stdlib.h>

#include "mu_test.h"
#include "generic_doubleLL.h"
#include "generic_doubleLL_itr.h"

#define LENGTH 15

/*
 * DECLARATIONS OF VARIABLES *
*/
List* list=NULL;
int items[LENGTH] = {0};
int* itemsPtr[LENGTH] = {NULL};
int i = 0;
char charItems[LENGTH] = "abcdefghijklmn";
char* charItemsPtr[LENGTH] = {NULL};

/*
 * UNIT TESTS *
*/

/*~~~~~~~~~~~~~~ list_create ~~~~~~~~~~~~~~*/
UNIT(list_create)
	list = List_Create();
	ASSERT_THAT(list);
	
	List_Destroy (&list,NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_destroy ~~~~~~~~~~~~~~*/
UNIT(list_destroy)	
	list = List_Create();
	ASSERT_THAT(list);
	
	List_Destroy(&list,NULL);
	ASSERT_THAT(!list);
END_UNIT

/*~~~~~~~~~~~~~~ list_destroy_uninitialized ~~~~~~~~~~~~~~*/
UNIT(list_destroy_uninitialized)
	List_Destroy(&list,NULL);
	ASSERT_THAT(!list);
END_UNIT

/*~~~~~~~~~~~~~~ list_destroy_twice ~~~~~~~~~~~~~~*/
UNIT(list_destroy_twice)
	List_Destroy(&list,NULL);
	ASSERT_THAT(!list);
	
	List_Destroy(&list,NULL);
	ASSERT_THAT(!list);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_int_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_head_int_pointer)
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushHead(list, (void*)itemsPtr[i]));
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_int_pointer_uninitialized ~~~~~~~~~~~~~~*/
UNIT(list_push_head_int_pointer_uninitialized)
	list=NULL;
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_UNINITIALIZED_ERROR == List_PushHead(list, (void*)itemsPtr[i]));
	}
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_char_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_head_char_pointer)
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		charItems[i] = i;
		charItemsPtr[i] = &charItems[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushHead(list, (void*)charItemsPtr[i]));
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_char_pointer_uninitialized ~~~~~~~~~~~~~~*/
UNIT(list_push_head_char_pointer_uninitialized)
	list=NULL;
	
	for(i = 0; i < LENGTH; ++i)
	{
		charItems[i] = i;
		charItemsPtr[i] = &charItems[i];
		ASSERT_THAT(LIST_UNINITIALIZED_ERROR == List_PushHead(list, (void*)charItemsPtr[i]));
	}
END_UNIT

/*~~~~~~~~~~~~~~ list_push_tail_int_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_tail_int_pointer)
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i]));
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_tail_int_pointer_uninitialized ~~~~~~~~~~~~~~*/
UNIT(list_push_tail_int_pointer_uninitialized)
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_UNINITIALIZED_ERROR == List_PushTail(list, (void*)itemsPtr[i]));
	}
END_UNIT

/*~~~~~~~~~~~~~~ list_push_tail_char_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_tail_char_pointer)
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		charItems[i] = i;
		charItemsPtr[i] = &charItems[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)charItemsPtr[i]));
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_tail_char_pointer_uninitialized ~~~~~~~~~~~~~~*/
UNIT(list_push_tail_char_pointer_uninitialized)
	list=NULL;
	
	for(i = 0; i < LENGTH; ++i)
	{
		charItems[i] = i;
		charItemsPtr[i] = &charItems[i];
		ASSERT_THAT(LIST_UNINITIALIZED_ERROR == List_PushTail(list, (void*)charItemsPtr[i]));
	}
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_and_tail_int_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_head_and_tail_int_pointer)
	list = List_Create();
	
	for(i = 0; i < LENGTH / 2; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i]));
		items[i + 1] = i + 1;
		itemsPtr[i + 1] = &items[i + 1];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i + 1]));
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_and_push_tail_char_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_head_and_push_tail_char_pointer)
	list = List_Create();
	
	for(i = 0; i < LENGTH / 2; ++i)
	{
		charItems[i] = i;
		charItemsPtr[i] = &charItems[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)charItemsPtr[i]));
		charItems[i + 1] = i + 1;
		charItemsPtr[i + 1] = &charItems[i + 1];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)charItemsPtr[i + 1]));
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_and_pop_head_int_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_head_and_pop_head_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushHead(list, (void*)itemsPtr[i]));
	}
	
	for(i = LENGTH - 1; i >= 0; --i)
	{
		ASSERT_THAT(LIST_SUCCESS == List_PopHead(list, (void**)&pItem));
		ASSERT_THAT(itemsPtr[i] == pItem);
		ASSERT_THAT(*itemsPtr[i] == *pItem);
		ASSERT_THAT(items[i] == *pItem);
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_tail_and_pop_tail_int_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_tail_and_pop_tail_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i]));
	}
	
	for(i = LENGTH - 1; i >= 0; --i)
	{
		ASSERT_THAT(LIST_SUCCESS == List_PopTail(list, (void**)&pItem));
		ASSERT_THAT(itemsPtr[i] == pItem);
		ASSERT_THAT(*itemsPtr[i] == *pItem);
		ASSERT_THAT(items[i] == *pItem);
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_tail_and_pop_head_int_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_tail_and_pop_head_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i]));
	}
	
	for(i = 0; i < LENGTH; ++i)
	{
		ASSERT_THAT(LIST_SUCCESS == List_PopHead(list, (void**)&pItem));
		ASSERT_THAT(itemsPtr[i] == pItem);
		ASSERT_THAT(*itemsPtr[i] == *pItem);
		ASSERT_THAT(items[i] == *pItem);
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_push_head_and_pop_tail_int_pointer ~~~~~~~~~~~~~~*/
UNIT(list_push_head_and_pop_tail_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(LIST_SUCCESS == List_PushHead(list, (void*)itemsPtr[i]));
	}
	
	for(i = 0; i < LENGTH; ++i)
	{
		ASSERT_THAT(LIST_SUCCESS == List_PopTail(list, (void**)&pItem));
		ASSERT_THAT(itemsPtr[i] == pItem);
		ASSERT_THAT(*itemsPtr[i] == *pItem);
		ASSERT_THAT(items[i] == *pItem);
	}
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_size_push_head_and_pop_head ~~~~~~~~~~~~~~*/
UNIT(list_size_push_head_and_pop_head_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	ASSERT_THAT(!List_Size(list));
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(i == List_Size(list));
		ASSERT_THAT(LIST_SUCCESS == List_PushHead(list, (void*)itemsPtr[i]));
	}
	
	ASSERT_THAT(LIST_SUCCESS == List_PopHead(list, (void**)&pItem));
	ASSERT_THAT(i - 1 == List_Size(list));
	
	ASSERT_THAT(LIST_SUCCESS == List_PopHead(list, (void**)&pItem));
	ASSERT_THAT(i - 2 == List_Size(list));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_size_push_head_and_pop_tail ~~~~~~~~~~~~~~*/
UNIT(list_size_push_head_and_pop_tail_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	ASSERT_THAT(!List_Size(list));
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(i == List_Size(list));
		ASSERT_THAT(LIST_SUCCESS == List_PushHead(list, (void*)itemsPtr[i]));
	}
	
	ASSERT_THAT(LIST_SUCCESS == List_PopTail(list, (void**)&pItem));
	ASSERT_THAT(i - 1 == List_Size(list));
	
	ASSERT_THAT(LIST_SUCCESS == List_PopTail(list, (void**)&pItem));
	ASSERT_THAT(i - 2 == List_Size(list));
	
	List_Destroy(&list, NULL);
END_UNIT
/*~~~~~~~~~~~~~~ list_size_push_tail_and_pop_tail ~~~~~~~~~~~~~~*/
UNIT(list_size_push_tail_and_pop_tail_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	ASSERT_THAT(!List_Size(list));
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(i == List_Size(list));
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i]));
	}
	
	ASSERT_THAT(LIST_SUCCESS == List_PopTail(list, (void**)&pItem));
	ASSERT_THAT(i - 1 == List_Size(list));
	
	ASSERT_THAT(LIST_SUCCESS == List_PopTail(list, (void**)&pItem));
	ASSERT_THAT(i - 2 == List_Size(list));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_size_push_tail_and_pop_head ~~~~~~~~~~~~~~*/
UNIT(list_size_push_tail_and_pop_head_int_pointer)
	int* pItem = NULL;
	
	list = List_Create();
	
	ASSERT_THAT(!List_Size(list));
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(i == List_Size(list));
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i]));
	}
	
	ASSERT_THAT(LIST_SUCCESS == List_PopHead(list, (void**)&pItem));
	ASSERT_THAT(i - 1 == List_Size(list));
	
	ASSERT_THAT(LIST_SUCCESS == List_PopHead(list, (void**)&pItem));
	ASSERT_THAT(i - 2 == List_Size(list));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_size_uninitialized ~~~~~~~~~~~~~~*/
UNIT(list_size_uninitialized)
	list=NULL;
	
	ASSERT_THAT(-1 == List_Size(list));
END_UNIT

/*~~~~~~~~~~~~~~ list_size_empty ~~~~~~~~~~~~~~*/
UNIT(list_size_empty)
	list = List_Create();
	
	ASSERT_THAT(!List_Size(list));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ list_size_after_destroy ~~~~~~~~~~~~~~*/
UNIT(list_size_after_destroy)
	list = List_Create();
	
	ASSERT_THAT(!List_Size(list));
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		ASSERT_THAT(i == List_Size(list));
		ASSERT_THAT(LIST_SUCCESS == List_PushTail(list, (void*)itemsPtr[i]));
	}
	
	List_Destroy(&list, NULL);
	
	ASSERT_THAT(-1 == List_Size(list));
END_UNIT

/*~~~~~~~~~~~~~~ listitr_begin ~~~~~~~~~~~~~~*/
UNIT(listitr_begin)
	ListItr itrBegin = NULL;
	
	list = List_Create();
	
	ASSERT_THAT(!List_Size(list));
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrBegin = ListItr_Begin(list);
	
	ASSERT_THAT(itrBegin);
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_end ~~~~~~~~~~~~~~*/
UNIT(listitr_end)
	ListItr itrEnd = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrEnd = ListItr_End(list);
	
	ASSERT_THAT(itrEnd);
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_begin_equal ~~~~~~~~~~~~~~*/
UNIT(listitr_begin_equal)
	ListItr itrBegin1 = NULL;
	ListItr itrBegin2 = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrBegin1 = ListItr_Begin(list);
	ASSERT_THAT(itrBegin1 != itrBegin2);
	
	itrBegin2 = ListItr_Begin(list);
	ASSERT_THAT(itrBegin1 == itrBegin2);
	
	ASSERT_THAT(-1 != ListItr_Equals(itrBegin1, itrBegin2) && ListItr_Equals(itrBegin1, itrBegin2));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_end_equal ~~~~~~~~~~~~~~*/
UNIT(listitr_end_equal)
	ListItr itrEnd1 = NULL;
	ListItr itrEnd2 = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrEnd1 = ListItr_End(list);
	ASSERT_THAT(itrEnd1 != itrEnd2);
	
	itrEnd2 = ListItr_End(list);
	ASSERT_THAT(itrEnd1 == itrEnd2);
	
	ASSERT_THAT(-1 != ListItr_Equals(itrEnd1, itrEnd2) && ListItr_Equals(itrEnd1, itrEnd2));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_begin_and_end_unequal ~~~~~~~~~~~~~~*/
UNIT(listitr_begin_and_end_unequal)
	ListItr itrBegin = NULL;
	ListItr itrEnd = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrBegin = ListItr_Begin(list);
	ASSERT_THAT(itrBegin != itrEnd);
	
	itrEnd = ListItr_End(list);
	ASSERT_THAT(itrBegin != itrEnd);
	
	ASSERT_THAT(!ListItr_Equals(itrBegin, itrEnd));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_begin_end_equal_uninitialized ~~~~~~~~~~~~~~*/
UNIT(listitr_begin_end_equal_uninitialized)
	ListItr itrBegin = NULL;
	ListItr itrEnd = NULL;
	
	itrBegin = ListItr_Begin(list);
	ASSERT_THAT(!itrBegin);
	
	itrEnd = ListItr_End(list);
	ASSERT_THAT(!itrEnd);
	
	ASSERT_THAT(ListItr_Equals(itrBegin, itrEnd));
END_UNIT

/*~~~~~~~~~~~~~~ listitr_next ~~~~~~~~~~~~~~*/
UNIT(listitr_next)
	ListItr itrNext = NULL;
	ListItr itrBegin0 = NULL;
	ListItr itrBegin1 = NULL;
	
	list = List_Create();
	
	items[0] = 0;
	itemsPtr[0] = &items[0];
	List_PushHead(list, (void*)itemsPtr[0]);
	
	itrBegin0 = ListItr_Begin(list);
	
	items[1] = 1;
	itemsPtr[1] = &items[1];
	List_PushHead(list, (void*)itemsPtr[1]);
	
	itrBegin1 = ListItr_Begin(list);
	itrNext = ListItr_Next(itrBegin1);
	ASSERT_THAT(itrBegin0 != itrBegin1);
	ASSERT_THAT(itrBegin0 == itrNext);
	ASSERT_THAT(ListItr_Equals(itrBegin0, itrNext));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_next_uninitialized ~~~~~~~~~~~~~~*/
UNIT(listitr_next_uninitialized)
	ListItr itr = NULL;
	ListItr itrNext = NULL;
	
	itrNext = ListItr_Next(itr);
	ASSERT_THAT(!itrNext);
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_prev ~~~~~~~~~~~~~~*/
UNIT(listitr_prev)
	ListItr itrPrev = NULL;
	ListItr itrEnd0 = NULL;
	ListItr itrEnd1 = NULL;
	
	list = List_Create();
	
	items[0] = 0;
	itemsPtr[0] = &items[0];
	List_PushTail(list, (void*)itemsPtr[0]);
	
	itrEnd0 = ListItr_End(list);
	
	items[1] = 1;
	itemsPtr[1] = &items[1];
	List_PushTail(list, (void*)itemsPtr[1]);
	
	
	itrEnd1 = ListItr_End(list);
	itrPrev = ListItr_Prev(itrEnd1);
	ASSERT_THAT(itrEnd0 != itrEnd1);
	ASSERT_THAT(itrEnd0 == itrPrev);
	ASSERT_THAT(ListItr_Equals(itrEnd0, itrPrev));
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_prev_uninitialized ~~~~~~~~~~~~~~*/
UNIT(listitr_prev_uninitialized)
	ListItr itr = NULL;
	ListItr itrPrev = NULL;
	
	itrPrev = ListItr_Next(itr);
	ASSERT_THAT(!itrPrev);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_get ~~~~~~~~~~~~~~*/
UNIT(listitr_get)
	ListItr itrBegin = NULL;
	ListItr itrEnd = NULL;
	ListItr itrPrev = NULL;
	ListItr itrNext = NULL;
	int* itrData = NULL;
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrBegin = ListItr_Begin(list);
	itrNext = ListItr_Next(itrBegin);
	itrEnd = ListItr_End(list);
	itrPrev = ListItr_Prev(itrEnd);
	
	itrData = ListItr_Get(itrBegin);
	ASSERT_THAT(itrData == itemsPtr[LENGTH - 1]);
	itrData = ListItr_Get(itrNext);
	ASSERT_THAT(itrData == itemsPtr[LENGTH - 2]);
	itrData = ListItr_Get(itrEnd);
	ASSERT_THAT(itrData == itemsPtr[0]);
	itrData = ListItr_Get(itrPrev);
	ASSERT_THAT(itrData == itemsPtr[1]);
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_get_uninitialized ~~~~~~~~~~~~~~*/
UNIT(listitr_get_uninitialized)
	ListItr itr = NULL;
	int* itrData = NULL;

	itrData = ListItr_Get(itr);
	ASSERT_THAT(!itrData);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_set ~~~~~~~~~~~~~~*/
UNIT(listitr_set)
	ListItr itrBegin = NULL;
	ListItr itrNext = NULL;
	int* itrData[3] = {NULL};
	
	list = List_Create();
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrBegin = ListItr_Begin(list);
	itrNext = ListItr_Next(itrBegin);
	itrData[0] = ListItr_Get(itrBegin);
	itrData[1] = ListItr_Get(itrNext);
	ASSERT_THAT(itrBegin != itrNext);
	
	itrData[2] = ListItr_Set(itrBegin, itrData[1]);
	ASSERT_THAT(itrBegin != itrNext);
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_set_uninitialized ~~~~~~~~~~~~~~*/
UNIT(listitr_set_uninitialized)
	ListItr itr = NULL;
	int* itrDataGet = NULL;
	
	items[0] = LENGTH;
	itemsPtr[0] = &items[0];
	
	itrDataGet = ListItr_Set(itr, itemsPtr);
	
	ASSERT_THAT(!itrDataGet);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_set_null_item ~~~~~~~~~~~~~~*/
UNIT(listitr_set_null_item)
	ListItr itrBegin = NULL;
	int* itrDataGet = NULL;
	int* itrDataSet = NULL;
	
	list = List_Create();
	
	items[0] = LENGTH;
	itemsPtr[0] = &items[0];
	List_PushHead(list, (void*)itemsPtr[0]);
	
	itrBegin = ListItr_Begin(list);
	
	itrDataGet = ListItr_Set(itrBegin, itrDataSet);
	
	ASSERT_THAT(!itrDataGet);
	
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_insert_before ~~~~~~~~~~~~~~*/
UNIT(listitr_insert_before)
	ListItr itrBegin = NULL;
	ListItr itrNext = NULL;
	ListItr itrPrev = NULL;
	ListItr itrInsBfr = NULL;
	int element = LENGTH * LENGTH;
	int* elementP = &element;
	
	ASSERT_THAT(!elementP || !itrInsBfr);
	
	list = List_Create();
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	
	itrBegin = ListItr_Begin(list);
	itrNext = ListItr_Next(itrBegin);
	for(i = 0; i < 2; ++i, itrNext = ListItr_Next(itrNext));
	
	itrInsBfr = ListItr_InsertBefore(itrNext, (int*)elementP);
	itrPrev = ListItr_Prev(itrNext);
	ASSERT_THAT(itrPrev != itrNext);
	ASSERT_THAT( elementP == ListItr_Get(itrPrev));
	ASSERT_THAT(ListItr_Equals(itrInsBfr, itrPrev));
	List_Destroy(&list, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ listitr_remove ~~~~~~~~~~~~~~*/
UNIT(listitr_remove)
	ListItr itrBegin = NULL;
	ListItr itrNext = NULL;
	ListItr itrPrev = NULL;
	ListItr itrInsBfr = NULL;
	int element = LENGTH * LENGTH;
	int* elementP = &element;
	int sizeBef = 0;
	int sizeAft = 0;
	
	ASSERT_THAT(!elementP || !itrInsBfr);
	
	list = List_Create();
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		List_PushHead(list, (void*)itemsPtr[i]);
	}
	sizeBef = List_Size(list);
	
	itrBegin = ListItr_Begin(list);
	itrNext = ListItr_Next(itrBegin);
	for(i = 0; i < 2; ++i, itrNext = ListItr_Next(itrNext));
	
	sizeAft = List_Size(list);
	ASSERT_THAT(sizeBef == sizeAft);
	
	itrInsBfr = ListItr_InsertBefore(itrNext, (int*)elementP);
	
	sizeAft = List_Size(list);
	ASSERT_THAT(sizeBef == sizeAft - 1);
	
	itrPrev = ListItr_Prev(itrNext);
	ASSERT_THAT(itrPrev != itrNext);
	ASSERT_THAT( elementP == ListItr_Get(itrPrev));
	ASSERT_THAT(ListItr_Equals(itrInsBfr, itrPrev));
	ASSERT_THAT(elementP == ListItr_Remove(itrInsBfr));
	
	sizeAft = List_Size(list);
	ASSERT_THAT(sizeBef == sizeAft);
	
	ASSERT_THAT(itemsPtr[LENGTH - 3] == ListItr_Remove(ListItr_Prev(itrNext)));
	sizeAft = List_Size(list);
	
	ASSERT_THAT(sizeBef == sizeAft + 1);
	List_Destroy(&list, NULL);
END_UNIT


/*
 * TEST SUITE *
*/

TEST_SUITE(list container)
	TEST(list_create)
	
	TEST(list_destroy)
	TEST(list_destroy_uninitialized)
	TEST(list_destroy_twice)
	
	TEST(list_push_head_int_pointer)
	TEST(list_push_head_int_pointer_uninitialized)
	TEST(list_push_head_char_pointer)
	TEST(list_push_head_char_pointer_uninitialized)
	
	TEST(list_push_tail_int_pointer)
	TEST(list_push_tail_int_pointer_uninitialized)
	TEST(list_push_tail_char_pointer)
	TEST(list_push_tail_char_pointer_uninitialized)
	
	TEST(list_push_head_and_tail_int_pointer)
	TEST(list_push_head_and_push_tail_char_pointer)
	
	TEST(list_push_head_and_pop_head_int_pointer)
	TEST(list_push_tail_and_pop_tail_int_pointer)
	TEST(list_push_tail_and_pop_head_int_pointer)
	TEST(list_push_head_and_pop_tail_int_pointer)
	
	TEST(list_size_push_head_and_pop_head_int_pointer)
	TEST(list_size_push_head_and_pop_tail_int_pointer)
	TEST(list_size_push_tail_and_pop_tail_int_pointer)
	TEST(list_size_push_tail_and_pop_head_int_pointer)
	TEST(list_size_uninitialized)
	TEST(list_size_empty)
	TEST(list_size_after_destroy)
	
	TEST(listitr_begin)
	TEST(listitr_end)
	TEST(listitr_begin_equal)
	TEST(listitr_end_equal)
	TEST(listitr_begin_and_end_unequal)
	TEST(listitr_begin_end_equal_uninitialized)
	TEST(listitr_next)
	TEST(listitr_next_uninitialized)
	TEST(listitr_prev)
	TEST(listitr_prev_uninitialized)
	TEST(listitr_get)
	TEST(listitr_get_uninitialized)
	TEST(listitr_set)
	TEST(listitr_set_uninitialized)
	TEST(listitr_set_null_item)
	TEST(listitr_insert_before)
	TEST(listitr_remove)
END_SUITE
