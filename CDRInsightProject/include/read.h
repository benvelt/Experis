/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

/** 
 *  @file read.h
 *  @brief API of the read library.
 *
 *  @author Ben Velt  (ben.velt@gamil.com)
 *
 *  @bug No known bugs! 
 */

#ifndef __READ_H__
#define __READ_H__

#include "detect.h"

/*
 STRUCTS DEFINITIONS
*/
typedef struct Read Read;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Allocate and initiate Read*.
 * @param[in] _numOfReaders - number of threads that will do the reading work.
 * @param[in] _detectP - an existing Detect*.
 * @return If success so return Parse*, else NULL.
 */
Read* Read_Create(Detect* _detectP, long _numOfReaders, char* _workDir, char* _doneDir);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Activate the reading operation.
 * @param[in] _read - a previously created Read pointer.
 * @return Success or failure value.
 * @retval 0 if success;
 * @retval -1 if _read is null;
 * @retval -2 if can not create reader.
 */
int Read_Run(Read* _read);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_GetLine ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Extract lines from the DS of Read.
 * @param[in] _read - a previously created Read* to extract lines from.
 * @return char* of the extracted line or NULL if _read not exist.
 */
char* Read_GetLine(Read* _read);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Resume ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Resume a previously Read_Pause readers job.
 * @param[in] _read - a previously created Read* to extract lines from.
 */
void Read_Resume(Read* _read);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Pause ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Pause a previously Read_Run call.
 * @param[in] _read - a previously created Read* to extract lines from.
 */
void Read_Pause(Read* _read);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Stop ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Stop a previously call of Read_Run.
 * @param[in] _read - a previously created Read pointer.
 * @return success or error value.
 * @retval 0 for success;
 * @retval -1 if _read is null;
 * @retval -2 if readers cancelling error;
 * @retval -3 if readers waiting error;
 */
int Read_Stop(Read* _read);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Read_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Deallocate a previously created Read struct.
 * @param[in] _parse - Parse to deallocate.
 */
void Read_Destroy(Read** _read);

#endif /* __READ_H__ */
