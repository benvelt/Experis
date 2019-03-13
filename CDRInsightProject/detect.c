/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <stdio.h> /*  */
#include <pthread.h> /* pthread_t, pthread_create*/
#include <string.h> /* strcpy, strcmp, strcat, strlen */
#include <unistd.h> /* sleep */
#include <dirent.h> /* opendir, readdir, closedir */

#include "detect.h"
#include "generic_queue.h"

/*
 MACROS DEFINITIONS
*/
#define QUEUE_SIZE 30
#define DIR_PATH_NAME_LENGTH 256
#define SEARCH_INTERVAL 2 /* [seconds] */
#define FILE_NAME_LENGTH 256
#define FILE_EXTENSION ".cdr"
#define FILE_EXTENSION_LENGTH 4
#define DEC_BASE 10

/*
 STRUCTS DEFINITIONS
*/
struct Detect
{
	Queue* m_filesQueue;
	char m_newCdrDirPath[DIR_PATH_NAME_LENGTH]; /* new cdr files dir */
	char m_workCdrDirPath[DIR_PATH_NAME_LENGTH]; /* work cdr files dir */
	char m_fileMask[DIR_PATH_NAME_LENGTH];
	pthread_t m_detector;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Detect* Detect_Create(char* _newCdrDirPath, char* _workCdrDirPath, char* _fileMask)
{
	Detect* detect = NULL;
	
	if(!_newCdrDirPath || !_workCdrDirPath)
		return NULL;
	
	if(!(detect = (Detect*)malloc(sizeof(Detect))))
		return NULL;
	
	if(!(detect->m_filesQueue = Queue_Create(QUEUE_SIZE)))
	{
		free(detect);
		return NULL;
	}
	
	
	strcpy(detect->m_newCdrDirPath, _newCdrDirPath);
	strcpy(detect->m_workCdrDirPath, _workCdrDirPath);
	strcpy(detect->m_fileMask, _fileMask);
	
	return detect;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Detect_Destroy(Detect** _detect)
{
	if(_detect && *_detect)
	{
		Queue_Destroy(&(*_detect)->m_filesQueue, free);
		free(*_detect);
		*_detect = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_GetFileName ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
char* Detect_GetFileName(Detect* _detect)
{
	char* newFile = NULL;
	
	Queue_Dequeue(_detect->m_filesQueue, (void**)&newFile);
	
	return newFile;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Detect_SearchNewFile ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Search files in a directory.
_newCdrDirPath - the directory to work on (length is DIR_PATH_NAME_LENGTH).
it will search file with the extension _fileMask.
if found, the file will be moved to _workCdrDirPath.
*/

static char* Detect_SearchNewFile(char* _newCdrDirPath, char* _workCdrDirPath, char* _fileMask)
{
	DIR* dir;
	struct dirent *ds;
	size_t length;
	char nextFileName[256];
	char currFileName[256];
	char* fileName;
	
	dir = opendir(_newCdrDirPath);
	while(0 != (ds = readdir(dir)))
	{
		
		length = strlen(ds->d_name);
		if(!strcmp(ds->d_name + length - FILE_EXTENSION_LENGTH, _fileMask))
		{
			strcpy(currFileName, _newCdrDirPath);
			strcat(currFileName, ds->d_name);
			
			strcpy(nextFileName, _workCdrDirPath);
			strcat(nextFileName, ds->d_name);
			
			if(!(fileName = (char*)malloc(length * sizeof(char) + 1)))
				return NULL;
			
			strcpy(fileName,ds->d_name);
			
			if(rename(currFileName, nextFileName))
			{
				free(fileName);
				return NULL;
			}
			
			break;
		}
	}
	closedir(dir);
	
	return fileName;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Detect_Function ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Used in pthread_create function. The stages of work are:
sleep with SEARCH_INTERVAL;
call Detect_SearchNewFile in order to get new file from working directory (detectStruct->m_newCdrDirPath);
if fileName is not NULL so insert to the files Queue (detectStruct->m_filesQueue).
*/
static void* Detect_Function(void* _detectStruct)
{
	Detect* detectStruct = (Detect*)_detectStruct;
	char* fileName;
	
	while(1)
	{
		if(!(fileName = Detect_SearchNewFile(detectStruct->m_newCdrDirPath, detectStruct->m_workCdrDirPath, 
												detectStruct->m_fileMask)))
			break;
		
		Queue_Enqueue(detectStruct->m_filesQueue, fileName);
		
		sleep(SEARCH_INTERVAL);
	}
	
	return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Detect_Run(Detect* _detect)
{
	if(!_detect)
		return -1;
	
	if(pthread_create(&_detect->m_detector, NULL, Detect_Function, _detect))
		return -2;
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Stop ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Detect_Stop(Detect* _detect)
{
	void* res;
	
	if(!_detect)
		return -1;
	
	if(pthread_cancel(_detect->m_detector))
		return -2;
	
	if(pthread_join(_detect->m_detector, &res))
		return -3;
	
	return 0;
}





