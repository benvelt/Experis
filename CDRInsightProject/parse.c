/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

#include <stdlib.h> /* strtol, malloc, */
#include <stdio.h>
#include <string.h> /* strtok_r, strcpy */
#include <pthread.h> /* pthread_t, pthread_create*/

#include "parse.h"
#include "generic_queue.h"

/*
 MACROS DEFINITIONS
*/
#define DEC_BASE 10

/*
 STRUCTS DEFINITIONS
*/
struct Parse
{
	int					m_numOfParsers;
	pthread_t*			m_parsers; /* parsers array */
	Read*				m_read;
	Storage*			m_storage;
	pthread_mutex_t 	m_lock;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Parse* Parse_Create(long _numOfParsers, Read* _readP, Storage* _StorageP)
{
	Parse* parse = NULL;
	
	if(!_numOfParsers || !_readP || !_StorageP)
		return NULL;
	
	if(!(parse = (Parse*)malloc(sizeof(Parse))))
		return NULL;
	
	parse->m_numOfParsers = _numOfParsers;
	
	if(!(parse->m_parsers = (pthread_t*)malloc(parse->m_numOfParsers * sizeof(pthread_t))))
	{
		free(parse);
		return NULL;
	}
	
	parse->m_read = _readP;
	parse->m_storage = _StorageP;
	
	if(pthread_mutex_init(&parse->m_lock, NULL))
	{
		free(parse);
		return NULL;
	}
	
	return parse;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Parse_Destroy(Parse** _parse)
{
	if(_parse && *_parse)
	{
		free((*_parse)->m_parsers);
		free(*_parse);
		*_parse = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Line ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
CDRFormat* Parse_Line(char* _CDRRecordLine)
{
	const char delimiter[4] = " | ";
	char *token;
	CDRFormat* cdrline = NULL;
	char* ptr1;
	char* ptr2;
	
	if(!_CDRRecordLine)
		return NULL;
	
	if(!(cdrline = (CDRFormat*)malloc(sizeof(CDRFormat))))
		return NULL;
	
	token = strtok_r(_CDRRecordLine, delimiter, &ptr1);
	strcpy(cdrline->m_imsi, token);
	
	strtok_r(ptr1, delimiter, &ptr2); /* ignore msisdn */
	
	strtok_r(ptr2, delimiter, &ptr1); /* ignore imei */
	
	token = strtok_r(ptr1, delimiter, &ptr2);
	strcpy(cdrline->m_operatorBrandName, token);
	
	token = strtok_r(ptr2, delimiter, &ptr1);
	strcpy(cdrline->m_operatorMCCnMNC, token);
	
	token = strtok_r(ptr1, delimiter, &ptr2);
	strcpy(cdrline->m_callType, token);
	
	strtok_r(ptr2, delimiter, &ptr1); /* ignore call date */
	
	strtok_r(ptr1, delimiter, &ptr2); /* ignore call time */
	
	token = strtok_r(ptr2, delimiter, &ptr1);
	cdrline->m_duration = strtol(token, NULL, DEC_BASE);
	
	token = strtok_r(ptr1, delimiter, &ptr2);
	cdrline->m_download = strtol(token, NULL, DEC_BASE);
	
	token = strtok_r(ptr2, delimiter, &ptr1);
	cdrline->m_upload = strtol(token, NULL, DEC_BASE);
	
	strtok_r(ptr1, delimiter, &ptr2); /* ignore party msisdn */
	
	token = strtok_r(ptr2, delimiter, &ptr1);
	strcpy(cdrline->m_partyOperatorBrandName, token);
	
	return cdrline;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Parse_Function ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*
Used in pthread_create function. The stages of work are:
git line from Read_GetLine;
if line exist and length isn't zero so:
	send line to Parse_Line to create the CDRFormat* struct;
	send the struct to Storage.
*/
static void* Parse_Function(void* _parseStruct)
{
	Parse* parseStruct = (Parse*)_parseStruct;
	char* line;
	CDRFormat* cdrFormat;
	
	while(1)
	{
		/* TODO pause and resume and shutdown functions */
		
		line = Read_GetLine(parseStruct->m_read);
		if(line && 4 < strlen(line))
		{
			cdrFormat = Parse_Line(line);
			if(cdrFormat)
			{
				pthread_mutex_lock(&parseStruct->m_lock);
				Storage_Insert(parseStruct->m_storage, cdrFormat);
				free(line);
				pthread_mutex_unlock(&parseStruct->m_lock);
			}
		}
	}
	
	return NULL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Parse_Run(Parse* _parse)
{
	int i;
	
	if(!_parse)
		return -1;
	
	for(i = 0; i < _parse->m_numOfParsers; ++i)
	{
		if(pthread_create(&_parse->m_parsers[i], NULL, Parse_Function, _parse))
			return -2;
	}
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Stop ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Stop a previously call of Parse_Run.
 * @param[in] _parse - a previously created Parse pointer.
 * @return success or error value.
 * @retval 0 for success;
 * @retval -1 if _parse is null;
 * @retval -2 if parsers cancelling error;
 * @retval -3 if parsers waiting error;
 */
int Parse_Stop(Parse* _parse)
{
	int i;
	void* res;
	
	if(!_parse)
		return -1;
	
	for(i = 0; i < _parse->m_numOfParsers; ++i)
	{
		if(pthread_cancel(_parse->m_parsers[i]))
			return -2;
	}
	
	for(i = 0; i < _parse->m_numOfParsers; ++i)
	{
		if(pthread_join(_parse->m_parsers[i], &res))
			return -3;
	}
	
	return 0;
}




