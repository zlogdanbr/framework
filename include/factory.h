#ifndef _MYFACTORY
#define _MYFACTORY
#include <iostream>
#include <map>

using namespace std;

// Base pure virtual class
class BasePtr
{
public:
    BasePtr(){};
    virtual ~BasePtr(){};
    virtual int DoSomething() = 0;
};

// Objects created by factory
// Object 1
class Derived1: public BasePtr
{
public:
    Derived1():BasePtr(){};
    virtual ~Derived1(){ cout << "Destructor Derived 1" << endl;};
    virtual int DoSomething()
    { 
        cout << "Do Something derived 1" << endl ; 
        return 0;
    };
};
// Object 2
class Derived2: public BasePtr
{
public:
    Derived2():BasePtr(){};
    virtual ~Derived2(){ cout << "Destructor Derived 2" << endl;};
    virtual int DoSomething()
    { 
        cout << "Do Something derived 2" << endl ;
        return 0;
    };
};

// Object 3
class Derived3: public BasePtr
{
public:
    Derived3():BasePtr(){};
    virtual ~Derived3(){ cout << "Destructor Derived 3" << endl;};
    virtual int DoSomething()
    { 
        cout << "Do Something derived 3" << endl ; 
        return 0;
    };
};


// Class factory
class MyClassFactory
{
public:
    BasePtr* getObjc(int option, BasePtr* ptr ) const;
};

// Queue used to store task
class MyQueue
{
public:
    MyQueue()
    {
    }
    ~MyQueue();
    void Register( BasePtr* ptr, int o );
    void Run(int myitem)const;
private:
    map< BasePtr*, int > myQueue;
    MyClassFactory fact{};
};

#endif

