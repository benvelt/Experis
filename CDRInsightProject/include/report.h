/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

/** 
 *  @file report.h
 *  @brief API of the report library.
 *
 *  @author Ben Velt  (ben.velt@gamil.com)
 * 
 *  @bug No known bugs! 
 */


#ifndef __REPORT_H__
#define __REPORT_H__

#include "storage.h"
#include "UI.h"

/*
 MACROS DEFINITIONS
*/
#define SIGUSR1_SUBSCRIBERS_REPORT 	"subscribers_report_sigusr1.txt"
#define SIGUSR2_OPERATORS_REPORT 	"operators_report_sigusr2.txt"

typedef struct Report Report;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Allocate and initiate Report*.
 * @param[in] _storage - a previously created Storage pointer.
 * @param[in] _ui - a previously created UI pointer.
 * @param[in] _reportsDir - the dir to write reports to.
 * @param[in] _numOfReporters - number of reporters that will do the Report_Run.
 * @return If success so return Detect*, else NULL.
 */
Report* Report_Create(Storage* _storage, UI* _ui, char* _reportsDir, long _numOfReporters);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Activate the reporting operation.
 * @param[in] _report - a previously created Report pointer.
 * @return Success or failure value.
 * @retval 0 if success;
 * @retval -1 if _report is null;
 * @retval -2 if can not create reporter.
 */
int Report_Run(Report* _report);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Stop ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Stop a previously call of Report_Run.
 * @param[in] _report - a previously created Report pointer.
 * @return success or error value.
 * @retval 0 for success;
 * @retval -1 if _report is null;
 * @retval -2 if reporter cancelling error;
 * @retval -3 if reporter waiting error;
 */
int Report_Stop(Report* _report);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Deallocate a previously created Report struct.
 * @param[in] _report - a previously created Report pointer.
 */
void Report_Destroy(Report** _report);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_AllSubscribers ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Print to file the Storage subscribers data.
 * @param[in] _report - a previously created Report pointer.
 * @param[in] _reportFileName - the file name to wrote to.
 * @return Success or failure value.
 * @retval 0 for success;
 * @retval -1 if cannot open _reportFileName.
 */
int Report_AllSubscribers(Report* _report, char* _reportFileName);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Report_AllSubscribers ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief Print to file the Storage operators data.
 * @param[in] _report - a previously created Report pointer.
 * @param[in] _reportFileName - the file name to wrote to.
 * @return Success or failure value.
 * @retval 0 for success;
 * @retval -1 if cannot open _reportFileName.
 */
int Report_AllOperators(Report* _report, char* _reportFileName);

#endif /*__REPORT_H__*/
