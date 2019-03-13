/********************************************************************************************************************************************
    Author :						Ben Velt
    Creation date :				26.06.18
    Date last modified :
    Description : 				BST create, destroy, insert, find and print.
********************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define MAGIC 0xDEADDEAD
#define IS_TREE_EXIST(T) (!((T)) || !((T))->m_root || ((T))->m_magic != MAGIC)

typedef	struct	BSTreeNode	BSTreeNode;

typedef	struct	BSTreeNode	BSTNode;
typedef	struct	BSTreeNode*	BSTNodeP;

struct BSTreeNode
{
	int						m_data;
	BSTreeNode*		m_left;
	BSTreeNode*		m_right;
	BSTreeNode*		m_parent;
};

struct BSTree
{
	int						m_magic;
	BSTreeNode*		m_root;
};

/*~~~~~~~~~~~~~~~~CREATE BSTREE~~~~~~~~~~~~~~~~*/
BSTree* BSTCreate(void)
{
	BSTree* bstree = NULL;
	
	bstree = malloc (sizeof (BSTree));
	
	if (!bstree) return NULL;
	
	bstree->m_root = NULL;
	bstree->m_magic = MAGIC;
	
	return bstree;
}

/*~~~~~~~~~~~~~~~~CREATE BST NODE~~~~~~~~~~~~~~~~*/
static BSTNodeP BSTNodeCreate(int _data)
{
	BSTNodeP node;
	
	node = malloc (sizeof (BSTNode));
	
	if (!node) return node;
	
	node->m_data = _data;
	node->m_left = NULL;
	node->m_right = NULL;
	node->m_parent = NULL;
	
	return node;
}

/*~~~~~~~~~~~~~~~~BST NODE INSERT~~~~~~~~~~~~~~~~*/
static BSTNodeP BSTNodeInsert(BSTNodeP _node, int _newData)
{
	BSTNodeP tempNode;
	
	if (_node->m_data == _newData)
	{
		return _node;
	}
	
	else if (_node->m_data > _newData)
	{
		if(!_node->m_left)
		{
			tempNode = BSTNodeCreate(_newData);
			if(!tempNode) return NULL;
			
			_node->m_left= tempNode;
			_node->m_left->m_parent = _node;
			return _node;
		}
		return BSTNodeInsert(_node->m_left, _newData);
	}
	else if (_node->m_data < _newData)
	{
		if(!_node->m_right)
		{
			tempNode = BSTNodeCreate(_newData);
			if(!tempNode) return NULL;
			
			_node->m_right= tempNode;
			_node->m_right->m_parent = _node;
			return _node;
		}
		
		return BSTNodeInsert(_node->m_right, _newData);
	}
	
	return _node;
}


/*~~~~~~~~~~~~~~~~BST INSERT~~~~~~~~~~~~~~~~*/
ADTErr BSTInsert(BSTree* _bstree, int _data)
{
	BSTNodeP node;
	
	if(!_bstree || _bstree->m_magic != MAGIC) return BST_ERR_NO_TREE;
	
	if(!_bstree->m_root) 
	{
		node = BSTNodeCreate(_data);
		
		if(!node) return BST_ERR_NODE_ALLOCATION_FAILED;
		
		_bstree->m_root = node;
	}
	else
	{
		BSTNodeInsert(_bstree->m_root, _data);
	}
	
	return BST_ERR_OK;
}

/*~~~~~~~~~~~~~~~~BST NODE DESTROY~~~~~~~~~~~~~~~~*/
static void BSTNodeDestroy(BSTNodeP _bstNode)
{
	if(_bstNode) return;
	
	BSTNodeDestroy(_bstNode->m_left);
	
	BSTNodeDestroy(_bstNode->m_right);
	
	free(_bstNode);
}

/*~~~~~~~~~~~~~~~~BST NODE FIND~~~~~~~~~~~~~~~~*/
static int BSTNodeFind(BSTNodeP _bstNode, int _data)
{
	int isDataFound = 0;
	
	if(!_bstNode) return -1;
	
	if(_data == _bstNode->m_data) return 1;
	
	if(_bstNode->m_data > _data)
	{
		if(!_bstNode->m_left) return 0;
		
		return BSTNodeFind(_bstNode->m_left, _data);
	}
	else if(_bstNode->m_data < _data)
	{
		if(!_bstNode->m_right) return 0;
		isDataFound = BSTNodeFind(_bstNode->m_right, _data);
		return isDataFound;
	}
	return isDataFound;
}

/*~~~~~~~~~~~~~~~~BST FIND~~~~~~~~~~~~~~~~*/
int BSTFind(BSTree* _bstree, int _data)
{
	if(IS_TREE_EXIST(_bstree)) return -1;
	
	return BSTNodeFind(_bstree->m_root, _data);
}

/*~~~~~~~~~~~~~~~~BST DESTROY~~~~~~~~~~~~~~~~*/
void BSTDestroy(BSTree* _bstree)
{
	if(IS_TREE_EXIST(_bstree)) return;
	
	BSTNodeDestroy(_bstree->m_root);
	
	_bstree->m_magic = 0;
	free(_bstree->m_root);
}


/*~~~~~~~~~~~~~~~~BST PRINT PRE OREDR~~~~~~~~~~~~~~~~*/
static void BSTPrintPreOrder(BSTNodeP _bstNode)
{
	if(!_bstNode) return;
	
	printf("%d ",_bstNode->m_data);
	
	BSTPrintPreOrder(_bstNode->m_left);
	
	BSTPrintPreOrder(_bstNode->m_right);
}

/*~~~~~~~~~~~~~~~~BST PRINT IN ORDER~~~~~~~~~~~~~~~~*/
static void BSTPrintInOrder(BSTNodeP _bstNode)
{
	if(!_bstNode) return;
	
	BSTPrintPreOrder(_bstNode->m_left);
	
	printf("%d ",_bstNode->m_data);
	
	BSTPrintPreOrder(_bstNode->m_right);
}

/*~~~~~~~~~~~~~~~~BST PRINT POST ORDER~~~~~~~~~~~~~~~~*/
static void BSTPrintPostOrder(BSTNodeP _bstNode)
{
	if(!_bstNode) return;
	
	BSTPrintPreOrder(_bstNode->m_left);
	
	BSTPrintPreOrder(_bstNode->m_right);
	
	printf("%d ",_bstNode->m_data);
}

/*~~~~~~~~~~~~~~~~BST PRINT~~~~~~~~~~~~~~~~*/
void BSTPrint(BSTree* _bstree, BSTreeTraversal _option)
{
	if(IS_TREE_EXIST(_bstree)) return;
	
	if (BSTREE_PRE_ORDER == _option)
	{
		BSTPrintPreOrder(_bstree->m_root);
	}
	else if (BSTREE_IN_ORDER == _option)
	{
		BSTPrintInOrder(_bstree->m_root);
	}
	else if (BSTREE_POST_ORDER == _option)
	{
		BSTPrintPostOrder(_bstree->m_root);
	}
}









