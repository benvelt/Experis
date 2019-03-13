#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "doublylinkedlist.h"

int FindNum (int* a, int* b);

int main ()		
{
	int		cont			= 1;				/* trigger to stop while loop */
	int		option		= 0;				/* switch (option) */ 
	char		isDestroy;
	int		data			= 0;
	int temp = 0;
	ADTErr 	err;
	int		direction = 0; 
	List* 		list = NULL;

	while (cont) 
	{
		printf ("\n---------------------------------------------------	\n");
		printf ("\tPlease choose option:							 \n\n");
		printf ("1. List Create;    										\n");
		printf ("2. List Destroy;    										\n");
		printf ("3. List Push Head;										\n");
		printf ("4. List Push Tail;										\n");
		printf ("5. List Pop Head;										\n");
		printf ("6. List Pop Tail;											\n");
		printf ("7. Count Items ammount in List;				\n");
		printf ("8. Is List Empty;										\n");
		printf ("9. List Print;												\n");
		printf ("10. Find number;										\n");
		printf ("Any another number to end program.		\n");
		scanf ("%d", &option);
		printf ("---------------------------------------------------		\n");
		
		switch (option) 
		{

			case 1: 
				printf ("\tList Created\n\n");			
				list = ListCreate ()	;
				
				break;
				
			case 2: 
				printf ("\tList Destroy\n\n");			
				printf ("\nAre you sure? [y/n] ");
				getc (stdin);
				scanf ("%c", &isDestroy);
				
				if ('y' == isDestroy)
				{
					printf ("\n\tList Destroyed\n");			
					ListDestroy (list);				
				}
				
				break;
				
			case 3:  
				printf ("\tList Push Head\n\n");			
				printf ("Please enter data: ");
				scanf ("%d", &data);			
				err = ListPushHead (list, data);
			   
			   	if (LINKED_LIST_ERR_NO_LIST == err)
			   	{
			   		printf ("\nLINKED_LIST_ERR_NO_LIST\n");
			   		break;
			   	}
			   	else if (LINKED_LIST_ERR_NO_NODE == err)
			   	{
			   		printf ("\nLINKED_LIST_ERR_NO_NODE\n");
			   		break;			   	
			   	}

				printf ("\nERR_OK\n");
				break;
				
				
			case 4:  
				printf ("\tList Push Tail\n\n");			
				printf ("Please enter data: ");
				scanf ("%d", &data);			
				err = ListPushTail (list, data);
			   
			   	if (LINKED_LIST_ERR_NO_LIST == err)
			   	{
			   		printf ("\nLINKED_LIST_ERR_NO_LIST\n");
			   		break;
			   	}
			   	else if (LINKED_LIST_ERR_NO_NODE == err)
				{
					printf ("\nLINKED_LIST_ERR_NO_NODE\n");
					break;
				}

				printf ("\nERR_OK\n");
				break;
				
			case 5: 
				printf ("\tList Pop Head\n\n");			
				err = ListPopHead (list, &data);
				if (LINKED_LIST_ERR_NO_NODE == err)
				{
					printf ("\nLINKED_LIST_ERR_NO_NODE\n");
					break;
				}
				
				printf ("%d had been pop from head\n", data);
				break;
			
			case 6: 
				printf ("\tList Pop Tail\n\n");			
				err = ListPopTail (list, &data);
				if (LINKED_LIST_ERR_NO_NODE == err)
				{
					printf ("\nLINKED_LIST_ERR_NO_NODE\n");
					break;	
				}
				
				printf ("%d had been pop from tail\n", data);
				break;			
			
			case 7:  
				printf ("\tCount Items ammount in List\n\n");			
				data = ListCountItems (list);
				
				if (-1 == data) 
				{
					printf ("\n\tThere is no list\n");
					break;
				}
				
				printf ("\n\tThere is %d elements in list\n", data);
				break;

			case 8:  
				printf ("\t\nIs List Empty\n");
				data = ListIsEmpty (list);
				
				if (data) 
     			{
					printf ("\n\tlist is not empty\n");
     			}
     			else
     			{
					printf ("\n\tlist is empty\n");
     			}
     			
				break;
			
			case 9 :
				printf ("\tList Print\n\n");			
				printf ("Print forward (1) or backward (0)? ");
				scanf ("%d", &direction);
				
				while (1 != direction && 0 != direction)
				{
					printf ("\nWRONG NUMBER!!\n");
					printf ("Print forward (1) or backward (0)? ");
					scanf ("%d", &direction);
				}
				
				ListPrint (list, direction);
				break;
				
			case 10 :
				printf ("\tFind number\n\n");
				printf ("Please enter which number to find: ");
				scanf ("%d", &data);
				temp = ListForEach (list, FindNum, &data);
				printf("\nNumber %d is at Node %d",data ,temp);
				break;
				
			default:
				printf ("\tGoodbye user\n\n");			
				cont = 0;
				break;
		}
	}
	return 0;
}

int FindNum (int* a, int* b)
{
	return (*a == *b);
}







