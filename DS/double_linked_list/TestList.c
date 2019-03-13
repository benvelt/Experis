/************************************************************
Author: Maya Sandovsky.
Date: 21/11/2011
Last modified date: 17/06/2018 Improved by Alex Katz
Description:
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#include "ADTDefs.h"
#include "doublylinkedlist.h"


int main(void)
{
	List*   list;
	int     grades[] = {89, 67, 100, 23, 77, 88, 99, 56, 77, 82, 66};
	int		numGrades = sizeof(grades) / sizeof(grades[0]);
	char	string[128];
	int     index, num;
	ADTErr  error;


/* Forward creation */
	list = ListCreate();
    /* Initialized list using ListInsertBefore. */
	for (index = 0; index < numGrades; ++index)
	{
		error = ListPushHead(list, grades[index]);
		sprintf(string, "While ListPushHead %d", grades[index]);
		ADTErrPrint (error, string);
	}

	ListPrint(list, 1);	
	printf("\n");
	ListPrint(list, 0);

    printf("\n=============================\n");
    num = ListCountItems(list);
	printf("Num of items: %d\n", num);

	ListDestroy(list);
	
/* Backward creation */
	list = ListCreate();
    /* Initialized list using ListInsertBefore. */
	for (index = 0; index < numGrades; ++index)
	{
		error = ListPushTail(list, grades[index]);
		sprintf(string, "While ListPushTail %d", grades[index]);
		ADTErrPrint (error, string);
	}

	ListPrint(list, 1);
	printf("\n");
	ListPrint(list, 0);

    printf("\n=============================\n");
    num = ListCountItems(list);
	printf("Num of items: %d\n", num);

	ListDestroy(list);
	

	return 0;
}
