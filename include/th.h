/*
*	-----------------------------------------------------------------
*	Modulo de threads
*	Daniel V. Gomes daniel.vasconcelosgomes@gmail.com
*	http://danielvgomes.webs.com/
*       ------------------------------------------------------------------
*/
#ifndef _THREADS_
#define _THREADS_

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
#include <unistd.h>


using namespace std;

#define MAX_THREADS 10
/*--------------------------------------------------------------------------------------------
*		Threads
---------------------------------------------------------------------------------------------*/
typedef struct Data
{
    int NoThread;
    pthread_t pthreadObj;
} ThreadInfo;

typedef vector< ThreadInfo > Threads;

class ThreadWrapper
{
public:
    ThreadWrapper();
    void AddRun(void* (*f)(void*) );
    int GetNumberOfCrtThreads()const{ return NumberOfCrtThreads ;};
    const pthread_t& getThreadFromSequence( int index )const{ return ThreadDataPool[index].pthreadObj;};
    void Join() const;
    bool getFullStack()const{ return FullStack ;};
private:
    Threads ThreadDataPool;
    bool FullStack;
    int NumberOfCrtThreads;
};

#endif


