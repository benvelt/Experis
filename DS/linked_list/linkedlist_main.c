#include <stdio.h> /* switch, printf */
#include <string.h> /* fgets */

#include "linkedlist.h"

int main ()
{
	int mainCont = 1;
	int mainOption = 0;
	int cont = 1;
	int option = 0;

	Person* head = NULL;
	Person* newPerson = NULL;
	size_t id = 0;
	char name[128];
	size_t age = 0;
	
	Person* item = NULL;
	
	while (mainCont)
	{
		printf ("\n**********************************************	\n");
		printf ("Please choose option: 				 				 \n\n");
		printf ("1. Regular insert/remove;			 				 	\n");
		printf ("2. By Key insert/remove;				 			 	\n");
		printf ("3. Recursive By Key insert/remove;			 	\n");
		printf ("Any other number to exit							 	\n");
		scanf ("%d", &mainOption);
		printf ("\n**********************************************	\n");
		
		switch (mainOption)
		{
			case 1 :
				while (cont)
				{
					printf ("\n**********************************************	\n");
					printf ("\tRegular insert / remove							 \n\n");
					printf ("Please choose option: 					 			 	\n");
					printf ("1. Regular insert;			 				 				\n");
					printf ("2. Regular remove;						 			 	\n");
					printf ("3. Print list;									 			 	\n");
					printf ("Any other number to exit							 	\n");
					scanf ("%d", &option);
					printf ("\n**********************************************	\n");
					
					switch (option)
					{
						case 1 :
							
							printf ("Enter person id: "				);
							scanf ("%lu", &id);
							getc (stdin);
							printf ("\nEnter person name: "		);
							fgets (name, 128, stdin);
							printf ("\nEnter person age: "		);	
							scanf ("%lu", &age);
							
							newPerson = NewPerson (newPerson, id, name, age);
							
							head = ListInsertHead (head, newPerson);
							break;
						case 2 :
							head = ListRemoveHead (head, &item);
							break;
						case 3 :
							ListPrint (head); 
							break;
						default :
							return 0;
							break;
					}
				}				
				break;
			case 2 :
				while (cont)
				{
					printf ("\n**********************************************	\n");
					printf ("\tBy Key insert / remove							 \n\n");
					printf ("Please choose option: 					 			 	\n");
					printf ("1. By Key insert;			 				 				\n");
					printf ("2. By Key remove;						 			 	\n");
					printf ("3. Print list;									 			 	\n");
					printf ("Any other number to exit							 	\n");
					scanf ("%d", &option);
					printf ("\n**********************************************	\n");
					
					switch (option)
					{
						case 1 :	
							printf ("Enter person id: "				);
							scanf ("%lu", &id);
							getc (stdin);
							printf ("\nEnter person name: "		);
							fgets (name, 128, stdin);
							printf ("\nEnter person age: "		);	
							scanf ("%lu", &age);
							
							newPerson = NewPerson (newPerson, id, name, age);
							
							head = ListInsertByKey (head, 1, newPerson);
							break;
							
						case 2 :
							printf ("Enter person id: "				);
							scanf ("%lu", &id);
							head = LIstRemoveByKey (head, id, &item);
							ListPrint (head); 
							break;
							
						case 3 :
						
							ListPrint (head); 
							break;
						default :
							return 0;
							break;
					}
				}
				break;
			case 3:
				while (cont)
				{
					printf ("\n**********************************************	\n");
					printf ("\tRecursive By Key insert / remove			 \n\n");
					printf ("Please choose option: 					 			 	\n");
					printf ("1. Recursive By Key insert;			 				\n");
					printf ("2. Recursive By Key remove;			 			 	\n");
					printf ("3. Print list;									 			 	\n");
					printf ("Any other number to exit							 	\n");
					scanf ("%d", &option);
					printf ("\n**********************************************	\n");
					
					switch (option)
					{
						case 1 :
							printf ("Enter person id: "				);
							scanf ("%lu", &id);
							getc (stdin);
							printf ("\nEnter person name: "		);
							fgets (name, 128, stdin);
							printf ("\nEnter person age: "		);	
							scanf ("%lu", &age);
							
							newPerson = NewPerson (newPerson, id, name, age);
							
							head = ListInsertByKeyRec (head, 1, newPerson);
							
							break;
						case 2 :
							printf ("Enter person id: "				);
							scanf ("%lu", &id);
							head = LIstRemoveByRec (head, id, &item);
							ListPrint (head); 
							break;
							
						case 3 :
							ListPrint (head); 
							break;
						default :
							return 0;
							break;
					}
				}				
				break;
			default :
				mainCont = 0;
				break;
		}
	}
	return 0;
}
