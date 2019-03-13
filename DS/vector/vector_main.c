#include <stdio.h>


#include "vector.h"

int main () {
	
	Vector* vector = NULL;

	int cont = 1; 									/* condition for interactive test */
	size_t option 		= 	0;

	size_t initialSize 	= 	0;
	size_t extendSize	= 	0;
	size_t isDestroy 	=	0;
	
	int item = 0;
	int index = 0;
	int noe = 0;
	int isEmpty = 10;	
	
	ADTErr errType;
	
	while (cont) {
		printf ("----------------------------------------------------	\n");
		printf ("Please choose your option:						\n");
		printf ("1. Create Vector;										\n");
		printf ("2. Destroy Vector;										\n");
	 	printf ("3. Add element to Vector;							\n");
		printf ("4. Delete last element of Vector;				\n");
		printf ("5. Get the i-th element of Vector;				\n");
		printf ("6. Set the i-th element of Vector;				\n");
		printf ("7. Get the element ammout in Vector;		\n");
		printf ("8. Know if Vector is empty;						\n");
		printf ("9. Print the Vector elements;						\n");
		printf ("\nAny other number to stop program.		\n");
		scanf("%lu", &option);
		printf ("----------------------------------------------------	\n");
		
		switch (option) 
		{
			case 1 :
				printf ("\tCreate Vector								\n");			
				printf ("Please enter your initial size:  "			);
				scanf("%lu", &initialSize);
				printf ("\nPlease enter your extend size:  "	);
				scanf("%lu", &extendSize);
				vector = VectorCreate (initialSize, extendSize);
				
				if (vector != NULL) 
				{
					PrintData (vector);
				}
				printf("\n");	
				break;
			
			case 2 :
				printf ("\tDestroy Vector   \n");			
				isDestroy = 0;
				printf ("Are you sure you want to destroy Vector?		\n");
				printf ("1. yes;\n2. No.												\n");
				scanf ("%lu", &isDestroy);	
				printf ("																		\n");
				
				if (isDestroy == 1) 
				{
					VectorDestroy (vector);
					/*TODO if not created so dont print */
					/* PrintData (vector); */
					printf("\n");
					break;
				} 
				else if (isDestroy == 2) 
				{
					break;
				}
				else 
				{
					printf ("wrong number.											\n");
					break;
				}
					
			case 3 :
				printf ("\tAdd element to Vector   				\n");			
				printf ("Please enter your initial size:  "			);
				scanf ("%d", &item);	
				
				errType = VectorAdd (vector, item);
				
				if (errType == ERR_NOT_INITIALIZED) 
				{
					printf ("\nERR_NOT_INITIALIZED\n");
				} 
				else if (errType == ERR_REALLOCATION_FAILED) 
				{
					printf ("\nERR_REALLOCATION_FAILED\n");
				}	
				else if (errType == ERR_OK) 
				{
					printf ("\nERR_OK\n");
				}
								
				PrintData (vector);
				printf("\n");
				break;
				
			case 4 :
				printf ("\tDelete last element of Vector      \n");
				errType = VectorDelete (vector, &item);
				
				if (ERR_NOT_INITIALIZED == errType)
				{
					printf ("\nERR_NOT_INITIALIZED");					
				} 
				else if (ERR_GENERAL == errType) 
				{
					printf ("\nERR_GENERAL");										
				} 
				else if (ERR_REALLOCATION_FAILED == errType) 
				{
					printf ("\nERR_REALLOCATION_FAILED");															
				} 
				else if (ERR_OK == errType) 
				{
					printf ("\nERR_OK");															
				}
								
				PrintData (vector);
				printf("\n");
				break;		
				
			case 5 :
				printf ("\tGet the i-th element of Vector     	\n");
				printf ("\nPlease enter the index:  "					);				
				scanf ("%d", &index);
				
				errType = VectorGet (vector, index, &item);
				if (ERR_NOT_INITIALIZED == errType) 
				{
					printf ("\nERR_NOT_INITIALIZED");										
				} 
				else if (ERR_OVERFLOW == errType) 
				{
					printf ("\nERR_OVERFLOW");	
					break;									
				} 
				else if (ERR_OK == errType) 
				{
						printf ("\nERR_OK");										
				}
				
				printf ("\nThe element value is: %d\n", item);
				PrintData (vector);	
				printf("\n");
				break;		
				
			case 6 :
				printf ("\tSet the i-th element of Vector    	\n");
				printf ("Please insert the item value:		   	\n");
				scanf ("%d", &item);
				printf ("Please insert the index:		     		\n");
				scanf ("%d", &index);
				
				errType = VectorSet (vector, index, item);  
				
				if (ERR_NOT_INITIALIZED == errType) 
				{
					printf ("\nERR_NOT_INITIALIZED");										
				} 
				else if (ERR_OVERFLOW == errType) 
				{
					printf ("\nERR_OVERFLOW");										
				} 
				else if (ERR_OK == errType) 
				{
					printf ("\nERR_OK");										
				}

				PrintData (vector);						
				printf("\n");
				break;		
				
			case 7 :
				printf ("\tGet the element ammout in Vector		\n");
				noe = VectorGetSize (vector);
				
				if (-1 == noe) 
				{
					printf ("not initialized\n");
				} 
				else if (0 == noe) 
				{
					printf ("the size is zero\n");
				} 
				else 
				{
					printf ("the size is %d\n", noe);					
				}
				
				break;		
				
			case 8 :
				printf ("\tKnow if Vector is empty						\n");	
				isEmpty = IsVectorEmpty (vector);
				
				if (-1 == isEmpty) 
				{
					printf ("not initialized\n");				
				} 
				else if (1 == isEmpty) 
				{
					printf ("vector is empty\n");				
				} 
				else if (0 == isEmpty) 
				{
					printf ("vector is not empty\n");								
				}
				
				break;		
				
			case 9 :
				printf ("\tPrint the Vector elements						\n");
				VectorPrint (vector);
				break;		
					
																																					
			default :
				cont = 0;
				break;	
		}	
	}
	return 0;
}
