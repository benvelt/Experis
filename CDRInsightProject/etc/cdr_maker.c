
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char* OBN = "B&B_Telecom";
/*
char* partyOBN[] = {"bari","bari","bari","bari","bari","bari","bari","bari","bari","bari"};
*/
char* partyOBN[] = {"Yairjun","bari","Janiv","Asaf","Michael","Avital","Hila","Liran","Eli","Yaron","B&B_Telecom"};
char* tuple = "90210";
char* callType[] = {"MOC","MTC","SMS-MO","SMS-MT","GPRS"};
char* filename[] = {"CDRfile1.cdr","CDRfile2.cdr","CDRfile3.cdr","CDRfile4.cdr","CDRfile5.cdr"};

int main()
{
	FILE* filePtr = NULL;
	long unsigned int number;
	long unsigned int number2;
	long unsigned int duration;
	long unsigned int i = 0;
	long unsigned int j = 0;
	srand(time(0)); /* rand() */
	
	for(j = 0; j < 4; ++j)
	{
		filePtr = fopen(filename[j], "w");
		for(i = 0; i < 500000 ; ++i)
		{
			number = (rand() %  1000); /* imsi */
			
			fprintf(filePtr,"%lu  | ",number);
			
			number = (rand() %  99999999) + 10000000; /* msisdn */
			
			fprintf(filePtr," %lu  | ",number);
			
			number = (rand() %  99999999) + 10000000; /* imei */
			
			fprintf(filePtr," %lu  | ",number);
			
			fprintf(filePtr," %s  | ",OBN); /* OBN */
			
			fprintf(filePtr," %s  | ",tuple); /* tuple */
			
			number = rand() % 5;
			fprintf(filePtr," %s  | ",callType[number]); /* callType */
			
			fprintf(filePtr," 06/11/1993  |  04:20:00  | "); /* callDate and callTime */
			
			if(!strcmp(callType[number], callType[0])  ||  !strcmp(callType[number], callType[1]))
			{
				duration = rand() %  1000; /* duration */
				fprintf(filePtr," %lu  | ",duration);
			}
			else
			{
				duration = 0;
				fprintf(filePtr," %lu  | ",duration);
			}
			
			if(!strcmp(callType[number], callType[4]))
			{
				duration = rand() %  1000; /* download */
				fprintf(filePtr," %lu  | ",duration);
				duration = rand() %  10; /* upload */
				fprintf(filePtr," %lu  | ",duration);
			}
			else
			{
				duration = 0;
				fprintf(filePtr," %lu  | ",duration);
				fprintf(filePtr," %lu  | ",duration);
			}
			
			number2 = (rand() %  99999999) + 1000000; /* party msisdn */
			
			fprintf(filePtr," %lu  | ",number2);
			
			if(!strcmp(callType[number], callType[4]))
			{
				fprintf(filePtr," GPRS  | \n"); /* party OBN */
			}
			else
			{
				fprintf(filePtr," %s  \n",partyOBN[rand() % 11]); /* party OBN */
			}
		}
	fclose(filePtr);
	}
/* imsi  |  msisdn  |  imei  |  OBN[64]  |  tuple[6]  |  calltype[8]  |  calldate[16]  |  calltime[16]  |  duration  |  download  |  upload  |  party msisdn  |  gprs  |  party OBN[64]*/
	return 0;
}

















