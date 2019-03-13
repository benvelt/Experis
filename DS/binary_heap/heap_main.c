#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "ADTDefs.h"
#include "vector.h"
#include "heap.h"

int main()
{
	int cont = 1;
	int option = 0;
	int data = 0;
	Vector* vec = NULL;
	Heap* heap = NULL;
	int result;
	int i = 0;
	
	int array[]= {14,8,13,11,6,15,9,5,25,12,17,36,19,100};
	int arrayLength = sizeof(array) / sizeof(array[0]);
	printf("%d",arrayLength);
	
	while (cont)
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Choose option:		\n");
		printf("1: Create Vector		\n");
		printf("2: Insert Vector		\n");
		printf("3: Create Heap		\n");
		printf("4: Insert Heap		\n");
		printf("5: Print Vector		\n");
		printf("6: Print Heap			\n");
		printf("Any another number - stop \n");
		
		scanf("%d", &option);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		switch (option)
		{
			case 1 :
				vec=VectorCreate(10, 10);
				if(!vec)
				{
					printf("Vector couldnt be created\n");
				}
				else
				{
					printf("Vector has been created\n");
				}
				break;
				
			case 2 :
				for (i = 0; i < arrayLength; ++i)
				{
					result=VectorAdd(vec,array[i]);
				}
				
				if(result==ERR_NOT_INITIALIZED)
				{
					printf("The vector hasnt been initialized yet.\n");
				}
				else if(result==ERR_REALLOCATION_FAILED)
				{
					printf("There is no free memory to add.\n");
				}
				else if(result==ERR_OK)
				{
					printf("Vector has been built.\n");
				}
				break;
			case 3 :
				printf("Heap has been built.\n");
				heap = HeapBuild(vec);
				
				break;
			case 4 :
				printf("Please enter the number to insert: \n");
				scanf("%d", &data);
				HeapInsert(heap, data);
				
				break;
			case 5 :
				VectorPrint(vec);
				
				break;
			case 6 :
				HeapPrint(heap);
				break;
			default :
				cont = 0;
				break;
			}
	}
	
	return 0;
}
