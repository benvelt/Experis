/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		
******************************************************************************************************/

#include <stdlib.h> /* strtol, malloc, */
#include <stdio.h> /* rename, fopen, fclose, fgets, feof */
#include <string.h> /* strtok_r, strcpy */

#include "params.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Params_ReadConfigFile ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Params_ReadConfigFile(char* _configFilePath, Params* _params)
{
	FILE* fileP = NULL;
	char line[50];
	char delimiter[4] = " = ";
	char *token;
	int length;
	int i;
	
	if(!_configFilePath || !_params)
		return -1;
	
	fileP = fopen(_configFilePath ,"r");
	if(!fileP)
		return -2;
	
	for(i = 0; i < 8; ++i)
	{
		fgets(line, 50, fileP);
		token = strtok(line, delimiter);
		if(!strcmp(token, "fileMask"))
		{
			token = strtok(NULL, delimiter);
			length = strlen(token);
			token[length - 1] = '\0';
			strcpy(_params->m_fileMask, token);
		}
		else if(!strcmp(token, "newDir"))
		{
			token = strtok(NULL, delimiter);
			length = strlen(token);
			token[length - 1] = '\0';
			strcpy(_params->m_newCdrFilesDir, token);
		}
		else if(!strcmp(token, "workDir"))
		{
			token = strtok(NULL, delimiter);
			length = strlen(token);
			token[length - 1] = '\0';
			strcpy(_params->m_workCdrFilesDir, token);
		}
		else if(!strcmp(token, "doneDir"))
		{
			token = strtok(NULL, delimiter);
			length = strlen(token);
			token[length - 1] = '\0';
			strcpy(_params->m_doneCdrFilesDir, token);
		}
		else if(!strcmp(token, "reportsDir"))
		{
			token = strtok(NULL, delimiter);
			length = strlen(token);
			token[length - 1] = '\0';
			strcpy(_params->m_reportsDir, token);
		}
		else if(!strcmp(token, "readers"))
		{
			token = strtok(NULL, delimiter); /* number */
			_params->m_readThreads = strtol(token, NULL, 10);
		}
		else if(!strcmp(token, "parsers"))
		{
			token = strtok(NULL, delimiter); /* number */
			_params->m_parseThreads = strtol(token, NULL, 10);
		}
		else if(!strcmp(token, "reporters"))
		{
			token = strtok(NULL, delimiter); /* number */
			_params->m_reportThreads = strtol(token, NULL, 10);
		}
		else
		{
			return -3;
		}
	}
	
	fclose(fileP);
	
	return 0;
}

