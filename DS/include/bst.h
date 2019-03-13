/********************************************************************************************************************************************
    Author :						Ben Velt
    Creation date :				26.06.18
    Date last modified :
    Description : 				BST create, destroy, insert, find and print.
********************************************************************************************************************************************/

#include "ADTDefs.h"

typedef	struct	BSTree				BSTree;


typedef enum 
{
	BSTREE_PRE_ORDER = 1,
	BSTREE_IN_ORDER,
	BSTREE_POST_ORDER
} BSTreeTraversal;

/* 	*	Description: 	creating the root.
	*	Input: 			
	*	Output: 		pointer to the root.
	*	Errors: 			NULL if no allocation				*/
BSTree* BSTCreate(void);

/* 	*	Description: 	dialocate _bstree.
	*	Input: 			_bstree type of BSTree*.
	*	Output			allocate and pointer to _bstree
	*	Errors: 			NULL if no allocation				*/
void BSTDestroy(BSTree* _bstree);

/* 	*	Description: 	add _data by rule (p>l && p>r).
	*	Input: 			BSTree* _bstree and int _data.
	*	Output: 		BST_ERR_NO_TREE when tree no initiated
							BST_ERR_NODE_ALLOCATION_FAILED when no more memory
							BST_ERR_OK when insert
	*	Errors: 				*/
ADTErr BSTInsert(BSTree* _bstree, int _data);

/* 	*	Description: 	boolean function to .know if _data appear at tree
	*	Input: 			1 if yes, 0 if no.
	*	Output: 						
	*	Errors: 			_*/
int BSTFind(BSTree* _bstree, int _data);

/* 	*	Description: 	creating head & tail of Doubly LL.
	*	Input: 			
	*	Output: 						
	*	Errors: 			NULL if no allocation				*/
void BSTPrint(BSTree* _bstree, BSTreeTraversal _option);

