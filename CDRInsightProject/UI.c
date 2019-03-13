/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <stdio.h> /*  */
#include <pthread.h> /* pthread_t, pthread_create*/
#include <unistd.h>
#include <string.h>

#include "UI.h"
#include "color.h"
#include "generic_queue.h"

/*
 MACROS DEFINITIONS
*/
#define QUEUE_SIZE 		15
#define CLEAR_SCREEN 	printf("\033[H\033[J")

/*
 STRUCTS DEFINITIONS
*/
struct UI
{
	Manager* 		m_manager;
	Storage* 		m_storage;
	pthread_t 		m_uiThread;
	SubscriberCDR* 	m_subscriberCDR;
	OperatorCDR* 	m_operatorCDR;
	Queue*			m_requestsQueue;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
UI* UI_Create(Manager* _manager, Storage* _storage)
{
	UI* ui = NULL;
	
	if(!_manager || !_storage)
		return NULL;
	
	ui = (UI*)malloc(sizeof(UI));
	if(!ui)
		return NULL;
	
	ui->m_manager = _manager;
	ui->m_storage = _storage;
	ui->m_subscriberCDR = (SubscriberCDR*)malloc(sizeof(SubscriberCDR));
	if(!ui->m_subscriberCDR)
	{
		free(ui);
		return NULL;
	}
	
	ui->m_operatorCDR = (OperatorCDR*)malloc(sizeof(OperatorCDR));
	if(!ui->m_operatorCDR)
	{
		free(ui->m_subscriberCDR);
		free(ui);
		return NULL;
	}
	
	ui->m_requestsQueue = Queue_Create(QUEUE_SIZE);
	if(!ui->m_requestsQueue)
	{
		free(ui->m_subscriberCDR);
		free(ui->m_subscriberCDR);
		free(ui);
		return NULL;
	}
	
	return ui;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void UI_Destroy(UI** _ui)
{
	if(_ui && *_ui)
	{
		Queue_Destroy(&(*_ui)->m_requestsQueue, free);
		free((*_ui)->m_operatorCDR);
		free((*_ui)->m_subscriberCDR);
		free(*_ui);
		*_ui = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static UI_PrintSingleSubscriber ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void UI_PrintSingleSubscriber(SubscriberCDR* _subStruct)
{
	printf("\nIMSI - %s\n",_subStruct->m_imsi);
	printf("Out Voice call to same operator - %lu\n",_subStruct->m_OutVoiceSameOperator);
	printf("In Voice call to same operator - %lu\n",_subStruct->m_InVoiceSameOperator);
	printf("Out Voice call to different operator - %lu\n",_subStruct->m_OutVoiceDiffOperator);
	printf("In Voice call to different operator - %lu\n",_subStruct->m_InVoiceDiffOperator);
	printf("Out SMS to same operator - %lu\n",_subStruct->m_OutSMSsameOperator);
	printf("In SMS to same operator - %lu\n",_subStruct->m_InSMSsameOperator);
	printf("Out SMS to different operator - %lu\n",_subStruct->m_OutSMSdiffOperator);
	printf("In SMS to different operator - %lu\n",_subStruct->m_OutSMSdiffOperator);
	printf("MB downloaded - %lu\n",_subStruct->m_MBdownloaded);
	printf("MB uploaded - %lu\n",_subStruct->m_MBuploaded);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static UI_PrintSingleOperator ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void UI_PrintSingleOperator(OperatorCDR* _opeStruct)
{
	printf("\nOperator brand name - %s\n",_opeStruct->m_partyOperatorBrandName);
	printf("Operator tuple - %s\n",_opeStruct->m_OperatorTuple);
	printf("Operator In voice calls - %lu\n",_opeStruct->m_InVoiceCall);
	printf("Operator Out voice calls - %lu\n",_opeStruct->m_OutVoiceCall);
	printf("Operator In SMS - %lu\n",_opeStruct->m_InSMS);
	printf("Operator Out SMS - %lu\n",_opeStruct->m_OutSMS);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static UI_Function ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void* UI_Function(void* _uiStruct)
{
	UI* uiStruct = (UI*)_uiStruct;
	int option;
	int cond = 1;
	int res;
	char keyForStorage[64];
	Request* req;
	char continueKey;
	int flag = 0;
	int i = 0;
	
	while(cond)
	{
		printf("\033[04m"BOLDYELLOW"\n              CDR Insight Project              \n\n"RESET);
		printf(BOLDWHITE"Please choose your option:			\n"RESET);
		printf("   1. Retrieve single Subscriber;			\n");
		printf("   2. Retrieve single Operator;				\n");
		printf("   3. Subscribers Report;					\n");
		printf("   4. Operators Report;						\n");
		printf("   5. Operators & Subscribers Reports;		\n");
		printf("   6. Pause System;							\n");
		printf("   7. Shutdown System;						\n");
		printf(GREEN"\n   Type your option here: "RESET);
		scanf("%d", &option);
		CLEAR_SCREEN;
		
		switch(option)
		{
			case 1 : /* Retrieve Subscriber */
				printf(BLINK BOLDMAGENTA"-------------- Retrieve single Subscriber --------------\n\n"RESET);
				printf(BOLDWHITE"Please enter the subscriber IMSI:  "RESET);
				scanf("%s", keyForStorage);
				
				res = Storage_RetrieveSubscriber(uiStruct->m_storage, keyForStorage, &(uiStruct->m_subscriberCDR));
				if(-2 == res)
					printf(BOLDRED"\nError in Retrieve single Subscriber : IMSI not found.\n"RESET);
				else
					UI_PrintSingleSubscriber(uiStruct->m_subscriberCDR);
				
				printf(GREEN"\nPress Enter to continue.\n"RESET);
				scanf("%c", &continueKey);
				scanf("%c", &continueKey);
				CLEAR_SCREEN;
				break;
			case 2 : /* Retrieve Operator */
				printf(BLINK BOLDMAGENTA"-------------- Retrieve single Operator --------------\n\n"RESET);
				printf(BOLDWHITE"Please enter the Operator Brand Name (OBN):  "RESET);
				scanf("%s", keyForStorage);
				res = Storage_RetrieveOperator(uiStruct->m_storage, keyForStorage, &(uiStruct->m_operatorCDR));
				if(-2 == res)
					printf(BOLDRED"\nError in Retrieve Operator Subscriber : OBN not found.\n"RESET);
				else
					UI_PrintSingleOperator(uiStruct->m_operatorCDR);
				printf(GREEN"\nPress Enter to continue.\n"RESET);
				scanf("%c", &continueKey);
				scanf("%c", &continueKey);
				CLEAR_SCREEN;
				break;
			case 3 : /* Subscribers Report */
				printf(BLINK BOLDMAGENTA"-------------- Subscribers Report --------------\n\n"RESET);
				
				req = (Request*)malloc(sizeof(Request));
				if(!req)
				{
					printf(BOLDRED"\nError in Subscribers Report : can not create task.\n"RESET);
					break;
				}
				
				printf(BOLDWHITE"Please enter the file name to write to:  "RESET);
				scanf("%s", req->m_fileName);
				req->m_requestType = 0;
				printf(BOLDWHITE"\nRequested option is being proccessed.\n"RESET);
				
				Queue_Enqueue(uiStruct->m_requestsQueue, req);
				sleep(2);
				CLEAR_SCREEN;
				break;
			case 4 : /* Operators Report */
				printf(BLINK BOLDMAGENTA"-------------- Operators Report --------------\n\n"RESET);
				
				req = (Request*)malloc(sizeof(Request));
				if(!req)
				{
					printf(BOLDRED"\nError in Operators Report : can not create task.\n"RESET);
					break;
				}
				
				printf(BOLDWHITE"Please enter the file name to write to:  "RESET);
				scanf("%s", req->m_fileName);
				req->m_requestType = 1;
				printf("\nRequested option is being proccessed.\n");
				
				Queue_Enqueue(uiStruct->m_requestsQueue, req);
				sleep(2);
				CLEAR_SCREEN;
				break;
			case 5 : /* Aggregated Reports */
				printf(BLINK BOLDMAGENTA"-------------- Operators & Subscribers Reports --------------\n\n"RESET);
				
				req = (Request*)malloc(sizeof(Request));
				if(!req)
				{
					printf(BOLDRED"\nError in Operators Report : can not create task.\n"RESET);
					break;
				}
				printf(BOLDWHITE"Please enter the file name to write subscribers report:  "RESET);
				scanf("%s", req->m_fileName);
				req->m_requestType = 0;
				Queue_Enqueue(uiStruct->m_requestsQueue, req);
				
				req = (Request*)malloc(sizeof(Request));
				if(!req)
				{
					printf(BOLDRED"\nError in Operators Report : can not create task.\n"RESET);
					break;
				}
				printf(BOLDWHITE"Please enter the file name to write operators report:  "RESET);
				scanf("%s", req->m_fileName);
				req->m_requestType = 1;
				Queue_Enqueue(uiStruct->m_requestsQueue, req);
				
				printf("\nRequested option is being proccessed.\n");
				
				sleep(2);
				CLEAR_SCREEN;
				break;
			case 6 : /* Pause system */
				printf(BLINK BOLDMAGENTA"-------------- System Paused --------------\n\n"RESET);
				flag = 1;
				Manager_Pause(uiStruct->m_manager);
				while(flag)
				{
					printf(BOLDWHITE"\tTo resume system enter 0\n\t"RESET);
					scanf("%d", &flag);
				}
				Manager_Resume(uiStruct->m_manager); /* Resume system */
				CLEAR_SCREEN;
				break;
			case 7 : /* Shutdown system */
				printf(BLINK BOLDMAGENTA"-------------- System Shutdown --------------\n\n"RESET);
				
				/* empty requests queue */
				while(!Queue_IsEmpty(uiStruct->m_requestsQueue))
					Queue_Dequeue(uiStruct->m_requestsQueue, (void**)&req);
				
				printf(RED"\n    System starts Shutdown process.\n\n"RESET);
				
				/* insert two last requests to the requests queue */
				req = (Request*)malloc(sizeof(Request));
				if(!req)
				{
					printf(BOLDRED"\nError in Operators Report : can not create task.\n"RESET);
					break;
				}
				
				strcpy(req->m_fileName, DEFAULT_SUBSCRIBERS_REPORT);
				req->m_requestType = 0;
				Queue_Enqueue(uiStruct->m_requestsQueue, req);
				
				req = (Request*)malloc(sizeof(Request));
				if(!req)
				{
					printf(BOLDRED"\nError in Operators Report : can not create task.\n"RESET);
					break;
				}
				strcpy(req->m_fileName, DEFAULT_OPERATORS_REPORT);
				req->m_requestType = 1;
				Queue_Enqueue(uiStruct->m_requestsQueue, req);
				
				/* if shutdown so make a final report */
				while(i < 9 || !Queue_IsEmpty(uiStruct->m_requestsQueue))
				{
					++i;
					write(1,"\u25A0 ",5);
					sleep(1);
				}
				CLEAR_SCREEN;
				res = Manager_Shutdown(uiStruct->m_manager);
				if(res)
				{
					printf("RES = %d\n",res);
					printf(BOLDRED"\nError in Shutdown system : can not create task.\n"RESET);
				}
				printf(GREEN"\n    System has been Shutdown successfully.\n\n"RESET);
				return NULL;
			default :
				break;
		}
	}
	
	return NULL;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int UI_Run(UI* _ui)
{
	if(!_ui)
		return -1;
	
	if(pthread_create(&_ui->m_uiThread, NULL, UI_Function, _ui))
		return -2;
	
	return 0;
}



/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_GetRequest ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int UI_GetRequest(UI* _ui, Request** _req)
{
	Queue_Dequeue(_ui->m_requestsQueue, (void**)_req);
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Wait ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int UI_Wait(UI* _ui)
{
	void* res;
	if(!_ui)
		return -1;
	
	pthread_join(_ui->m_uiThread, &res);
	
	return 0;
}


















