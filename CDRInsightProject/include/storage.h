/******************************************************************************************************
	Author :					Ben Velt
	Creation date :				25.08.18
	Date last modified :		03.09.18
******************************************************************************************************/

/** 
 *  @file storage.h
 *  @brief API of the manager library.
 *
 *  @author Ben Velt  (ben.velt@gamil.com)
 *
 *  @bug No known bugs! 
 */

#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* rename, fopen, fclose, fgets, feof */

#include "cdr_format.h"

typedef struct Storage Storage;

typedef struct SubscriberCDR
{
	char	m_imsi[16];
	size_t	m_OutVoiceSameOperator;
	size_t	m_InVoiceSameOperator;
	size_t	m_OutVoiceDiffOperator;
	size_t	m_InVoiceDiffOperator;
	size_t	m_OutSMSsameOperator;
	size_t	m_InSMSsameOperator;
	size_t	m_OutSMSdiffOperator;
	size_t	m_InSMSdiffOperator;
	size_t	m_MBdownloaded;
	size_t	m_MBuploaded;
} SubscriberCDR;

typedef struct OperatorCDR
{
	char	m_partyOperatorBrandName[64];
	char	m_OperatorTuple[16];
	size_t	m_InVoiceCall;
	size_t	m_OutVoiceCall;
	size_t	m_InSMS;
	size_t	m_OutSMS;
} OperatorCDR;

typedef int (*PrintSubReportToFile)(char* _key, SubscriberCDR* _subStruct, FILE* _reportFileName);
typedef int (*PrintOpeReportToFile)(char* _key, OperatorCDR* _opeStruct, FILE* _reportFileName);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
Storage* Storage_Create(void);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
void Storage_Destroy(Storage** _storage);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_Insert ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_Insert(Storage* _storage, CDRFormat* _cdrFmt);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_GetAllSubscribers ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveSubscriber(Storage* _storage, char* _imsi, SubscriberCDR** _subStruct);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_RetrieveOperator ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveOperator(Storage* _storage, char* _partyOperator, OperatorCDR** _opeStruct);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_RetrieveAllSubsribers ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveAllSubscribers(Storage* _storage, PrintSubReportToFile _func, FILE* _fileName);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_RetrieveAllOperators ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveAllOperators(Storage* _storage, PrintOpeReportToFile _func, FILE* _fileName);

#endif /* __STORAGE_H__ */













