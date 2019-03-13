/********************************************************************************************************************************************
    Author :						Ben Velt
    Creation date :				26.06.18
    Date last modified :		
    Description : 				BST create, destroy, insert, find and print.
********************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define TRUE 1
#define FLASE 0

int main()
{
	int IsWhile = TRUE;
	int userData = 0;
	int option = 0;
	int isDataFound = 0;
	
	ADTErr err;
	BSTree* bstree = NULL;
	BSTreeTraversal printOrder = 1;
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	while(IsWhile)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	\n");
		printf("Please choose your option:			\n\n");
		printf("1. BST Create;						\n");
		printf("2. BST Insert;						\n");
		printf("3. BST Print;							\n");
		printf("4. BST Find Data;					\n");
		printf("5. BST Destroy;						\n");
		printf("Any other number to exit.		\n");
		scanf("%d", &option);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	\n");
		
		switch(option)
		{
			case 1 :
/*~~~~~~~~~~~~~~~~CREATE BSTREE~~~~~~~~~~~~~~~~*/
				bstree = BSTCreate( );
				
				bstree ? printf("\n\tBST has been created.\n\n") : printf("\n\tBST has not been created.\n\n");
				
				break;
			case 2:
/*~~~~~~~~~~~~~~~~BST INSERT~~~~~~~~~~~~~~~~*/
				printf("Please insert your data:			\n\n");
				scanf("%d", &userData);
				
				err = BSTInsert(bstree, userData);
				if(BST_ERR_NO_TREE == err)
					printf("\n\tBST_ERR_NO_TREE\n");
				else if (BST_ERR_NODE_ALLOCATION_FAILED == err)
					printf("\n\tBST_ERR_NODE_ALLOCATION_FAILED\n");
				else if (BST_ERR_OK == err)
					printf("\n\tBST_ERR_OK\n");
				
				break;
			case 3:
/*~~~~~~~~~~~~~~~~BST PRINT~~~~~~~~~~~~~~~~*/
				printf("Please choose print order:\n\n");
				printf("1. Print Pre Order;		\n");
				printf("2. Print In Order;		\n");
				printf("3. Print Post Order;	\n");
				scanf("%u",&printOrder);
				printf("\nBST elements is:\n\n\t");
				BSTPrint(bstree, printOrder);
				
				printf("\n\n");
				
				break;
			case 4 :
/*~~~~~~~~~~~~~~~~BST FIND DATA~~~~~~~~~~~~~~~~*/
				printf("Please enter which number to find:\n");
				scanf("%d",&userData);
				isDataFound = BSTFind(bstree, userData);
				
				if(-1 == isDataFound) printf("\n\tNo BST.\n");
				else if (1 == isDataFound) printf("\n\t%d exist in BST.\n",userData);
				else if (0 == isDataFound) printf("\n\t%d does not exist in BST.\n",userData);
				
				break;
			case 5 :
/*~~~~~~~~~~~~~~~~BST DESTROY~~~~~~~~~~~~~~~~*/
				BSTDestroy(bstree);
				printf("\n\tBST has been destroyed.\n");
				break;
			default :
				IsWhile = FALSE;
				
				break;
		}
	}
	return 0;
}








































