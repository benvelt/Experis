#ifndef __CDR_FORMAT_H__
#define __CDR_FORMAT_H__

typedef struct CDRFormat
{
	char m_imsi[16];
	char m_operatorBrandName[64];
	char m_operatorMCCnMNC[8];
	char m_callType[8];
	long m_duration;
	long m_download;
	long m_upload;
	char m_partyOperatorBrandName[64];
} CDRFormat;

#endif /* __CDR_FORMAT_H__ */ 
