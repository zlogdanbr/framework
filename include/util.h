#ifndef _UTILDVG_
#define _UTILDVG_
#include <string>
using namespace std;

#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace util
{
	int ConvertHexStringToDecimalString( const char* HexInputString, std::string& Output ) ;
	char* vSetCurrentTimeStamp( char* szTimeStamp );
	char* vSetCurrentTimeStamp( char* szTimeStamp, int isize );
	int calculateCRC( char* buffer, int size );
	unsigned char* sConvertHexBin2String( unsigned char ch, 
					      unsigned char* buffer);
	char* szConvertStringToData( char* stringbuffer, char* hexbuffer, int size);
}
#endif
