#include "factory.h"

BasePtr* MyClassFactory::getObjc(int option, BasePtr* ptr ) const
{
    switch ( option )
    {
        case 1:
            ptr =  new Derived1;
            break;
        case 2:
            ptr =  new Derived2;
            break;
        case 3:
            ptr =  new Derived3;
            break;
        default:
            ptr = nullptr;
    }
    return ptr;
}

void MyQueue::Register(BasePtr* ptr, int o )
{
   ptr = fact.getObjc( o , ptr );
   if ( ptr != nullptr )
   {
        myQueue.insert( std::pair< BasePtr*, int >(ptr, o) );
   }
   else
   {
        cout << "Object-" << o <<  " cannot be created, does not exist declaration" << endl;
   }
}

MyQueue::~MyQueue()
{
    for( auto mptr = myQueue.cbegin(); mptr != myQueue.cend(); mptr++ )
    {
       BasePtr* p = mptr->first;
       if ( p != NULL )
       {
            delete p;
            p = NULL;
       }
    }
}

void MyQueue::Run( int myitem ) const
{
    for( auto mptr = myQueue.cbegin(); mptr != myQueue.cend(); mptr++ )
    {
       if ( myitem == mptr->second )
       {
            BasePtr* p = mptr->first;
            p->DoSomething();
       }
    }
}

//int main()
//{
//    BasePtr* ptr1 = NULL;
//    BasePtr* ptr2 = NULL;
//    BasePtr* ptr3 = NULL;
//    MyQueue q{};

//    q.Register( ptr1, 1 );
//    q.Register( ptr2, 2 );
//    q.Register( ptr3, 3 );
//    q.Register( ptr3, 325 );

//    q.Run(1);
//    q.Run(325);


//    return 0;
//}

