/********************************************************************************************************************************************
    Author :						Ben Velt
    Creation date :				26.06.18
    Date last modified :
    Description : 				BST create, destroy, insert, find and print.
********************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "generic_bst.h"

/*
#define IS_(T) (!((T)) || !((T))->m_root || ((T))->m_magic != MAGIC)
*/
#define TRUE 1
#define FALSE 0

#define SUPER_ROOT(T)		(&((T))->m_superRoot)
#define COMPARATOR(T)		(((T))->m_comparator)

#define SUPER_ROOT_FAMILY(T,I)		(SUPER_ROOT((T))->m_family[(I)])

#define LEFT			0
#define RIGHT		1
#define PARENT	2

#define DATA(N)				(N)->m_data
#define N_FAMILY(N)			(N)->m_family
	#define N_LEFT(TN)			(TN)->m_family[LEFT]
	#define N_RIGHT(TN)			(TN)->m_family[RIGHT]
	#define N_PARENT(TN)		(TN)->m_family[PARENT]

#define MAGIC 0xABBAABBA


typedef	struct	TreeNode TreeNode;


struct TreeNode
{
	void* m_data;
	TreeNode* m_family[3];
};

struct BSTree
{
	TreeNode m_superRoot;
	Comparator m_comparator;
};


/*~~~ STATIC FUNCTIONS DECLARATIONS ~~~*/
static TreeNode* BSTNodeCreate(TreeNode* _parent, void* _item, int _side);
static void* BSTNodeDestroy(TreeNode* _node);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ BSTree_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
BSTree* BSTree_Create(Comparator _comparator)
{
	BSTree* bstree = NULL;
	
	if(_comparator)
	{
		bstree = malloc(sizeof(BSTree));
		
		if(bstree)
		{
			DATA(SUPER_ROOT(bstree)) = (void*)MAGIC;
			SUPER_ROOT_FAMILY(bstree,PARENT) = NULL;
			SUPER_ROOT_FAMILY(bstree,LEFT) = NULL;
			SUPER_ROOT_FAMILY(bstree,RIGHT) = NULL;
			COMPARATOR(bstree) = _comparator;
		}
	}
	
	return bstree;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ BSTree_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Destroy tree
 * Destroys the tree, freeing the memory.
 * If supplied with non-NULL destroyer function, frees items in tree.
 * Average time complexity: O(1)..O(n) (depends on memory freeing)
 *
 * @params _tree : A previously created Tree ADT returned via BSTreeCreate
 * @params _destroyer : A function to destroy the data in the tree (may be NULL if unnecessary)
 */
void  BSTree_Destroy(BSTree** _tree, void (*_destroyer)(void*))
{
	TreeNode* currNode = (TreeNode*)BSTreeItr_Begin(*_tree);
	void* data = NULL;
	
	if(_tree && *_tree)
	{
		while(currNode)
		{
			data = BSTNodeDestroy(currNode->m_data);
			if(_destroyer) _destroyer(data);
			currNode = (TreeNode*)BSTreeItr_Next((BSTreeItr)currNode);
		}
		free(*_tree);
		_tree = NULL;
	}
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ BSTree_Insert ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* TODO create node should only allocate and init the node, connect its parent and thats it. the insert for which child will be done by BSTree_Insert */
BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	TreeNode* currNode = NULL;
	
	if(_tree && _item)
	{
		currNode = SUPER_ROOT(_tree);
		
		if(!_tree->m_superRoot.m_family[LEFT]/*SUPER_ROOT_FAMILY(_tree, LEFT)*/)
		{
			currNode = BSTNodeCreate(SUPER_ROOT(_tree), _item, LEFT);
			return (BSTreeItr)currNode;
		}
		else
		{
			currNode = N_LEFT(currNode);
			while(TRUE)
			{
				if(COMPARATOR(_tree)(_item, currNode->m_data))
				{
					if(!N_LEFT(currNode))
					{
						currNode = BSTNodeCreate(currNode, _item, LEFT);
						return (BSTreeItr)currNode;
					}
					currNode = N_LEFT(currNode);
				}
				else
				{
					if(!N_RIGHT(currNode))
					{
						currNode = BSTNodeCreate(currNode, _item, RIGHT);
						return (BSTreeItr)currNode;
					}
					currNode = N_RIGHT(currNode);
				}
			}
		}
	}
	return (BSTreeItr)currNode;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ BSTree_FindFirst ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Search the first element for which the given predicate returns 0
 * iterating using in-order manner over elements
 * O(k * n) where O(k) is the time complexity of the predicate
 *
 * @param _tree : A previously created Tree ADT returned via BSTreeCreate
 * @param _predicate : Predicate function
 * @param _params : Predicate parameters
 * @return an iterator pointing to the first data found, to end of tree if not found or NULL on NULL input
 */
 
 /*
BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
	
}
*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~ BSTreeItr_Begin ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Get an in-order itertator to the tree's begin 
 *
 * @param _tree : tree to create iterator from
 * @return an iterator pointing at the tree's begin or end if tree is empty 
 */
BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	TreeNode* currNode = NULL;
	
	if(_tree)
	{
		currNode = SUPER_ROOT_FAMILY(_tree,LEFT);
		
		if(!currNode)
		{
			return (BSTreeItr)SUPER_ROOT(_tree);
		}
		
		while(N_LEFT(currNode))
		{
			currNode = N_LEFT(currNode);
		}
	}
	return (BSTreeItr)currNode;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ BSTreeItr_Next ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
BSTreeItr BSTreeItr_Next(BSTreeItr _itr)
{
	TreeNode* node = (TreeNode*)_itr;
	TreeNode* nextNode = NULL;
	
	if(node)
	{
		if(N_RIGHT(node))
		{
			nextNode = node;
			while(N_LEFT(nextNode))
			{
				nextNode = N_LEFT(nextNode);
			}
		}
		else
		{
			nextNode = node;
			while(N_PARENT(nextNode))
			{
				nextNode = N_PARENT(nextNode);
				if(nextNode == N_LEFT(N_PARENT(nextNode)))
				{
					return (BSTreeItr)nextNode;
				}
			}
		}
	}
	return (BSTreeItr)nextNode;
}

/*~~~~~~~~~~~~~~~~BSTNodeCreate~~~~~~~~~~~~~~~~*/
static TreeNode* BSTNodeCreate(TreeNode* _parent, void* _item, int _side)
{
	TreeNode* node = NULL;
	
	node = malloc (sizeof (TreeNode));
	
	if(node)
	{
		N_LEFT(node) = NULL;
		N_RIGHT(node) = NULL;
		N_PARENT(node) = _parent;
		DATA(node) = _item;
		N_LEFT(_parent) = node;
	}
	
	return node;
}

/*~~~~~~~~~~~~~~~~BSTNodeDestroy~~~~~~~~~~~~~~~~*/
static void* BSTNodeDestroy(TreeNode* _node)
{
	void* data = _node->m_data;
	
	free(_node);
	
	return data;
}

















