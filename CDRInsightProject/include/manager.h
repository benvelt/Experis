/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

/** 
 *  @file manager.h
 *  @brief API of the manager library.
 *
 *  @author Ben Velt  (ben.velt@gamil.com)
 *
 *  @bug No known bugs! 
 */

#ifndef __MANAGER_H__
#define __MANAGER_H__

/*
 DEFAULT MACROS DEFINITIONS
*/
#define DEFAULT_NEW_CDR_DIR 	"./new_CDR_files/"
#define DEFAULT_WORK_CDR_DIR 	"./work_CDR_files/"
#define DEFAULT_DONE_CDR_DIR 	"./done_CDR_files/"
#define DEFAULT_REPORTS_DIR 	"./Reports/"
#define DEFAULT_FILE_MASK 		".cdr"
#define DEFAULT_PARSERS			1
#define DEFAULT_READERS			1
#define DEFAULT_REPORTERS 		1

typedef struct Manager Manager;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Manager* Manager_Create(void);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Manager_Destroy(Manager** _manager);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Run ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Manager_Run(Manager* _manager);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Shutdown ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Manager_Shutdown(Manager* _manager);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Resume ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Manager_Resume(Manager* _manager);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Manager_Pause ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int Manager_Pause(Manager* _manager);







#endif /* __MANAGER_H__ */


