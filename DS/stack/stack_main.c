#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "stack.h"
#include "ADTDefs.h"

int main()
{
	Stack* stackPtr;
	int cont = 1;
	int option;
	int initialSize;
	int extendSize;
	int Item;
	int flag;

	while (cont) 
	{
		printf("\n---------------------------------------------------------\n");
		printf("\nPlease select the function you wish to use: 	\n");
		printf("1: Stack Create 												\n");
		printf("2: Stack Destroy 											\n");
		printf("3: Stack Push 												\n");
		printf("4: Stack Pop 													\n");
		printf("5: Stack Top 													\n");
		printf("6: Is Stack Empty  											\n");
		printf("Any another number - stop 							\n");
		scanf("%d", &option);
		printf("\n---------------------------------------------------------\n");
		
		switch (option) 
		{
			case 1:
				printf("\nPlease enter initial size: "		);
				scanf("%d",&initialSize);
				printf("\nPlease enter extend size: "		);
				scanf("%d",&extendSize);
				printf("\n										       ");
				stackPtr = StackCreate(initialSize, extendSize);

				break;
			
			case 2:
				StackDestroy(stackPtr);

				break;
			
			case 3:
				printf("Please enter the item you wish to add: ");
				scanf("%d",&Item);
				printf("\n										       ");
				StackPush(stackPtr,Item);

				break;
			
			case 4:
				StackPop(stackPtr,&Item);
				printf("The number **%d\n** 				" ,Item);
			
				break;
			
			case 5:
				StackTop(stackPtr, &Item);
				printf("The Top number is **%d\n** 	" ,Item);
			
				break;	
			
			case 6:

				flag = StackIsEmpty(stackPtr);
				if(1 == flag) 
				{
					printf("Stack is empty\n");
				} 
				else 
				{
					printf("The stack in not empty\n");
				}

				break;

			default: 
				cont = 0;  
			
				break;
		}
	}
	return 0;
}
