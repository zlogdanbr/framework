#ifndef _LOGSYS_
#define _LOGSYS_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <sys/types.h>
#include <sys/time.h> 
#include <netinet/in.h>
#include <errno.h>
#include <syslog.h>

using namespace std;

/*--------------------------------------------------------------------------------------------
*		Logs
*               Classe utilizada para logar dados ( singleton)
---------------------------------------------------------------------------------------------*/
class LogData
{
private:
	// Singleton
	LogData() {};
	LogData(const LogData&);
	const LogData& operator=(const LogData&);

	char* vSetCurrentTimeStamp( char* szTimeStamp, int type ) const;
public:
	// controlled instantiation
	static LogData& GetInstance()
	{
		// static objects are constructed only once
		static LogData OnlyInstance;
		return OnlyInstance;
	}
	
	// funcoes de log
	void StartLoging() const;
	void StopLoging() const;
        void LogMsg( const char* ) const;
};

#endif

