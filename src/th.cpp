/*
*	-----------------------------------------------------------------
*	Implementacao threads
*
*	Daniel V. Gomes daniel.vasconcelosgomes@gmail.com
*	http://danielvgomes.webs.com/
*       ------------------------------------------------------------------
*/

#include "../include/th.h"

ThreadWrapper::ThreadWrapper(  )
{
     // contador das threads usadas no pool
     NumberOfCrtThreads = 0;
     FullStack = false;
}

void ThreadWrapper::AddRun( void* (*f)(void*) )
{
    // executa a thread atraves da funcao passada para f
    if ( NumberOfCrtThreads < MAX_THREADS )
    {
        ThreadInfo InitThreadData;
        InitThreadData.NoThread = NumberOfCrtThreads;
        pthread_create( &(InitThreadData.pthreadObj) , NULL, f, NULL);
        NumberOfCrtThreads++;
        ThreadDataPool.push_back(InitThreadData);
    }

    else
    {
        FullStack = true;
    }
}

void ThreadWrapper::Join() const
{
    // join da thread
    for( auto It = ThreadDataPool.cbegin(); It != ThreadDataPool.cend(); It++ )
    {
	    pthread_join( It->pthreadObj,NULL);
    }

}








