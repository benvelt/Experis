/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

/** 
 *  @file parse.h
 *  @brief API of the parse library.
 *
 *  @author Ben Velt  (ben.velt@gamil.com)
 *
 *  @bug No known bugs! 
 */

#ifndef __PARSE_H__
#define __PARSE_H__

#include "read.h"
#include "storage.h"
#include "cdr_format.h"

typedef struct Parse Parse;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Allocate and initiate Parse*.
 * @param[in] _numOfParsers - number of threads that will do the parsing work.
 * @param[in] _readP - an existing Read pointer.
 * @param[in] _storeP - an existing Store pointer.
 * @return If success so return Parse*, else NULL.
 */
Parse* Parse_Create(long _numOfParsers, Read* _readP, Storage* _StorageP);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Activate the parsing operation.
 * @param[in] _parse - a previously created Parse pointer.
 * @return Success or failure value.
 * @retval 0 if success;
 * @retval -1 if _parse is null;
 * @retval -2 if can not create parsers.
 */
int Parse_Run(Parse* _parse);

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
int Parse_Stop(Parse* _parse);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Line ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Parsing lines to desired format (CDRFormat).
 * @param[in] _CDRRecordLine - the line needed for parsing.
 * @return CDRFormat* or null if failed to parse.
 * @retval CDRFormat* on success;
 * @retval NULL if can not allocate the CDRFormat*.
 */
CDRFormat* Parse_Line(char* _CDRRecordLine);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Parse_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Deallocate a previously created Parse struct.
 * @param[in] _parse - Parse to deallocate.
 */
void Parse_Destroy(Parse** _parse);

#endif /* __PARSE_H__ */
