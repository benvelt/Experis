/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			23.07.18
 * Date last modified :
 * Description : 			main program to check zlog4c file.
******************************************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "zlog4c.h"

void Print(void)
{
	int i = 9;
	ZLOG(LOG_CRITICAL,"PRINT","Log_Level is critical, var i = %d, char test is - %c.", i,'t');
	puts("\nIn Print function.\n");
}

void Print2(void)
{
	int i = 0;
	ZLOG(LOG_ERROR,"PRINT2","Log_Level is error, var i = %d, string test is - %s.", i, "tested string");
	puts("\nIn Print function.\n");
}

int main()
{
	zlog_init("app.log.config");
	
	printf("Starting main %ld\n",time(NULL) / 1000000);
	
	Print();
	Print2();
	
	return 0;
}

















