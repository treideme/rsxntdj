/* excpt.c - frame-based exception handlers for Win32 and GNU C/C++
   include extended version (finally handlers)
   examples: \rsxnt\sample\console\excpt

   Copyright (c) 1995-1999 Rainer Schnitker

   This file is part of RSXNT.

   RSXNT is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   RSXNT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with RSXNT; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA. */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <excpt.h>

#define END_OF_FRAMES ((EXCEPTION_REGISTRATION_RECORD_RSXNT *)0xffffffff)

/* asm function that calls the filter function */
int _exception_test_filter (void (*fCHandler)(), DWORD);

#if defined (RSXNT_SEH)
EXCEPTION_DISPOSITION _except_handler2
#else
EXCEPTION_DISPOSITION _except_handler1
#endif
(
 struct _EXCEPTION_RECORD * ExceptionRecord,
 void                     * EstablisherFrame,
 struct _CONTEXT          * ContextRecord,
 void                     * DispatcherContext
)
{
    /* fatal errors : run next handler */
    if (ExceptionRecord->ExceptionFlags == EXCEPTION_NONCONTINUABLE ||
        ExceptionRecord->ExceptionCode == EXCEPTION_BREAKPOINT ||
        ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW)
    {
        return (ExceptionContinueSearch);
    }
    else {
        EXCEPTION_REGISTRATION_RECORD_RSXNT *err_frame
            = (EXCEPTION_REGISTRATION_RECORD_RSXNT *) EstablisherFrame;
        EXCEPTION_REGISTRATION_RECORD_RSXNT *err;
        EXCEPTION_POINTERS ep;

        if (err_frame->iContext != XCPT_CONTEXT_TRY)
            return (ExceptionContinueSearch);

        ep.ExceptionRecord = ExceptionRecord;
        ep.ContextRecord = ContextRecord;

        // walk through all excpt filters
        for (err = err_frame; err->pPrev != END_OF_FRAMES; err = err->pPrev)
        {
            int ret;

            err->iContext = XCPT_CONTEXT_EXCEPTION;

            if ((int) err->fFilterEnd - (int) err->fFilter <= 4)
                continue;

            err->iContext = (int) &ep;
            err->ExceptionCode = ExceptionRecord->ExceptionCode;
            ret = _exception_test_filter(err->fFilter, err->Ebp);
            err->iContext = XCPT_CONTEXT_EXCEPTION;

            if (ret == EXCEPTION_CONTINUE_EXECUTION)
                return (ExceptionContinueExecution);

            else if (ret == EXCEPTION_EXECUTE_HANDLER)
                break;

            else if (ret != EXCEPTION_CONTINUE_SEARCH)
            {
                MessageBox (NULL, "illegal exception filter return value",
                            NULL, MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
                return (ExceptionContinueSearch);
            }
        }
        if (err->pPrev == END_OF_FRAMES) /* give up (rsxnt handler) */
            return (ExceptionContinueSearch);

#if defined (RSXNT_SEH)

        // walk through all finally handlers
        for ( ; err_frame != err; err_frame = err_frame->pPrev)
        {
            extern int _exception_term_handler (void (*fCHandler)(), DWORD);

            if ((int) err_frame->fFilterEnd - (int) err_frame->fFilter > 4)
                continue;

            err_frame->iContext = XCPT_CONTEXT_FINALLY;

            _exception_term_handler(err_frame->fFilterEnd, err_frame->Ebp);
        }
#endif

        err->iContext = XCPT_CONTEXT_HANDLER;
        err->ExceptionCode = ExceptionRecord->ExceptionCode;

        /* continue the __except block */
        ContextRecord->Eip = (DWORD) err->fFilterEnd;
        ContextRecord->Esp = (DWORD) err->Esp;
        ContextRecord->Ebp = (DWORD) err->Ebp;
        ContextRecord->Ebx = (DWORD) err->Ebx;
        ContextRecord->Esi = (DWORD) err->Esi;
        ContextRecord->Edi = (DWORD) err->Edi;
        return (ExceptionContinueExecution);
    }
}
