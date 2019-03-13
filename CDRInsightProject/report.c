#include <stdlib.h> /* malloc, free */
#include <stdio.h> /*  */
#include <pthread.h> /* pthread_t, pthread_create*/
#include <string.h> /* strcpy, strcmp, strcat, strlen */
#include <time.h>
#include <signal.h>

#include "report.h"
#include "color.h"

/*
 MACROS DEFINITIONS
*/
#define BUF_LNG 64

/*
 STRUCTS & VARIABLES DEFINITIONS
*/
struct Report
{
	Storage* 	m_storage;
	char 		m_reportsDir[50];
	long 		m_numOfReporters;
	pthread_t* 	m_reporters;
	UI* 		m_ui;
	struct sigaction m_sigusr1_sa;
	struct sigaction m_sigusr2_sa;
};

Report* signalsStruct;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static SigUSR1Handler ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void SigUSR1Handler(int sig)
{
	Report_AllSubscribers(signalsStruct, SIGUSR1_SUBSCRIBERS_REPORT);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static SigUSR2Handler ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void SigUSR2Handler(int sig)
{
	Report_AllOperators(signalsStruct, SIGUSR2_OPERATORS_REPORT);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Report* Report_Create(Storage* _storage, UI* _ui, char* _reportsDir, long _numOfReporters)
{
	Report* report = NULL;
	struct sigaction sigusr1_sa;
	struct sigaction sigusr2_sa;
	
	sigusr1_sa.sa_handler = SigUSR1Handler;
	sigusr1_sa.sa_flags = 0;
	sigemptyset(&sigusr1_sa.sa_mask);
	
	sigusr2_sa.sa_handler = SigUSR2Handler;
	sigusr2_sa.sa_flags = 0;
	sigemptyset(&sigusr2_sa.sa_mask);
	
	if(-1 == sigaction(SIGUSR1, &sigusr1_sa, NULL)|| -1 == sigaction(SIGUSR2, &sigusr2_sa, NULL))
		return NULL;
	
	if(!_storage || !_ui || !_reportsDir || !_numOfReporters)
		return NULL;
	
	report = (Report*)malloc(sizeof(Report));
	if(!report)
		return NULL;
	
	report->m_numOfReporters = _numOfReporters;
	
	report->m_reporters = (pthread_t*)malloc(report->m_numOfReporters * sizeof(pthread_t));
	if(!report->m_reporters)
	{
		free(report);
		return NULL;
	}
	
	report->m_storage = _storage;
	strcpy(report->m_reportsDir, _reportsDir);
	report->m_ui = _ui;
	
	report->m_sigusr1_sa = sigusr1_sa;
	report->m_sigusr2_sa = sigusr2_sa;
	
	signalsStruct = report;
	
	return report;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Report_Destroy(Report** _report)
{
	if(_report && *_report)
	{
		free((*_report)->m_reporters);
		free(*_report);
		*_report = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ GetTime ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
char* GetTime(char* _buffer)
{
	time_t timer;
	struct tm* tm_info;
	
	time(&timer);
	tm_info = localtime(&timer);
	
	strftime(_buffer, BUF_LNG, "%Y-%m-%d %H:%M:%S", tm_info);
	
	return _buffer;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ PrintAllSubscribers ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int PrintAllSubscribers(char* _key, SubscriberCDR* _subStruct, FILE* _filePtr)
{
	fprintf(_filePtr,"%s, ",_subStruct->m_imsi);
	fprintf(_filePtr,"%lu, ",_subStruct->m_OutVoiceSameOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_InVoiceSameOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_OutVoiceDiffOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_InVoiceDiffOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_OutSMSsameOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_InSMSsameOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_OutSMSdiffOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_InSMSdiffOperator);
	fprintf(_filePtr,"%lu, ",_subStruct->m_MBdownloaded);
	fprintf(_filePtr,"%lu\n",_subStruct->m_MBuploaded);
	
	_subStruct->m_OutVoiceSameOperator 	= 0;
	_subStruct->m_InVoiceSameOperator 	= 0;
	_subStruct->m_OutVoiceDiffOperator 	= 0;
	_subStruct->m_InVoiceDiffOperator 	= 0;
	_subStruct->m_OutSMSsameOperator 	= 0;
	_subStruct->m_InSMSsameOperator 	= 0;
	_subStruct->m_OutSMSdiffOperator 	= 0;
	_subStruct->m_InSMSdiffOperator 	= 0;
	_subStruct->m_MBdownloaded 			= 0;
	_subStruct->m_MBuploaded 			= 0;
	
	return 1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ PrintAllOperators ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int PrintAllOperators(char* _key, OperatorCDR* _opeStruct, FILE* _filePtr)
{
	fprintf(_filePtr,"%s, ",_opeStruct->m_partyOperatorBrandName);
	fprintf(_filePtr,"%s, ",_opeStruct->m_OperatorTuple);
	fprintf(_filePtr,"%lu, ",_opeStruct->m_InVoiceCall);
	fprintf(_filePtr,"%lu, ",_opeStruct->m_OutVoiceCall);
	fprintf(_filePtr,"%lu, ",_opeStruct->m_InSMS);
	fprintf(_filePtr,"%lu\n",_opeStruct->m_OutSMS);
	
	_opeStruct->m_InVoiceCall 	= 0;
	_opeStruct->m_OutVoiceCall 	= 0;
	_opeStruct->m_InSMS 		= 0;
	_opeStruct->m_OutSMS 		= 0;
	
	return 1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_AllSubscribers ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Report_AllSubscribers(Report* _report, char* _reportFileName)
{
	char fullFilePath[50];
	int res;
	FILE* filePtr = NULL;
	char buffer[BUF_LNG];
	
	strcpy(fullFilePath, _report->m_reportsDir);
	strcat(fullFilePath, _reportFileName);
	
	filePtr = fopen(fullFilePath, "w");
	if(!filePtr)
		return -1;
	
	GetTime(buffer);
	
	fprintf(filePtr,"%s\n",buffer);
	
	res = Storage_RetrieveAllSubscribers(_report->m_storage, PrintAllSubscribers, filePtr);
	
	fclose(filePtr);
	
	return res;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_AllOperators ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Report_AllOperators(Report* _report, char* _reportFileName)
{
	char fullFilePath[50];
	int res;
	FILE* filePtr = NULL;
	char buffer[BUF_LNG];
	
	strcpy(fullFilePath, _report->m_reportsDir);
	strcat(fullFilePath, _reportFileName);
	
	filePtr = fopen(fullFilePath, "w");
	if(!filePtr)
		return -1;
	
	GetTime(buffer);
	
	fprintf(filePtr,"%s\n",buffer);
	
	res = Storage_RetrieveAllOperators(_report->m_storage, PrintAllOperators, filePtr);
	
	fclose(filePtr);
	
	return res;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Report_Function ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static void* Report_Function(void* _reportStruct)
{
	Report* reportStruct = (Report*)_reportStruct;
	Request* req;
	
	while(1)
	{
		UI_GetRequest(reportStruct->m_ui, &req);
		
		if(0 == req->m_requestType)
			Report_AllSubscribers(reportStruct, req->m_fileName);
		else if(1 == req->m_requestType)
			Report_AllOperators(reportStruct, req->m_fileName);
		
		free(req);
	}
	
	return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Report_Run(Report* _report)
{
	int i = 0;
	
	if(!_report)
		return -1;
	
	for(i = 0; i < _report->m_numOfReporters; ++i)
	{
		if(pthread_create(&_report->m_reporters[i], NULL, Report_Function, _report))
			return -2;
	}
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Stop ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Report_Stop(Report* _report)
{
	int i;
	void* res;
	
	if(!_report)
		return -1;
	
	for(i = 0; i < _report->m_numOfReporters; ++i)
	{
		if(pthread_cancel(_report->m_reporters[i]))
			return -2;
	}
	
	for(i = 0; i < _report->m_numOfReporters; ++i)
	{
		if(pthread_join(_report->m_reporters[i], &res))
			return -3;
	}
	
	return 0;
}










