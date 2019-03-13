#include <stdio.h>
#include <stdlib.h>

#include "ADTDefs.h"
#include "queuebylinkedlist.h"

int main()
{
	Queue* queue=NULL;
	int cont = 1;
	int option;
	int initialSize;
	int item;
	int result;

	while (cont) {
		
		printf ("----------------------------------------------------	\n");
		printf ("Please choose your option:						\n");
		printf ("1. Queue Create;										\n");
		printf ("2. Queue Destroy;										\n");
		printf ("3. Queue Insert;										\n");
		printf ("4. Queue Remove;										\n");
		printf ("5. Queue Is Empty;									\n");
		printf ("6. Queue Print;											\n");
		printf ("\nAny other number to stop program.		\n");
		scanf("%d", &option);
		printf ("----------------------------------------------------	\n");
		
		switch (option) {

			case 1:
				queue = ListCreate ()	;

				
				break;
			    if (queue != NULL)
			    {
					printf ("\tList Created\n\n");			
					printf("\n");
			    }

			    break;

			case 2:
				printf("\n");

			    QueueDestroy(queue);

			    if(queue==NULL)
			    {
					printf("Queue was destroyed successfully \n");
			    }
			    
			    printf("\n");
			    break;

			case 3:

			    printf("\n");

			    printf("Please enter the value you wish to insert:");


			    scanf("%d",&item);
			    printf("\n");
			    result=QueueInsert(queue,item);

			    if(result==ERR_OK)

			    {
		            printf("%d inserted successfully \n",item);
		            printf("\n");
			    }

			    if(result==ERR_NOT_INITIALIZED) 
			    {
					printf("Queue is not initialized \n");
					printf("\n");
				}

				if(result==ERR_OVERFLOW) 
				{
					printf("Queue is full \n");
					printf("\n");
				}

				    break;

			case 4:
				printf("\n");
			    result=QueueRemove(queue, &item);
			    if(result==ERR_OK)
			    {
					printf("%d removed succesfully \n",item);
			        printf("\n");
			    }

			    if(result==ERR_NOT_INITIALIZED) 
			    {
			        printf("Queue is not initialized \n");
					printf("\n");
			    }

			    if(result==ERR_UNDERFLOW) 
			    {
					printf("Queue is empty \n");
					printf("\n");
			    }

				    break;
			/*	    
			case 5:

			  result = QueueIsEmpty (queue);

			  if (result == 1) 
			  {
				printf("Queue is empty \n");
			  }

			  if (result==0) 
			  {
				printf("Queue is NOT empty \n");
			  }
			  if(result==-1) 
			  {
				printf("Queue is not initialized \n");
			  }


				    break;
				    
				    */
			case 6:
				
				QueuePrint (queue);

			    break;

			default: cont = 0;  break;

		}
	}
	return 0;
}

