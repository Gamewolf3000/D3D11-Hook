#pragma once

#include <stdafx.h>

// eliminate spurious "statement has no effect" warnings.
#pragma warning(disable: 4705)

// wrapper for whatever critical section we have
class CCritSec {

    // make copy constructor and assignment operator inaccessible

    CCritSec(const CCritSec &refCritSec);
    CCritSec &operator=(const CCritSec &refCritSec);

    CRITICAL_SECTION m_CritSec;

#ifdef _DEBUG
public:
    DWORD   m_currentOwner;
    DWORD   m_lockCount;
    BOOL    m_fTrace;        // Trace this one
public:
    CCritSec();
    ~CCritSec();
    void Lock();
    void Unlock();
#else

public:
    CCritSec() {
        InitializeCriticalSection(&m_CritSec);
    };

    ~CCritSec() {
        DeleteCriticalSection(&m_CritSec);
    };

    void Lock() {
        EnterCriticalSection(&m_CritSec);
    };

    void Unlock() {
        LeaveCriticalSection(&m_CritSec);
    };
#endif
};

//
// To make deadlocks easier to track it is useful to insert in the
// code an assertion that says whether we own a critical section or
// not.  We make the routines that do the checking globals to avoid
// having different numbers of member functions in the debug and
// retail class implementations of CCritSec.  In addition we provide
// a routine that allows usage of specific critical sections to be
// traced.  This is NOT on by default - there are far too many.
//

#ifdef _DEBUG
    BOOL WINAPI CritCheckIn(CCritSec * pcCrit);
    BOOL WINAPI CritCheckIn(const CCritSec * pcCrit);
    BOOL WINAPI CritCheckOut(CCritSec * pcCrit);
    BOOL WINAPI CritCheckOut(const CCritSec * pcCrit);
    void WINAPI DbgLockTrace(CCritSec * pcCrit, BOOL fTrace);
#else
    #define CritCheckIn(x) TRUE
    #define CritCheckOut(x) TRUE
    #define DbgLockTrace(pc, fT)
#endif


// locks a critical section, and unlocks it automatically
// when the lock goes out of scope
class CAutoLock {

    // make copy constructor and assignment operator inaccessible

    CAutoLock(const CAutoLock &refAutoLock);
    CAutoLock &operator=(const CAutoLock &refAutoLock);

protected:
    CCritSec * m_pLock;

public:
    CAutoLock(CCritSec * plock)
    {
        m_pLock = plock;
        m_pLock->Lock();
    };

    ~CAutoLock() {
        m_pLock->Unlock();
    };
};