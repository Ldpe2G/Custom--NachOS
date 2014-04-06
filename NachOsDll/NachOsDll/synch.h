// synch.h 
//	Data structures for synchronizing threads.
//
//	Three kinds of synchronization are defined here: semaphores,
//	locks, and condition variables.
//
//	Note that all the synchronization objects take a "name" as
//	part of the initialization.  This is solely for debugging purposes.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// synch.h -- synchronization primitives.  

#include "copyright.h"
#include "thread.h"
#include "list.h"


#ifndef SYNCH_H
#define SYNCH_H


//#include "main.h"

// Interrupts can be disabled (IntOff) or enabled (IntOn)
//enum IntStatus { IntOff, IntOn };		/* Liang DePeng + */
const int IntOff = 0;
const int IntOn = 1;

// The following class defines a "semaphore" whose value is a non-negative
// integer.  The semaphore has only two operations P() and V():
//
//	P() -- waits until value > 0, then decrement
//
//	V() -- increment, waking up a thread waiting in P() if necessary
// 
// Note that the interface does *not* allow a thread to read the value of 
// the semaphore directly -- even if you did read the value, the
// only thing you would know is what the value used to be.  You don't
// know what the value is now, because by the time you get the value
// into a register, a context switch might have occurred,
// and some other thread might have called P or V, so the true value might
// now be different.

/**** delete
 * Liang DePeng - */
/*
class Semaphore{
  public:
    Semaphore(char* debugName, int initialValue);	// set initial value
    ~Semaphore();   					// de-allocate semaphore
    char* getName() { return name;}			// debugging assist
    
    void P();	// these are the only operations on a semaphore
    void V();	 	// they are both *atomic*
    void SelfTest();	// test routine for semaphore implementation
    
  private:
    char* name;        // useful for debugging
    int value;         // semaphore value, always >= 0

	List *ThreadQueue;   
    //List<Thread *> *queue;   
	
	// threads waiting in P() for the value to be > 0
};*/
/* Liang DePeng -
 ****/

/**** add
 * Liang DePeng + */
/*int fakeCompare (Item *x, Item *y){	
	return 0;
}*/

class __declspec(dllexport) FSemaphore: public Item{
public:
    FSemaphore(char* debugName, int initialValue);/*{
		name = debugName;
		value = initialValue;
		ThreadQueue = (* getList)(fakeCompare);	
	};	*/

	virtual ~FSemaphore() = 0{};  	// de-allocate semaphore
    virtual char* getName() = 0; 	// debugging assist
    
    virtual void P() = 0;			// these are the only operations on a semaphore
    virtual void V() = 0;			// they are both *atomic*
    virtual void SelfTest() = 0;	// test routine for semaphore implementation
    
protected:
    char* name;        // useful for debugging
    int value;         // semaphore value, always >= 0

	List *ThreadQueue;   
	// threads waiting in P() for the value to be > 0
};

//�궨�庯��ָ��
typedef FSemaphore* (*GetSemaphore)(char* debugName, int initialValue);  
typedef void (*DeleteSemaphore)(FSemaphore*);

extern "C" {
	__declspec(dllexport) FSemaphore* GetSemaphoreF(char* debugName, int initialValue);
	__declspec(dllexport) void DeleteSemaphoreF(FSemaphore*);
}

extern GetSemaphore getSemaphore;
extern DeleteSemaphore deleteSemaphore;	
/* Liang DePeng +
 ****/


// The following class defines a "lock".  A lock can be BUSY or FREE.
// There are only two operations allowed on a lock: 
//
//	Acquire -- wait until the lock is FREE, then set it to BUSY
//
//	Release -- set lock to be FREE, waking up a thread waiting
//		in Acquire if necessary
//
// In addition, by convention, only the thread that acquired the lock
// may release it.  As with semaphores, you can't read the lock value
// (because the value might change immediately after you read it).  

/**** delete
 * Liang DePeng - */
/*
class Lock{
  public:
    Lock(char* debugName);  	// initialize lock to be FREE
    ~Lock();			// deallocate lock
    char* getName() { return name; }	// debugging assist

    void Acquire(); 		// these are the only operations on a lock
    void Release(); 		// they are both *atomic*

    bool IsHeldByCurrentThread() { 
    		return lockHolder == kernel->currentThread; }
    				// return true if the current thread 
				// holds this lock.
    
    // Note: SelfTest routine provided by SynchList
    
  private:
    char *name;			// debugging assist
    Thread *lockHolder;		// thread currently holding lock
    Semaphore *semaphore;	// we use a semaphore to implement lock
};*/
/* Liang DePeng -
 ****/

/**** add
 * Liang DePeng + */
class __declspec(dllexport) FLock: public Item{
public:
	FLock(char* debugName);/*{	// initialize lock to be FREE
		name = debugName;
		semaphore = (* getSemaphore)("lock", 1);	//new Semaphore("lock", 1);  // initially, unlocked
		lockHolder = NULL;
	}  	*/
	virtual ~FLock() = 0{};			// deallocate lock
    virtual char* getName() = 0; //{ return name; }	// debugging assist

    virtual void Acquire() = 0; 		// these are the only operations on a lock
    virtual void Release() = 0; 		// they are both *atomic*

    virtual bool IsHeldByCurrentThread() = 0;/* { 
    		return lockHolder == kernel->currentThread; }*/
    				// return true if the current thread 
				// holds this lock.
    
    // Note: SelfTest routine provided by SynchList
protected:
    char *name;			// debugging assist
    Thread *lockHolder;		// thread currently holding lock
    FSemaphore *semaphore;	// we use a semaphore to implement lock
};

//�궨�庯��ָ��
typedef FLock* (*GetLock)(char* debugName);  
typedef void (*DeleteLock)(FLock*);

extern "C" {
	__declspec(dllexport) FLock* GetLockF(char* debugName);
	__declspec(dllexport) void DeleteLockF(FLock*);
}

extern GetLock getLock;
extern DeleteLock deleteLock;	
/* Liang DePeng +
 ****/

// The following class defines a "condition variable".  A condition
// variable does not have a value, but threads may be queued, waiting
// on the variable.
//
// All operations on a condition variable must be made while
// the current thread has acquired a lock.  Indeed, all accesses
// to a given condition variable must be protected by the same lock.
// In other words, mutual exclusion must be enforced among threads calling
// the condition variable operations.
//
// These are only operations on a condition variable: 
//
//	Wait() -- release the lock, relinquish the CPU until signaled, 
//		then re-acquire the lock
//
//	Signal() -- wake up a thread, if there are any waiting on 
//		the condition
//
//	Broadcast() -- wake up all threads waiting on the condition
//
// In Nachos, condition variables are assumed to obey *Mesa*-style
// semantics.  When a Signal or Broadcast wakes up another thread,
// it simply puts the thread on the ready list, and it is the responsibility
// of the woken thread to re-acquire the lock (this re-acquire is
// taken care of within Wait()).  By contrast, some define condition
// variables according to *Hoare*-style semantics -- where the signalling
// thread gives up control over the lock and the CPU to the woken thread,
// which runs immediately and gives back control over the lock to the 
// signaller when the woken thread leaves the critical section.
//
// The consequence of using Mesa-style semantics is that some other thread
// can acquire the lock, and change data structures, before the woken
// thread gets a chance to run.  The advantage to Mesa-style semantics
// is that it is a lot easier to implement than Hoare-style.

class Condition {
  public:
    Condition(char* debugName);	// initialize condition to 
					// "no one waiting"
    ~Condition();			// deallocate the condition
    char* getName() { return (name); }
    
    void Wait(FLock *conditionLock); 	// these are the 3 operations on 
					// condition variables; releasing the 
					// lock and going to sleep are 
					// *atomic* in Wait()
    void Signal(FLock *conditionLock);   // conditionLock must be held by
    void Broadcast(FLock *conditionLock);// the currentThread for all of 
					// these operations
    // SelfTest routine provided by SyncLists

  private:
    char* name;
	List *WaitQueue;	/* Liang Depeng - */
    //List<Semaphore *> *waitQueue;	// list of waiting threads	/* Liang Depeng - */
};
#endif // SYNCH_H
