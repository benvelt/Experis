/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			23.07.18
 * Date last modified :
 * Description : 			inittial, write and terminate a Logger file in order to document entries.
******************************************************************************************************************/

#ifndef __ZLOG4C_H__
#define __ZLOG4C_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdarg.h>

#define PASS 1
#define FAIL 0

#ifdef DEBUG
	#define ZLOG(LOG_LVL,MDL_NAME,MSG,...)	do {\
											zlog_write(((LOG_LVL)),((MDL_NAME)),__func__,__FILE__,__LINE__,\
												((MSG)),__VA_ARGS__);\
											} while(0)
#else
	#define ZLOG(LOG_LVL,MDL_NAME,MSG,...)	do {\
											zlog_write(((LOG_LVL)),((MDL_NAME)),((MSG)),__VA_ARGS__);\
											} while(0)
#endif /* DEBUG */

typedef enum Log_Level {
	LOG_TRACE = 0		/* Trace message usually very detailed */
	,LOG_DEBUG			/* A message useful for debugging */
	,LOG_INFO			/* Informative message */
	,LOG_WARNING		/* Warning */
	,LOG_ERROR			/* An error occurred */
	,LOG_CRITICAL		/* Critical error */
	,LOG_SEVERE			/* Server error requiring immediate intervention */
	,LOG_FATAL			/* Fatal error signaling an emergency */
	,LOG_NONE			/* Used only in configuration file */
} Log_Level;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ zlog_init ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief This function will receive Log Configuration File to check the Log_Level and destination file to write into.
 * @params[in] _configFile A previously created file with defined level and file.
 * @returns pointer to Zlog struct.
 * @retval NULL if _configFile is null;
 * @retval NULL when unable to open the destination file;
 * @retval NULL when unable to allocate;
 * @retval NULL when unable to open _configFile;
 * @retval NULL when unable to allocate.
 * @note if unable to open _configFile so the default is: Log_Level = LOG_ERROR, destination file = logfile.log.
 * @note the following errors: TRACE, DEBUG, INFO, WARNING, ERROR, CRITICAL, SEVERE, FATAL, NONE.
 */
int zlog_init(const char* _configFile);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ zlog_write ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief Writes to a logged file a given entry.
 * @params[in] _logLvl - the defined Log_Level of the entry;
 * @params[in] _mdlName - the module name of the entry;
 * @params[in] _funcName - the function which the entry is in;
 * @params[in] _fileName - the file name which the entry is in;
 * @params[in] _line - the line name which the entry is in;
 * @params[in] _msgFmt - the format of the variables (...) in message;
 * @returns success or fail.
 * @retval PASS when writing to logger file;
 * @retval FAIL when not writing to logger file;
 */
#ifdef DEBUG
int zlog_write(Log_Level _logLvl, const char* _mdlName,const char* _funcName,const char* _fileName, int _line, char* _msgFmt,...);
#else
int zlog_write(Log_Level _logLvl, const char* _mdlName, char* _msgFmt, ...);
#endif /* DEBUG */

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ zlog_terminate ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/** 
 * @brief close a previously opened logger file.
 * @note this function will be called automatically when the program is finished after calling to zlog_init.
 */
void zlog_terminate(void);

#endif /* __ZLOG4C_H__ */

