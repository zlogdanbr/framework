#include "db.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

CSqlite::CSqlite( ):db(NULL)
{
    // db is made NULL
    QueryC.Clear();
}

CSqlite::~CSqlite()
{
    if ( db != NULL )
    {
        sqlite3_close(db);// close sqlite instance
    }

    QueryC.Clear();
}

bool CSqlite::bconnect( std::string& dbname )
{
    int rc = 0;

    /* Open database */
    rc = sqlite3_open(dbname.c_str(), &db);
    if( rc )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool CSqlite::bExecuteQuery( const char* query, int opt ) const
{
    char *zErrMsg = 0;
    int rc;

    // clear the query buffer because this is a static class
    QueryC.Clear();

    rc = sqlite3_exec(db, query, callback, NULL, &zErrMsg);// executes query

    // callback actually retrieves data
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return false;
    }

    return true;
}


inline bool CSqlite::SaveQueryToFile( ofstream& myfile )
{
    string YesOrNo="";

    cout << "Save Query to file?(yes/no):" << endl;
    getline(cin, YesOrNo);

    if( YesOrNo.compare("yes") == 0 )
    {
        string FileName="";
        cout << "Please input the filename>" ;
        getline(cin, FileName);
        string tp="";
        myfile.open( "reports//" + FileName );
        GetTimeStamp( tp );
        myfile << "Report generated at : " << tp << endl;
        return true;
    }

    return false;

}

void CSqlite::PrintQueryRaw( )
{
    int cnt = 0;
    int nreg = 0;

    int Registers =  ( QueryC.getQueryResult().size() / QueryC.getQuerySize() );
    auto header = QueryC.getQueryHeaders().rbegin();
    ofstream myfile;
    bool SaveToFile = SaveQueryToFile( myfile );


    if ( SaveToFile == true )
    {
        myfile << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
        myfile <<  "R " << nreg << endl;
    }

    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    cout <<  "R " << nreg << endl;

    for( auto ptr = QueryC.getQueryResult().rbegin(); ptr != QueryC.getQueryResult().rend();  ptr++ )
    {
        if ( SaveToFile == true )
        {
            myfile << "[ "<< *(header+cnt) << " ]: " ;
            myfile << *ptr << endl;
        }
        cout << "[ "<< *(header+cnt) << " ]: " ;
        cout << *ptr << endl;
        cnt++;
        if ( cnt == QueryC.getQuerySize() )
        {
            cnt = 0;
            nreg++;

            if ( nreg < Registers )
            {
                if ( SaveToFile == true )
                {
                    myfile << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                    myfile <<  "R " << nreg << endl;
                }
                cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
                cout <<  "R " << nreg << endl;
            }
        }
    }

    if ( SaveToFile == true )
    {
        myfile.close();
    }

    cout << Registers << " registers found." << endl;
}

int CSqlite::callback(void *data, int argc, char **argv, char **azColName)
{
    QueryC.setQuerySize(argc);

    //headers
    for(int i = 0; i < argc ; i++ )
    {
        if ( azColName[i] != nullptr )
        {
            QueryC.InsertQueryHeader( azColName[i] );
        }
    }

    for( int i = 0 ;  i < argc; i++ )
    {
        if ( argv[i] != nullptr )
        {
            QueryC.InsertQueryResult( argv[i] );
        }
        else
        {
            QueryC.InsertQueryResult( "N/A" );
        }
    }

    return 0;
}

inline void CSqlite::ReplaceCharsFromString( std::string& mystring, char whattoChange, char changeTo ) const
{
    for( int IndexOnString = 0; IndexOnString < (int)mystring.size() ; IndexOnString++ )
    {
        if ( mystring[ IndexOnString ] == whattoChange )
        {
            mystring[ IndexOnString ] =  changeTo;
        }
    }
}

void CSqlite::GetTimeStamp( std::string& stamp ) const
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [128];

    memset( buffer, 0x00, sizeof( buffer ) );
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime (buffer,16,"%d%m%Y_%H%M%S",timeinfo);

    stamp = buffer;
}
