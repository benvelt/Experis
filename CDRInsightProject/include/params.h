/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

/** 
 *  @file params.h
 *  @brief Read a config file parameters and initiate Params struct.

 *  @config file standard for example:
 *     fileMask = .cdr
 *     newDir = ./new_CDR_files/
 *     workDir = ./work_CDR_files/
 *     doneDir = ./done_CDR_files/
 *     reportsDir = ./Reports/
 *     readers = 4
 *     parsers = 4
 *     reporters = 4

 *  @author Ben Velt  (ben.velt@gamil.com)
 *
 *  @bug No known bugs! 
 */

#ifndef __PARAMS_H__
#define __PARAMS_H__

typedef struct Params 
{
	long 		m_parseThreads;
	long 		m_readThreads;
	long 		m_reportThreads;
	char 		m_newCdrFilesDir[50];
	char 		m_workCdrFilesDir[50];
	char 		m_doneCdrFilesDir[50];
	char 		m_reportsDir[50];
	char 		m_fileMask[10];
} Params;


/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Params_ReadConfigFile ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Read an exist configuration file.
 * @param[in] _configFilePath - 
 * @param[in] _params - a previously allocated Params struct.
 * @return Success or failure value.
 * @retval 0 if success;
 * @retval -1 if _configFilePath or _params is null;
 * @retval -2 if can not open _configFilePath;
 * @retval -3 if _configFilePath file not by standard;
 */
int Params_ReadConfigFile(char* _configFilePath, Params* _params);


#endif /* __PARAMS_H__ */













