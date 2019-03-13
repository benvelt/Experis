#include <stdio.h>
#include <stdlib.h>
#include "mu_test.h"
#include "bst.h"

#define ARRAY_LENGTH		14

typedef int Item;

const static int array[ARRAY_LENGTH] = {14,8,13,11,6,15,9,5,25,12,17,36,19,100};

UNIT(bst_create)
	BSTree* bstree = NULL;
	bstree = BSTCreate();
	ASSERT_THAT(bstree);
	BSTDestroy(bstree);
END_UNIT

UNIT(bst_destroy)
	BSTree* bstree = NULL;
	bstree = BSTCreate();
	BSTDestroy(bstree);
	bstree = NULL;
	BSTDestroy(bstree);
	ASSERT_THAT(!bstree);
	BSTDestroy(bstree);
END_UNIT

UNIT(bst_insert)
	BSTree* bstree = NULL;
	int i = 0;
	ADTErr err;
	bstree = BSTCreate();
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		err =  BSTInsert(bstree, array[i]);
		ASSERT_THAT(BST_ERR_OK == err);
	}
	BSTDestroy(bstree);
END_UNIT

UNIT(bst_find)
	BSTree* bstree = NULL;
	int i = 0;
	bstree = BSTCreate();
	for(i = 0; i < ARRAY_LENGTH; ++i)
	{
		BSTInsert(bstree, array[i]);
	}
	ASSERT_THAT(1 == BSTFind(bstree,100));
	ASSERT_THAT(0 == BSTFind(bstree,1000));
	BSTDestroy(bstree);
	ASSERT_THAT(-1 == BSTFind(bstree, 100));
END_UNIT

TEST_SUITE(bst container)
	TEST(bst_create)
	TEST(bst_destroy)
	TEST(bst_insert)
	TEST(bst_find)
END_SUITE

