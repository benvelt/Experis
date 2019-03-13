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

#include <stdlib.h> /* strtol, malloc, */
#include <stdio.h> /* rename, fopen, fclose, fgets, feof */
#include <string.h> /* strtok_r, strcpy */

#include "params.h"

#define PATH "./config/parameters.config"

/*
 MACROS DEFINITIONS
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Params_ReadConfigFile ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Params_ReadConfigFile(char* _configFilePath, Params* _params)
{
	FILE* fileP = NULL;
	char line[50];
	char delimiter[4] = " = ";
	char *token;
	int length;
	
	if(!_configFilePath || !_params)
		return -1;
	
	fileP = fopen(_configFilePath ,"r");
	if(!fileP)
		return -2;
	
	/*~~~~~~~~~ fileMask ~~~~~~~~~*/
	fgets(line, 50, fileP); /* fileMask = .cdr */
	token = strtok(line, delimiter); /* fileMask */
	if(strcmp(token, "fileMask"))
	{
		fclose(fileP);
		return -3;
	}
	token = strtok(NULL, delimiter); /* .cdr */
	length = strlen(token);
	token[length - 1] = '\0';
	strcpy(_params->m_fileMask, token);
	
	
	/*~~~~~~~~~ newDir ~~~~~~~~~*/
	fgets(line, 50, fileP); /* newDir = ./new_CDR_files */
	token = strtok(line, delimiter); /* newDir */
	if(strcmp(token, "newDir"))
	{
		fclose(fileP);
		return -4;
	}
	token = strtok(NULL, delimiter); /* ./new_CDR_files */
	length = strlen(token);
	token[length - 1] = '\0';
	strcpy(_params->m_newCdrFilesDir, token);
	
	/*~~~~~~~~~ workDir ~~~~~~~~~*/
	fgets(line, 50, fileP); /* workDir = ./work_CDR_files */
	token = strtok(line, delimiter); /* workDir */
	if(strcmp(token, "workDir"))
	{
		fclose(fileP);
		return -5;
	}
	token = strtok(NULL, delimiter); /* ./work_CDR_files */
	length = strlen(token);
	token[length - 1] = '\0';
	strcpy(_params->m_workCdrFilesDir, token);
	
	/*~~~~~~~~~ doneDir ~~~~~~~~~*/
	fgets(line, 50, fileP); /* doneDir = ./done_CDR_files */
	token = strtok(line, delimiter); /* doneDir */
	if(strcmp(token, "doneDir"))
	{
		fclose(fileP);
		return -6;
	}
	token = strtok(NULL, delimiter); /* ./done_CDR_files */
	length = strlen(token);
	token[length - 1] = '\0';
	strcpy(_params->m_doneCdrFilesDir, token);
	
	/*~~~~~~~~~ reportsDir ~~~~~~~~~*/
	fgets(line, 50, fileP); /* reportsDir = ./Reports/ */
	token = strtok(line, delimiter); /* reportsDir */
	if(strcmp(token, "reportsDir"))
	{
		fclose(fileP);
		return -7;
	}
	token = strtok(NULL, delimiter); /* ./Reports/ */
	length = strlen(token);
	token[length - 1] = '\0';
	strcpy(_params->m_reportsDir, token);
	
	/*~~~~~~~~~ readers ~~~~~~~~~*/
	fgets(line, 50, fileP); /* readers = 4 */
	token = strtok(line, delimiter); /* readers */
	if(strcmp(token, "readers"))
	{
		fclose(fileP);
		return -8;
	}
	token = strtok(NULL, delimiter); /* number */
	_params->m_readThreads = strtol(token, NULL, 10);
	
	/*~~~~~~~~~ parsers ~~~~~~~~~*/
	fgets(line, 50, fileP); /* parsers = 4 */
	token = strtok(line, delimiter); /* parsers */
	if(strcmp(token, "parsers"))
	{
		fclose(fileP);
		return -9;
	}
	token = strtok(NULL, delimiter); /* number */
	_params->m_parseThreads = strtol(token, NULL, 10);
	
	/*~~~~~~~~~ reporters ~~~~~~~~~*/
	fgets(line, 50, fileP); /* reporters = 4 */
	token = strtok(line, delimiter); /* reporters */
	if(strcmp(token, "reporters"))
	{
		fclose(fileP);
		return -10;
	}
	token = strtok(NULL, delimiter); /* number */
	_params->m_reportThreads = strtol(token, NULL, 10);
	
	fclose(fileP);
	
	return 0;
}

