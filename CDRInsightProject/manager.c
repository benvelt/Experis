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

#include <string.h> /* strcat, strcpy */
#include <unistd.h> /* sleep */

#include "detect.h"
#include "read.h"
#include "storage.h"
#include "parse.h"
#include "params.h"
#include "report.h"
#include "UI.h"
#include "manager.h"
#include "color.h"

#define CONFIG_DIR "./config/parameters.config"
#define CLEAR_SCREEN 	printf("\033[H\033[J")
/*
 MACROS DEFINITIONS
*/

/*
 STRUCTS DEFINITIONS
*/
struct Manager
{
	Detect* 	m_detect;
	Read* 		m_read;
	Parse* 		m_parse;
	Storage* 	m_storage;
	Params* 	m_params;
	UI* 		m_ui;
	Report* 	m_report;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Manager* Manager_Create(void)
{
	Manager* manager = NULL;
	int res;
	
	manager = (Manager*)malloc(sizeof(Manager));
	if(!manager)
		return NULL;
	
	manager->m_params = (Params*)malloc(sizeof(Params));
	
	res = Params_ReadConfigFile(CONFIG_DIR, manager->m_params);
	if(res) /* if there is error with the config file so default initiate */
	{
		printf("inside Manager_Create: Params_ReadConfigFile fail, res = %d\n",res);
		
		manager->m_params->m_parseThreads 	= DEFAULT_PARSERS;
		manager->m_params->m_readThreads 	= DEFAULT_READERS;
		manager->m_params->m_reportThreads 	= DEFAULT_REPORTERS;
		strcpy(manager->m_params->m_newCdrFilesDir, DEFAULT_NEW_CDR_DIR);
		strcpy(manager->m_params->m_workCdrFilesDir, DEFAULT_WORK_CDR_DIR);
		strcpy(manager->m_params->m_doneCdrFilesDir, DEFAULT_DONE_CDR_DIR);
		strcpy(manager->m_params->m_reportsDir, DEFAULT_REPORTS_DIR);
		strcpy(manager->m_params->m_fileMask, DEFAULT_FILE_MASK);
	}
	
	printf(BOLDWHITE"\nConfiguration file:\n"RESET);
	printf(WHITE" - Number of readers   is: %ld\n",manager->m_params->m_readThreads);
	printf(" - Number of parsers   is: %ld\n",manager->m_params->m_parseThreads);
	printf(" - Number of reporters is: %ld\n",manager->m_params->m_reportThreads);
	printf(" - New  CDR files directory is: %s\n",manager->m_params->m_newCdrFilesDir);
	printf(" - Work CDR files directory is: %s\n",manager->m_params->m_workCdrFilesDir);
	printf(" - Done CDR files directory is: %s\n",manager->m_params->m_doneCdrFilesDir);
	printf(" - Reports  files directory is: %s\n",manager->m_params->m_reportsDir);
	printf(" - File mask is: *%s\n"RESET,manager->m_params->m_fileMask);
	return manager;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Manager_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int Manager_CreateSystem(Manager* _manager)
{
	int result = 0;
	
	/* static init */
	_manager->m_detect = Detect_Create(_manager->m_params->m_newCdrFilesDir, 
										_manager->m_params->m_workCdrFilesDir, 
										_manager->m_params->m_fileMask);
	if(!_manager->m_detect)
	{
		printf("Detect_Create error\n");
		result = -1;
		goto DETECT_CREATE_ERROR;
	}
	
	_manager->m_read = Read_Create(_manager->m_detect, _manager->m_params->m_readThreads, 
									_manager->m_params->m_workCdrFilesDir, 
									_manager->m_params->m_doneCdrFilesDir);
	if(!_manager->m_read)
	{
		printf("Read_Create error\n");
		result = -2;
		goto READ_CREATE_ERROR;
	}
	
	_manager->m_storage = Storage_Create();
	if(!_manager->m_storage)
	{
		printf("Storage_Create error\n");
		result = -3;
		goto STORAGE_CREATE_ERROR;
	}
	
	_manager->m_parse = Parse_Create(_manager->m_params->m_parseThreads, _manager->m_read, _manager->m_storage);
	if(!_manager->m_parse)
	{
		printf("Parse_Create error\n");
		result = -4;
		goto PARSE_CREATE_ERROR;
	}
	
	_manager->m_ui = UI_Create(_manager, _manager->m_storage);
	if(!_manager->m_ui)
	{
		printf("Parse_Create error\n");
		result = -5;
		goto UI_CREATE_ERROR;
	}
	
	_manager->m_report = Report_Create(_manager->m_storage, _manager->m_ui, _manager->m_params->m_reportsDir, 
										_manager->m_params->m_reportThreads);
	if(!_manager->m_report)
	{
		printf("Parse_Create error\n");
		result = -6;
		goto REPORT_CREATE_ERROR;
	}
	
	return result;
	
	REPORT_CREATE_ERROR:
	UI_Destroy(&_manager->m_ui);
	
	UI_CREATE_ERROR:
	Parse_Destroy(&_manager->m_parse);
	
	PARSE_CREATE_ERROR:
	Storage_Destroy(&_manager->m_storage);
	
	STORAGE_CREATE_ERROR:
	Read_Destroy(&_manager->m_read);
	
	READ_CREATE_ERROR:
	Detect_Destroy(&_manager->m_detect);
	
	DETECT_CREATE_ERROR:
	Manager_Destroy(&_manager);
	
	return result;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Manager_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int Manager_RunSystem(Manager* _manager)
{
	int res;
	
	/* dynamic init */
	res = Parse_Run(_manager->m_parse);
	if(res)
	{
		/* TODO destroy manager->m_storage */
		/* TODO destroy manager->m_read */
		/* TODO destroy manager->m_detect */
		/* TODO destroy manager */
		return -1;
	}
	res = Read_Run(_manager->m_read);
	if(res)
	{
		/* TODO shutdown Parse_Run */
		/* TODO destroy manager->m_storage */
		/* TODO destroy manager->m_read */
		/* TODO destroy manager->m_detect */
		/* TODO destroy manager */
		return -2;
	}
	res = Detect_Run(_manager->m_detect);
	if(res)
	{
		/* TODO shutdown Read_Run */
		/* TODO shutdown Parse_Run */
		/* TODO destroy manager->m_storage */
		/* TODO destroy manager->m_read */
		/* TODO destroy manager->m_detect */
		/* TODO destroy manager */
		return -3;
	}
	
	res = UI_Run(_manager->m_ui);
	if(res)
	{
		/* TODO shutdown Detect_Run */
		/* TODO shutdown Read_Run */
		/* TODO shutdown Parse_Run */
		/* TODO destroy manager->m_storage */
		/* TODO destroy manager->m_read */
		/* TODO destroy manager->m_detect */
		/* TODO destroy manager */
		return -4;
	}
	
	res =  Report_Run(_manager->m_report);
	if(res)
	{
		/* TODO shutdown Report_Run */
		/* TODO shutdown Detect_Run */
		/* TODO shutdown Read_Run */
		/* TODO shutdown Parse_Run */
		/* TODO destroy manager->m_storage */
		/* TODO destroy manager->m_read */
		/* TODO destroy manager->m_detect */
		/* TODO destroy manager */
		return -4;
	}
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Manager_Destroy(Manager** _manager)
{
	if(_manager && !_manager)
	{
		free(*_manager);
		*_manager = NULL;
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
	Manager* manager = NULL;
	int res;
	
	CLEAR_SCREEN;
	
	manager = Manager_Create();
	if(!manager)
	{
		printf("Manager_CreateSystem Manager_Create error\n");
		return -1;
	}
	
	/* static initiate */
	res = Manager_CreateSystem(manager);
	if(res)
	{
		printf("Manager_CreateSystem error!\n");
		return -1;
	}
	
	res = Manager_RunSystem(manager);
	if(res)
	{
		printf("Manager_CreateSystem error!\n");
		return -2;
	}
	
	res = UI_Wait(manager->m_ui);
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Pause ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Manager_Pause(Manager* _manager)
{
	Read_Pause(_manager->m_read);
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Resume ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Manager_Resume(Manager* _manager)
{
	Read_Resume(_manager->m_read);
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Shutdown ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Manager_Shutdown(Manager* _manager)
{
	if(Read_Stop(_manager->m_read))
		return -3;
	
	if(Report_Stop(_manager->m_report))
		return -1;
	
	if(Detect_Stop(_manager->m_detect))
		return -2;
	
	if(Parse_Stop(_manager->m_parse))
		return -4;
	
	
	Report_Destroy(&_manager->m_report);
	Parse_Destroy(&_manager->m_parse);
	Storage_Destroy(&_manager->m_storage);
	Read_Destroy(&_manager->m_read);
	Detect_Destroy(&_manager->m_detect);
	
	return 0;
}










