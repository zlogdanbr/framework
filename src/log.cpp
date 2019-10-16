#include "../include/log.h"

// Obtem a leitura atual do relogio
char* LogData::vSetCurrentTimeStamp( char* szTimeStamp, int type )const
{
        time_t rawtime;
        struct tm * timeinfo;

        char buffer[32];
        memset(buffer,0,sizeof( buffer));

        if ( szTimeStamp == NULL )
          return NULL;

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

	if ( type == 0 )
	{
		//2014-04-08 20:00:00
		// %Y-%m-%d %H:%M:%S
		strftime (buffer,20 ,"%Y-%m-%d_%H-%M-%S",timeinfo);
		memcpy(szTimeStamp,buffer,19);
		*(szTimeStamp+19)= 0x00;
	}
	else
	{
		strftime (buffer,20 ,"%Y-%m-%d_%H:%M:%S",timeinfo);
		memcpy(szTimeStamp,buffer,19);
		*(szTimeStamp+19)= 0x00;
	}

	return szTimeStamp;

}

// incializa o log de sistema
void LogData::StartLoging() const
{
	openlog(NULL, 0, LOG_USER);
	syslog(LOG_INFO, "Inicio do log." );
}


// finaliza o log de sistema
void LogData::StopLoging()const
{
	closelog();
}

// Escreve mensagem no log de sistema
void LogData::LogMsg( const char* Msg ) const
{
	if ( Msg == NULL )
		return;
	syslog(LOG_NOTICE, "%s\n", Msg );

}
