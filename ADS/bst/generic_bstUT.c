#include <stdio.h>
#include <stdlib.h>

#include "mu_test.h"
#include "generic_bst.h"

#define LENGTH 15

static int i = 0;
static int items[LENGTH] = {0};
static int* itemsPtr[LENGTH] = {NULL};
static int unsortItems[LENGTH] = {14,8,15,11,6,0,13,9,5,25,12,17,36,19,100};

/*
p *(int*)currNode->m_data
*/

/*
	* Comparator Functions:
	* typedef int (*Comparator)(void* _left, void* _right); *
*/
int IntPtrComparator(int* _data1, int* _data2)
{
	return *_data1 < *_data2;
}

/*
 * UNIT TESTS *
*/

/*~~~~~~~~~~~~~~ bstree_create ~~~~~~~~~~~~~~*/
UNIT(bstree_create)
	BSTree* bstree = NULL;
	
	bstree = BSTree_Create((Comparator)IntPtrComparator);
	
	ASSERT_THAT(bstree);
	
	BSTree_Destroy(&bstree, NULL);
END_UNIT

/*~~~~~~~~~~~~~~ bstree_insert ~~~~~~~~~~~~~~*/
UNIT(bstree_insert)
	BSTree* bstree = NULL;
	BSTreeItr itr = NULL;
	
	bstree = BSTree_Create((Comparator)IntPtrComparator);
	
	for(i = 0; i < LENGTH; ++i)
	{
		items[i] = i;
		itemsPtr[i] = &items[i];
		itr = BSTree_Insert(bstree, itemsPtr[i]);
		ASSERT_THAT(itr);
	}
	
	
END_UNIT

/*~~~~~~~~~~~~~~ bstreeitr_begin ~~~~~~~~~~~~~~*/
UNIT(bstreeitr_begin)
	BSTree* bstree = NULL;
	BSTreeItr itrFlag = NULL;
	BSTreeItr itrBegin = NULL;
	
	bstree = BSTree_Create((Comparator)IntPtrComparator);
	
	for(i = 0; i < LENGTH; ++i)
	{
		itemsPtr[i] = &unsortItems[i];
		if(0 != unsortItems[i])
		{
			BSTree_Insert(bstree, itemsPtr[i]);
		}
		else
		{
			itrFlag = BSTree_Insert(bstree, itemsPtr[i]);
		}
		/*
		(0 != unsortItems[i]) ? BSTree_Insert(bstree, itemsPtr[i]) : itrFlag = BSTree_Insert(bstree, itemsPtr[i]);
		*/
	}
	
	itrBegin = BSTreeItr_Begin(bstree);
	
	ASSERT_THAT(itrBegin == itrFlag);
	
	
END_UNIT

/*
 * TEST SUITE *
*/

TEST_SUITE(bst container)
	TEST(bstree_create)
	TEST(bstree_insert)
	TEST(bstreeitr_begin)
END_SUITE
