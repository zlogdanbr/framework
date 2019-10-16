
#ifndef SLQINTERF
#define SLQINTERF

#include <cstdio>
#include <cstdlib>
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <deque>


template<class T>
class QueryContainer
{
public:
    QueryContainer()
    {
        QueryResult.clear(); ;
        QuerySize = 0;
    };

    virtual ~QueryContainer()
    {
    };

    inline void InsertQueryResult( T t )
    {
        QueryResult.push_front( t );
    };

    inline void InsertQueryHeader( T t )
    {
        QueryHeaders.push_front( t );
    };

    inline void Clear()
    {
        QueryResult.clear();
        QueryHeaders.clear();
        QuerySize = 0;
    };

    inline int getQuerySize()const{ return QuerySize; };
    inline void setQuerySize( int& Querysize ){ this->QuerySize = Querysize;};
    inline std::deque< T >& getQueryResult(){ return QueryResult; };
    inline std::deque< T >& getQueryHeaders(){ return QueryHeaders; };

private:
    std::deque< T > QueryResult;
    std::deque< T > QueryHeaders;
    int QuerySize;
};

static QueryContainer<std::string> QueryC;

class CSqlite
{
public:
    CSqlite();
    virtual ~CSqlite();
    bool bconnect( std::string& dbname );
    bool bExecuteQuery( const char* query, int opt ) const;
    void PrintQueryRaw( );

private:
    CSqlite( const CSqlite& );
    static int callback(void *data, int argc, char **argv, char **azColName);
    void GetTimeStamp( std::string& stamp ) const;
    inline void ReplaceCharsFromString( std::string& mystring, char whattoChange, char changeTo ) const;
    inline bool SaveQueryToFile( std::ofstream& myfile );
    sqlite3 *db;
    const char* path;
};

#endif
