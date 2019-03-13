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

#ifndef __UI_H__
#define __UI_H__

#include "manager.h"
#include "storage.h"

#define DEFAULT_OPERATORS_REPORT "operators_report.txt"
#define DEFAULT_SUBSCRIBERS_REPORT "subscribers_report.txt"

typedef struct UI UI;

typedef struct Request
{
	char 	m_fileName[256];
	int 	m_requestType; /* 0 for sub report | 1 for ope report */
} Request;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Allocate and initiate Detect*.
 * @param[in] _manager - a previously created Manager pointer.
 * @param[in] _storage - a previously created Storage pointer.
 * @return If success so return UI*, else NULL.
 */
UI* UI_Create(Manager* _manager, Storage* _storage);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Activate the ui'ing operation.
 * @param[in] _ui - a previously created UI pointer.
 * @return Success or failure value.
 * @retval 0 if success;
 * @retval -1 if _ui is null;
 * @retval -2 if can not create uier.
 */
int UI_Run(UI* _ui);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Wait ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Wait for return of previously UI_Run call.
 * @param[in] _ui - a previously created UI pointer.
 * @return Success or failure value.
 * @retval 0 if success;
 * @retval -1 if _ui is null.
 */
int UI_Wait(UI* _ui);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_GetRequest ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Get request from the _ui request DS.
 * @param[in] _ui - a previously created UI pointer.
 * @param[in] _req - a Request container.
 * @return Success or failure value.
 * @retval 0 if success;
 */
int UI_GetRequest(UI* _ui, Request** _req);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ UI_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Deallocate a previously created UI struct.
 * @param[in] _ui - UI to deallocate.
 */
void UI_Destroy(UI** _ui);

#endif /*__UI_H__*/
