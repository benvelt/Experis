/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

/** 
 *  @file detect.h
 *  @brief API of the detect library.
 *
 *  @author Ben Velt  (ben.velt@gamil.com)
 * 
 *  @bug No known bugs! 
 */

#ifndef __DETECT_H__
#define __DETECT_H__

typedef struct Detect Detect;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Allocate and initiate Detect*.
 * @param[in] _newCdrDirPath - the new cdr files directory path.
 * @param[in] _workCdrDirPath - the work cdr files directory path.
 * @param[in] _fileMask - the files to work with.
 * @return If success so return Detect*, else NULL.
 */
Detect* Detect_Create(char* _newCdrDirPath, char* _workCdrDirPath, char* _fileMask);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_GetFileName ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Get file name from Detect struct.
 * @param[in] _detect - the Detect to get file name from.
 * @return char* if success or NULL if fail.
 */
char* Detect_GetFileName(Detect* _detect);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Activate the detecting operation.
 * @param[in] _detect - a previously created Detect pointer.
 * @return Success or failure value.
 * @retval 0 if success;
 * @retval -1 if _detect is null;
 * @retval -2 if can not create detector.
 */
int Detect_Run(Detect* _detect);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Stop ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Stop a previously call of Detect_Run.
 * @param[in] _detect - a previously created Detect pointer.
 * @return success or error value.
 * @retval 0 for success;
 * @retval -1 if _detect is null;
 * @retval -2 if detector cancelling error;
 * @retval -3 if detector waiting error;
 */
int Detect_Stop(Detect* _detect);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Detect_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Deallocate a previously created Detect struct.
 * @param[in] _detect - Detect to deallocate.
 */
void Detect_Destroy(Detect** _detect);

#endif /* __DETECT_H__ */
