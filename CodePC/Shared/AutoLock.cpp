#include <AutoLock.h>

#ifdef _DEBUG
/******************************Public*Routine******************************\
* Debug CCritSec helpers
*
* We provide debug versions of the Constructor, destructor, Lock and Unlock
* routines.  The debug code tracks who owns each critical section by
* maintaining a depth count.
*
* History:
*
\**************************************************************************/

CCritSec::CCritSec()
{
    InitializeCriticalSection(&m_CritSec);
    m_currentOwner = m_lockCount = 0;
    m_fTrace = FALSE;
}

CCritSec::~CCritSec()
{
    DeleteCriticalSection(&m_CritSec);
}

void CCritSec::Lock()
{
    UINT tracelevel=3;
    DWORD us = GetCurrentThreadId();
    DWORD currentOwner = m_currentOwner;
    if (currentOwner && (currentOwner != us)) {
        // already owned, but not by us
        if (m_fTrace) {
            //DbgLog((LOG_LOCKING, 2, TEXT("Thread %d about to wait for lock %x owned by %d"),
              //  GetCurrentThreadId(), &m_CritSec, currentOwner));
            tracelevel=2;
	        // if we saw the message about waiting for the critical
	        // section we ensure we see the message when we get the
	        // critical section
        }
    }
    EnterCriticalSection(&m_CritSec);
    if (0 == m_lockCount++) {
        // we now own it for the first time.  Set owner information
        m_currentOwner = us;

        if (m_fTrace) {
           // DbgLog((LOG_LOCKING, tracelevel, TEXT("Thread %d now owns lock %x"), m_currentOwner, &m_CritSec));
        }
    }
}

void CCritSec::Unlock() {
    if (0 == --m_lockCount) {
        // about to be unowned
        if (m_fTrace) {
           // DbgLog((LOG_LOCKING, 3, TEXT("Thread %d releasing lock %x"), m_currentOwner, &m_CritSec));
        }

        m_currentOwner = 0;
    }
    LeaveCriticalSection(&m_CritSec);
}

void WINAPI DbgLockTrace(CCritSec * pcCrit, BOOL fTrace)
{
    pcCrit->m_fTrace = fTrace;
}

BOOL WINAPI CritCheckIn(CCritSec * pcCrit)
{
    return (GetCurrentThreadId() == pcCrit->m_currentOwner);
}

BOOL WINAPI CritCheckIn(const CCritSec * pcCrit)
{
    return (GetCurrentThreadId() == pcCrit->m_currentOwner);
}

BOOL WINAPI CritCheckOut(CCritSec * pcCrit)
{
    return (GetCurrentThreadId() != pcCrit->m_currentOwner);
}

BOOL WINAPI CritCheckOut(const CCritSec * pcCrit)
{
    return (GetCurrentThreadId() != pcCrit->m_currentOwner);
}
#endif
