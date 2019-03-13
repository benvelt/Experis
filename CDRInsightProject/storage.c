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

#include "storage.h"
#include "Protected_Hash.h"

/*
 MACROS DEFINITIONS
*/
#define SUBSCRIBERS_CAP		100
#define OPERATORS_CAP		150
#define OPERATORS_CAP		150
#define SUBSCRIBERS_LOCKS	1
#define OPERATORS_LOCKS		1
#define HASH_FUNC_VAR		5381
#define HASH_FUNC_MASK		5

/*
 STRUCTS DEFINITIONS
*/
struct Storage
{
	ProtectedHash* m_subscribersDS;
	ProtectedHash* m_operatorsDS;
	SubscriberCDR* m_spareSubStruct;
	OperatorCDR* m_spareOprStruct;
};

size_t Storage_EqualityFunc(char* _str1, char* _str2)
{
	return strcmp(_str1, _str2);
}


size_t Storage_HashFunc(char *str)
{
	unsigned long hash = HASH_FUNC_VAR;
	unsigned long c;

	while ((c = (unsigned long)*str++))
	{
		hash = ((hash << HASH_FUNC_MASK) + hash) + c;
	}
	return hash;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_Create ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
Storage* Storage_Create(void)
{
	Storage* storage = NULL;
	
	if(NULL == (storage = (Storage*)malloc(sizeof(Storage))))
		return NULL;
	
	storage->m_subscribersDS = ProtectedHash_Create(SUBSCRIBERS_CAP, SUBSCRIBERS_LOCKS, 
													(HashFunction)Storage_HashFunc, 
													(EqualityFunction)Storage_EqualityFunc);
	if(!storage->m_subscribersDS)
	{
		free(storage);
		return NULL;
	}
	
	storage->m_operatorsDS = ProtectedHash_Create(OPERATORS_CAP, OPERATORS_LOCKS, 
													(HashFunction)Storage_HashFunc, 
													(EqualityFunction)Storage_EqualityFunc);
	if(!storage->m_operatorsDS)
	{
		ProtectedHash_Destroy(&storage->m_subscribersDS,NULL, NULL);
		free(storage);
		return NULL;
	}
	
	storage->m_spareSubStruct = (SubscriberCDR*)malloc(sizeof(SubscriberCDR));
	if(!storage->m_spareSubStruct)
	{
		ProtectedHash_Destroy(&storage->m_operatorsDS,NULL, NULL);
		ProtectedHash_Destroy(&storage->m_subscribersDS,NULL, NULL);
		free(storage);
		return NULL;
	}
	
	storage->m_spareOprStruct = (OperatorCDR*)malloc(sizeof(OperatorCDR));
	if(!storage->m_spareOprStruct)
	{
		free(storage->m_spareSubStruct);
		ProtectedHash_Destroy(&storage->m_operatorsDS,NULL, NULL);
		ProtectedHash_Destroy(&storage->m_subscribersDS,NULL, NULL);
		free(storage);
		return NULL;
	}
	
	return storage;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_Destroy ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
void Storage_Destroy(Storage** _storage)
{
	if(_storage && *_storage)
	{
		free((*_storage)->m_spareOprStruct);
		free((*_storage)->m_spareSubStruct);
		ProtectedHash_Destroy(&(*_storage)->m_subscribersDS, NULL, free);
		ProtectedHash_Destroy(&(*_storage)->m_operatorsDS, NULL, free);
		free(*_storage);
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ SubscriberUpdateFunc ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void SubscriberUpdateFunc(SubscriberCDR* _exist, SubscriberCDR* _new)
{
	_exist->m_OutVoiceSameOperator 	+= _new->m_OutVoiceSameOperator;
	_exist->m_InVoiceSameOperator 	+= _new->m_InVoiceSameOperator;
	_exist->m_OutVoiceDiffOperator 	+= _new->m_OutVoiceDiffOperator;
	_exist->m_InVoiceDiffOperator 	+= _new->m_InVoiceDiffOperator;
	_exist->m_OutSMSsameOperator 	+= _new->m_OutSMSsameOperator;
	_exist->m_InSMSsameOperator 	+= _new->m_InSMSsameOperator;
	_exist->m_OutSMSdiffOperator 	+= _new->m_OutSMSdiffOperator;
	_exist->m_InSMSdiffOperator 	+= _new->m_InSMSdiffOperator;
	_exist->m_MBdownloaded 			+= _new->m_MBdownloaded;
	_exist->m_MBuploaded 			+= _new->m_MBuploaded;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Storage_InsertSubscriber ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int Storage_InsertSubscriber(Storage* _storage, CDRFormat* _cdrFmt)
{
	Map_Result mapRes;
	int isSameOperator = strcmp(_cdrFmt->m_operatorBrandName, _cdrFmt->m_partyOperatorBrandName);
	
	/* imsi */
	strcpy(_storage->m_spareSubStruct->m_imsi, _cdrFmt->m_imsi);
	/* calling same operator */
	_storage->m_spareSubStruct->m_OutVoiceSameOperator 	= 0;
	_storage->m_spareSubStruct->m_InVoiceSameOperator 	= 0;
	/* calling different operator */
	_storage->m_spareSubStruct->m_OutVoiceDiffOperator 	= 0;
	_storage->m_spareSubStruct->m_InVoiceDiffOperator 	= 0;
	/* sms to same operator */
	_storage->m_spareSubStruct->m_OutSMSsameOperator 	= 0;
	_storage->m_spareSubStruct->m_InSMSsameOperator 	= 0;
	/* sms to different operator */
	_storage->m_spareSubStruct->m_OutSMSdiffOperator 	= 0;
	_storage->m_spareSubStruct->m_InSMSdiffOperator 	= 0;
	/* internet */
	_storage->m_spareSubStruct->m_MBdownloaded 			= 0;
	_storage->m_spareSubStruct->m_MBuploaded 			= 0;
	
	/* check call type */
	if(!strcmp("MOC", _cdrFmt->m_callType))				/* MOC - outgoing voice call */
	{
		if(!isSameOperator)
			_storage->m_spareSubStruct->m_OutVoiceSameOperator += _cdrFmt->m_duration;
		else
			_storage->m_spareSubStruct->m_OutVoiceDiffOperator += _cdrFmt->m_duration;
	}
	else if(!strcmp("MTC", _cdrFmt->m_callType))		/* MTC - incoming voice call */
	{
		if(!isSameOperator)
			_storage->m_spareSubStruct->m_InVoiceSameOperator += _cdrFmt->m_duration;
		else
			_storage->m_spareSubStruct->m_InVoiceDiffOperator += _cdrFmt->m_duration;
	}
	else if(!strcmp("SMS-MO", _cdrFmt->m_callType))		/* SMS-MO - outgoing message */
	{
		if(!isSameOperator)
			_storage->m_spareSubStruct->m_OutSMSsameOperator += 1;
		else
			_storage->m_spareSubStruct->m_OutSMSdiffOperator += 1;
	}
	else if(!strcmp("SMS-MT", _cdrFmt->m_callType))		/* SMS-MT - incoming message */
	{
		if(!isSameOperator)
			_storage->m_spareSubStruct->m_InSMSsameOperator += 1;
		else
			_storage->m_spareSubStruct->m_InSMSdiffOperator += 1;
	}
	else if(!strcmp("GPRS", _cdrFmt->m_callType))		/* GPRS - internet */
	{
		_storage->m_spareSubStruct->m_MBdownloaded += _cdrFmt->m_download;
		_storage->m_spareSubStruct->m_MBuploaded += _cdrFmt->m_upload;
	}
	
	mapRes = ProtectedHash_Upsert(_storage->m_subscribersDS, _storage->m_spareSubStruct->m_imsi, 
									_storage->m_spareSubStruct, (ValueUpdateFuncion)SubscriberUpdateFunc);
	
	if(MAP_UPSERT_INSERT == mapRes)
	{
		_storage->m_spareSubStruct = (SubscriberCDR*)malloc(sizeof(SubscriberCDR));
		if(!_storage->m_spareSubStruct)
			return -2;
	}
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ OperatorUpdateFunc ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void OperatorUpdateFunc(OperatorCDR* _exist, OperatorCDR* _new)
{
	_exist->m_InVoiceCall 	+= _new->m_InVoiceCall;
	_exist->m_OutVoiceCall 	+= _new->m_OutVoiceCall;
	_exist->m_InSMS 		+= _new->m_InSMS;
	_exist->m_OutSMS 		+= _new->m_OutSMS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static Storage_InsertOperator ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static int Storage_InsertOperator(Storage* _storage, CDRFormat* _cdrFmt)
{
	Map_Result mapRes;
	
	strcpy(_storage->m_spareOprStruct->m_partyOperatorBrandName, _cdrFmt->m_partyOperatorBrandName);
	strcpy(_storage->m_spareOprStruct->m_OperatorTuple, _cdrFmt->m_operatorMCCnMNC);
	_storage->m_spareOprStruct->m_InVoiceCall 	= 0;
	_storage->m_spareOprStruct->m_OutVoiceCall 	= 0;
	_storage->m_spareOprStruct->m_InSMS 		= 0;
	_storage->m_spareOprStruct->m_OutSMS 		= 0;
	
	/* check call type */
	if(!strcmp("MTC", _cdrFmt->m_callType))				/* MTC - incoming voice call */
	{
		_storage->m_spareOprStruct->m_InVoiceCall += _cdrFmt->m_duration;
	}
	else if(!strcmp("MOC", _cdrFmt->m_callType))		/* MOC - outgoing voice call */
	{
		_storage->m_spareOprStruct->m_OutVoiceCall += _cdrFmt->m_duration;
	}
	else if(!strcmp("SMS-MT", _cdrFmt->m_callType))		/* SMS-MT - incoming message */
	{
		_storage->m_spareOprStruct->m_InSMS += 1;
	}
	else if(!strcmp("SMS-MO", _cdrFmt->m_callType))		/* SMS-MO - outgoing message */
	{
		_storage->m_spareOprStruct->m_OutSMS += 1;
	}
	
	mapRes = ProtectedHash_Upsert(_storage->m_operatorsDS, _storage->m_spareOprStruct->m_partyOperatorBrandName, 
									_storage->m_spareOprStruct, (ValueUpdateFuncion)OperatorUpdateFunc);
	
	if(MAP_UPSERT_INSERT == mapRes)
	{
		_storage->m_spareOprStruct = (OperatorCDR*)malloc(sizeof(OperatorCDR));
		if(!_storage->m_spareOprStruct)
			return -2;
	}
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_Insert ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_Insert(Storage* _storage, CDRFormat* _cdrFmt)
{
	int res;
	
	if(!_storage || !_cdrFmt)
		return -1;
	
	/* subscriber struct */
	res = Storage_InsertSubscriber(_storage, _cdrFmt);
	
	/* operator struct */
	if(strcmp(_cdrFmt->m_operatorBrandName, _cdrFmt->m_partyOperatorBrandName))
		res = Storage_InsertOperator(_storage, _cdrFmt);
			if(res)
				return -2;
	/* after the operation the struct is useless */
	free(_cdrFmt);
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_RetrieveSubscriber ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveSubscriber(Storage* _storage, char* _imsi, SubscriberCDR** _subStruct)
{
	if(!_storage || !_imsi || !_subStruct)
		return -1;
	
	if(MAP_KEY_NOT_FOUND_ERROR == ProtectedHash_Find(_storage->m_subscribersDS, _imsi, (void**)_subStruct))
		return -2;
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_RetrieveOperator ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveOperator(Storage* _storage, char* _partyOperator, OperatorCDR** _opeStruct)
{
	if(!_storage || !_partyOperator || !_opeStruct)
		return -1;
	
	if(MAP_SUCCESS != ProtectedHash_Find(_storage->m_operatorsDS, _partyOperator, (void**)_opeStruct))
		return -2;
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_RetrieveAllSubsribers ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveAllSubscribers(Storage* _storage, PrintSubReportToFile _func, FILE* _fileName)
{
	size_t res;
	
	if(!_storage || !_func || !_fileName)
		return -1;
	
	res = ProtectedHash_ForEach(_storage->m_subscribersDS, (KeyValueActionFunction)_func, _fileName);
	
	if(!res)
		return -2;
	
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Storage_RetrieveAllOperators ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/**
 * @brief 
 * @param[in] 
 * @param[in] 
 * @param[in] 
 * @return 
 */
int Storage_RetrieveAllOperators(Storage* _storage, PrintOpeReportToFile _func, FILE* _fileName)
{
	size_t res;
	
	if(!_storage || !_func || !_fileName)
		return -1;
	
	res = ProtectedHash_ForEach(_storage->m_operatorsDS, (KeyValueActionFunction)_func, _fileName);
	
	if(!res)
		return -2;
	
	return 0;
}








