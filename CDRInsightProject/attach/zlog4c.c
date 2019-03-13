/*****************************************************************************************************************
 * Author :					Ben Velt
 * Creation date :			23.07.18
 * Date last modified :
 * Description : 			inittial, write and terminate a Logger file in order to document entries.
******************************************************************************************************************/

#include "zlog4c.h"

#define MAX_ERR_LNG 15
#define FILE_NAME_LNG 256
#define BUF_LNG 26
#define PASS 1
#define FAIL 0

#define DEBUG_PARAM		buffer, s_zlogStat.m_pid, pthread_self(), e_sLogLvl[_logLvl], _mdlName,\
						_funcName, _fileName, _line
#define FORMAT_DPRT		"%s %d %ld %c %s %s@%s:%d "


#define NDEBUG_PARAM	buffer, s_zlogStat.m_pid, pthread_self(), e_sLogLvl[_logLvl], _mdlName
#define FORMAT_PRT		"%s %d %ld %c %s "

static const char* c_DEFAULT_CONFIG_FILE = "app.log.config";
static const char* c_DEFAULT_LOG_FILE = "logfile.txt";


static const char* logStr[] = 
{
	"TRACE",
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR",
	"CRITICAL",
	"SEVERE",
	"FATAL",
	"NONE"
};

static const char e_sLogLvl[] = {'T', 'D', 'I', 'W', 'E', 'C', 'S', 'F', 'N'};

static struct s_zlogStat
{
	Log_Level	m_logLvl;
	FILE*		m_loggerFile;
	pid_t		m_pid;
} s_zlogStat;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ static GetTime ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static char* GetTime(char* _buffer)
{
	time_t timer;
	struct tm* tm_info;
	
	time(&timer);
	tm_info = localtime(&timer);
	
	strftime(_buffer, BUF_LNG, "%Y-%m-%d %H:%M:%S", tm_info);
	
	return _buffer;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ zlog_init ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int zlog_init(const char* _configFile)
{
	FILE* filePtr = NULL;
	char error[MAX_ERR_LNG];
	char logDst[FILE_NAME_LNG] = "";
	int i, retVal = 0;
	
	if(s_zlogStat.m_loggerFile) return retVal;
	
	atexit(zlog_terminate);
	
	s_zlogStat.m_pid = getpid();
	/* define the default Log_Level: */
	s_zlogStat.m_logLvl = LOG_TRACE;
	
	filePtr = fopen((_configFile) ? _configFile : c_DEFAULT_CONFIG_FILE ,"r");
	
	if(filePtr)
	{
		fscanf(filePtr,"%s%*[^\n]", error);
		fscanf(filePtr,"%s%*[^\n]", logDst);
		fclose(filePtr);
		
		for(i = LOG_TRACE; i <= LOG_NONE; ++i)
			if(0 == strcmp(logStr[i], error)) s_zlogStat.m_logLvl = i;
		
		filePtr = fopen(logDst ,"w");
		
		if(!filePtr)
		{
			filePtr = fopen(c_DEFAULT_LOG_FILE, "w");
			if(!filePtr) return -1;
		}
	}
	else
	{
		filePtr = fopen(c_DEFAULT_LOG_FILE ,"w");
		if(!filePtr) return -2;
		
		fscanf(filePtr,"%s%*[^\n]", error);
		fscanf(filePtr,"%s%*[^\n]", logDst);
		fclose(filePtr);
		
		for(i = LOG_TRACE; i <= LOG_NONE; ++i)
			if(0 == strcmp(logStr[i], error)) s_zlogStat.m_logLvl = i;
		
		filePtr = fopen(logDst ,"w");
		
		if(!filePtr)
		{
			filePtr = fopen(c_DEFAULT_LOG_FILE, "w");
			if(!filePtr) retVal = -1;
		}
	}
	
	s_zlogStat.m_loggerFile = filePtr;
	
	return 1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ zlog_write ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef DEBUG
int zlog_write(Log_Level _logLvl, const char* _mdlName,const char* _funcName,const char* _fileName, int _line, char* _msgFmt,...)
#else
int zlog_write(Log_Level _logLvl, const char* _mdlName, char* _msgFmt, ...)
#endif /* DEBUG */
{
	char buffer[BUF_LNG];
	va_list arg;
	
	if(s_zlogStat.m_loggerFile)
	{
		if(_logLvl >= s_zlogStat.m_logLvl)
		{
			GetTime(buffer);
#ifdef DEBUG
			fprintf(s_zlogStat.m_loggerFile,FORMAT_DPRT, DEBUG_PARAM);
#else
			fprintf(s_zlogStat.m_loggerFile,FORMAT_PRT, NDEBUG_PARAM);
#endif /* DEBUG */
			
			/* print message */
			va_start(arg, _msgFmt);
			vfprintf(s_zlogStat.m_loggerFile, _msgFmt, arg);
			va_end(arg);
			fprintf(s_zlogStat.m_loggerFile,"\n");
			return PASS;
		}
	}
	return FAIL;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ zlog_terminate ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void zlog_terminate()
{
	if(s_zlogStat.m_loggerFile) fclose(s_zlogStat.m_loggerFile);
}

