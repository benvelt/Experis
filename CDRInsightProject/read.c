/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		
******************************************************************************************************/

/** 
 *  @file HashMap.h
 *  @brief Generic Hash map of key-value pairs implemented with separate chaining using linked lists.
 *	
 *  @details  The hash map (sometimes called dictionary or associative array)
 *  is a set of distinct keys (or indexes) mapped (or associated) to values.
 *  size of allocated table will be the nearest prime number greater than requested capacity.
 *  Lists used for chaining will be allocated eagerly.
 *
 *  @author Muhammad Zahalqa  (MuhammadZ@experis.co.il)
 * 
 *  @bug No known bugs! 
 */

#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* rename, fopen, fclose, fgets, feof */
#include <pthread.h> /* pthread_t, pthread_create*/
#include <string.h> /* strcat, strcpy */
#include <unistd.h>
#include "read.h"
#include "generic_queue.h"

/*
 MACROS DEFINITIONS
*/
#define QUEUE_SIZE 30
#define LINE_LENGTH 256
#define ON 1
#define OFF 0

/*
 STRUCTS DEFINITIONS
*/
struct Read
{
	Detect*		m_detect;
	Queue*		m_linesQueue;
	int			m_numOfReaders;
	pthread_t*	m_readers; /* readers array */
	char m_workDir[256];
	char m_doneDir[256];
	pthread_mutex_t 	m_lock;
	pthread_cond_t 		m_runCond;
	int 				m_runFlag;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Read* Read_Create(Detect* _detectP, long _numOfReaders, char* _workDir, char* _doneDir)
{
	Read* read;
	
	if(!_numOfReaders || !_detectP || !_workDir || !_doneDir)
		return NULL;
	
	read = (Read*)malloc(sizeof(Read));
	if(!read)
		return NULL;
	
	read->m_detect = _detectP;
	
	/* create the queue that will store the lines from file */
	read->m_linesQueue = Queue_Create(QUEUE_SIZE);
	if(!read->m_linesQueue)
	{
		free(read);
		return NULL;
	}
	
	read->m_numOfReaders = _numOfReaders;
	
	read->m_readers = (pthread_t*)malloc(read->m_numOfReaders * sizeof(pthread_t));
	if(!read->m_readers)
	{
		Queue_Destroy(&read->m_linesQueue, NULL);
		free(read);
		return NULL;
	}
	
	strcpy(read->m_workDir, _workDir);
	strcpy(read->m_doneDir, _doneDir);
	
	if(pthread_cond_init(&read->m_runCond, NULL))
	{
		Queue_Destroy(&read->m_linesQueue, NULL);
		free(read);
		return NULL;
	}
	
	if(pthread_mutex_init(&read->m_lock, NULL))
	{
		Queue_Destroy(&read->m_linesQueue, NULL);
		free(read);
		return NULL;
	}
	
	read->m_runFlag = ON;
	
	return read;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Read_Destroy(Read** _read)
{
	if(_read && *_read)
	{
		free((*_read)->m_readers);
		Queue_Destroy(&(*_read)->m_linesQueue, free);
		free(*_read);
		*_read = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_GetLine ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
 dequeue lines from linesQueue
*/
char* Read_GetLine(Read* _read)
{
	char* extractedLine;
	
	if(!_read)
		return NULL;
	
	Queue_Dequeue(_read->m_linesQueue, (void**)&extractedLine);
	
	return extractedLine;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Read_TransferDoneFile ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
change the _fileName dir to a _newPath dir.
this will be done after the Read_Function finished to read _fileName file.
_fileName example configuration is - "file.txt"
_newPath example configuration is - "/home/usr/newPath/"
*/
static int Read_TransferDoneFile(char* _fileName,char* _newPath)
{
	if(rename(_fileName, _newPath))
		return -1;
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Read_Function ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Used in pthread_create function. The stages of work are:
get file name from Detect_GetFileName;
open the file and go to the start of the file;
	allocate space for the read line from file;
	insert the line to the queue;
	check if reached to end of file.
*/
static void* Read_Function(void* _readStruct)
{
	FILE* fileP;
	char* fileName;
	char* line;
	Read* readStruct = (Read*)_readStruct;
	char currFileName[256];
	char doneFileName[256];
	
	while(1)
	{
		do
		{
			fileName = Detect_GetFileName(readStruct->m_detect);
		} while(4 > strlen(fileName));
		
		if(!fileName)
			return NULL;
		
		strcpy(currFileName, readStruct->m_workDir);
		strcat(currFileName, fileName);
		
		fileP = fopen(currFileName ,"r");
		if(!fileP)
			return NULL;
		
		while(1)
		{
			/* Resume / Pause */
			pthread_mutex_lock(&readStruct->m_lock);
			while(readStruct->m_runFlag == OFF)
				pthread_cond_wait(&readStruct->m_runCond, &readStruct->m_lock);
			
			pthread_mutex_unlock(&readStruct->m_lock);
			/* Pause / Resume */
			
			line = malloc(LINE_LENGTH * sizeof(char));
			fgets(line, LINE_LENGTH, fileP);
			
			Queue_Enqueue(readStruct->m_linesQueue, line);
			if(feof(fileP))
			{
				fclose(fileP);
				
				strcpy(doneFileName, readStruct->m_doneDir);
				strcat(doneFileName, fileName);
				
				if(Read_TransferDoneFile(currFileName, doneFileName))
					return NULL;
				
				/* in Detect_SearchNewFile, fileName got malloc, than it passed to Read_Function,
				than it passed to Read_TransferDoneFile and here it supposed to be free */
				free(fileName);
				
				break;
			}
		}
	}
	
	return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Read_Run(Read* _read)
{
	int i;
	
	if(!_read)
		return -1;
	
	for(i = 0; i < _read->m_numOfReaders; ++i)
	{
		if(pthread_create(&_read->m_readers[i], NULL, Read_Function, _read))
			return -2;
	}
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Pause ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Read_Pause(Read* _read)
{
	_read->m_runFlag = OFF;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Resume ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Read_Resume(Read* _read)
{
	_read->m_runFlag = ON;
	pthread_cond_broadcast(&_read->m_runCond);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Stop ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Read_Stop(Read* _read)
{
	int i;
	void* res;
	int result;
	
	if(!_read)
		return -1;
	
	for(i = 0; i < _read->m_numOfReaders; ++i)
	{
		result = pthread_cancel(_read->m_readers[i]);
		
		if(result)
			return -2;
	}
	
	for(i = 0; i < _read->m_numOfReaders; ++i)
	{
		if(pthread_join(_read->m_readers[i], &res))
			return -3;
	}
	
	return 0;
}





