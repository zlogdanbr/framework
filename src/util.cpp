#include "../include/util.h"

namespace util
{
	int iConvertBin2Ascii(char* bBindata, int iDataSize, char* szDataAscii )
	{
		// ex: 0x55 = U
		//     0x21 = !
		//     0x00 gets converted to . to avoid problems with NULL terminators
		//     control chars get converted to .

		if (( bBindata == NULL )||(szDataAscii) == NULL )
			return 1;

		for(int i = 0; i < iDataSize; i++ )
		{
			if ( bBindata[i] < 0x20 )
				szDataAscii[i] = '.';
			else
				szDataAscii[i] =  bBindata[i] ;
		}

		return 0;
	}

	/************************************************************************************
	* int iConvertBinArray2String( char* bBindata, 
	*												 int iDataSize,
	*												 char* szDataString )
	* description: Originally the data from the MF is binary, thus to print it in a file we must convert
	*			   it to an ASCII representation of this array of bytes. This convertion is not literal,
	*			   because each nibble of the bin values is converted to an ASCII byte. The output is
	*			   twice as big as the input
	* INPUT:		Original data buffer and its size
	* OUTPUT:	 	New buffer	
	* RETURNS:	    returns 0 OK else 1
	*************************************************************************************/
	int iConvertBinArray2String(	char* bBindata, 
					int iDataSize,
					char* szDataString ) 
	{	

		if (( bBindata == NULL )||(szDataString) == NULL )
			return 1;

		for(int i = 0; i < iDataSize ; i++)
		{
			char tmp[3];
			memset(tmp,0,3);
			sConvertHexBin2String((unsigned char)bBindata[i],(unsigned char*)tmp);
			memcpy((szDataString+2*i),tmp,2);
		}

		return 0;
	}
	
	/************************************************************************************
	*unsigned char* sConvertHexBin2String(unsigned char ch, unsigned char* buffer)
	* description: Originally the data from the MF is binary, thus to print it in a file we must convert
	*			   it to an ASCII representation of this array of bytes. This convertion is not literal,
	*			   because each nibble of the bin values is converted to an ASCII byte. The output is
	*			   twice as big as the input. This method actually converts each nibble of a byte to
	*			   its ascii representation.
	* INPUT:		A char
	* OUTPUT:	 	2 byte ASCII array representation
	* RETURNS:	    Pointer of the first byte of this array ( includes NULL terminator )
	*************************************************************************************/
	unsigned char* sConvertHexBin2String(unsigned char ch, unsigned char* buffer)
	{
	  char tmp[3];
	  memset(tmp,0,3);
	  if ( (ch&0x0F) == 0 )
	  {
		if ( ch == 0x00 )
		{
			tmp[0] = 0x30;
			tmp[1] = 0x30;
			tmp[2] = 0x00;
		}
		else
		{
			sprintf(tmp,"%x",ch);
			if ( tmp[1] == 0 )
				tmp[1] = 0x30;
		}
	  }
	  else
	  if ( ((ch&0xF0)<<4) == 0 )
	  {
		char cfix = 0x00;
		sprintf(tmp,"%x",ch);
		cfix = tmp[0];
		tmp[0] = 0x30;
		tmp[1] = cfix;
	  }
	  else
			sprintf(tmp,"%x",ch);
	  memcpy(buffer,tmp,3);	
	  return buffer;  
	}


	int ConvertHexStringToDecimalString( const char* HexInputString, std::string& Output )
	{
		// Given an input like "0E0AFF1245EE99"
		// convert it to "14 10 255 18 69 238 153"
		char Out[ 528 ];

		if ( HexInputString == NULL )
				return -1;

		memset( Out, 0x00, sizeof( Out ) );


		std::string tmp( HexInputString );
		Output.clear();
		int len = ( ( tmp.length() - 2 )/2 );

		for( int i = 0; i < len + 1 ; i ++ )
		{
			string tmp2 = tmp.substr( 2*i , 2 );
			int tmpInteger =  strtol( tmp2.c_str(), NULL, 16 );
			sprintf( Out + strlen( Out ), "%d", tmpInteger );
			if( i == len )
			{                   
				break;
			}
		}

		Output.append( Out );

		if ( Output.length() <= 0 )
		   return -1;
		return 0;
	}


	char* vSetCurrentTimeStamp( char* szTimeStamp )
	{
		time_t rawtime;
		struct tm * timeinfo;

		char buffer[32];
		memset(buffer,0,sizeof( buffer));

		if ( szTimeStamp == NULL )
		  return NULL;

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		// 01012000_HHMMSS
		strftime (buffer,16,"%d%m%Y_%H%M%S",timeinfo);
		memcpy(szTimeStamp,buffer,15);
		*(szTimeStamp+15)= 0x00;

		return szTimeStamp;

	}


	char* vSetCurrentTimeStamp( char* szTimeStamp, const char* szFormat, int isize )

	{
		time_t rawtime;
		struct tm * timeinfo;

		char buffer[32];
		memset(buffer,0,sizeof( buffer));

		if ( szTimeStamp == NULL )
				return NULL;

		time ( &rawtime );
		timeinfo = localtime ( &rawtime );

		strftime (buffer, isize, szFormat ,timeinfo);
		memcpy(szTimeStamp,buffer,isize);
		*(szTimeStamp+isize)= 0x00;

		return szTimeStamp;
	}

	int calculateCRC( char* buffer, int size )
	{
		int CRC = 0;
		int Index = 0;
		for( Index = 0; Index < size ; Index++ )
				CRC = CRC + buffer[ Index ];
		return CRC;
	}

	char* szConvertStringToData( char* stringbuffer, char* hexbuffer, int size )
	{
		int i = 0;
		for( i = 0 ; i < size/2 ; i++  )
		{
			char buf[3];
			memset(buf,0,3);
			memcpy(buf,&stringbuffer[2*i],2);
			buf[2] = 0;
			hexbuffer[ i ] = strtol( buf, NULL, 16 );
		}
		return hexbuffer;
	}
}
