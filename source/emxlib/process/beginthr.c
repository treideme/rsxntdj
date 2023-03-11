/*
    beginthr.c -  replaces thread calls in the emx library

    Copyright (C) 1995-1998
        Rainer Schnitker, Heeper Str. 283, 33607 Bielefeld
        email: rainer@mathematik.uni-bielefeld.de

    All rights reserved
*/

#include <emx/syscalls.h>
#include <emx/thread.h>

#define WIN32_LEAN_AND_MEAN
#include <wingnuc.h>
#include <windows.h>
#include <winerror.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef __MT__

extern int __thread_init();
extern struct _thread __thread_1;
extern unsigned long __ThreadIndex;

static DWORD WINAPI thread_start (void * param)
{
    struct _thread *tp = (struct _thread *) param;

    TlsSetValue(__ThreadIndex, tp);   /* set thread local storage */

    tp->_th_start (tp->_th_arg);

    _endthread();

    /* Never executed! */
    return 0;
}

int _beginthread (void (*start)(void *arg), void *stack, unsigned stack_size,
                  void *arg_list)
{
    HANDLE hThread;
    DWORD tid;
    struct _thread *tp;

    if (!__thread_init()) {
        errno = ENOSYS;
        return -1;
    }

    tp = (struct _thread *) HeapAlloc(GetProcessHeap(),
                    HEAP_ZERO_MEMORY, sizeof(struct _thread));

    if (!tp) {
        errno = ENOMEM;
        return -1;
    }

    tp->_th_rand = 1;
    tp->_th_start = start;
    tp->_th_arg = arg_list;

    hThread = CreateThread (NULL, stack_size, thread_start, tp,
                CREATE_SUSPENDED, &tid);

    if (hThread == 0) {
        errno = EINVAL;
        return -1;
    }
    tp->_th_reserved[0] = (int) hThread; /* for _endthread() */
    
    if (__newthread (tid) != 0) {       /* system call */
        TerminateThread(hThread, 0);
        return -1;
    }

    if (!ResumeThread (hThread)) {
        errno = ESRCH;
        return -1;
    }
    return (int) hThread;
}

void _endthread (void)
{
    struct _thread *tp;

    if (!__thread_init())
        return;

    tp = _thread ();

    if (tp != & __thread_1) {               /* not main thread */
        HANDLE h = (HANDLE) tp->_th_reserved[0];
        HeapFree(GetProcessHeap(), 0, tp);
        __endthread (_gettid());            /* system call */
        ExitThread(0);
        CloseHandle (h);
    }
    ExitProcess(0);
}

#endif

