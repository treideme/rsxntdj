/* excpt.h - Structured Exception Handling types, defines and routines

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

#if !defined (_EXCPT_H)
#define _EXCPT_H

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(RC_INVOKED)

#define EXCEPTION_EXECUTE_HANDLER        1
#define EXCEPTION_CONTINUE_SEARCH        0
#define EXCEPTION_CONTINUE_EXECUTION    -1

typedef enum {
  ExceptionContinueExecution,
  ExceptionContinueSearch,
  ExceptionNestedException,
  ExceptionCollidedUnwind
} EXCEPTION_DISPOSITION;

struct _EXCEPTION_RECORD;
struct _CONTEXT;
struct _EXCEPTION_POINTERS;

EXCEPTION_DISPOSITION _except_handler
(
 struct _EXCEPTION_RECORD *ExceptionRecord,
 void * EstablisherFrame,
 struct _CONTEXT *ContextRecord,
 void * DispatcherContext
);

typedef EXCEPTION_DISPOSITION (*_EXCEPTION_HANDLER)
(
 struct _EXCEPTION_RECORD * ExceptionRecord,
 void                     * EstablisherFrame,
 struct _CONTEXT          * ContextRecord,
 void                     * DispatcherContext
);

typedef struct _EXCEPTION_REGISTRATION_RECORD
{
    struct _EXCEPTION_REGISTRATION_RECORD * __volatile__ pPrev;
    _EXCEPTION_HANDLER                      __volatile__ fHandler;
} EXCEPTION_REGISTRATION_RECORD;

typedef struct _EXCEPTION_REGISTRATION_RECORD_RSXNT
{
    struct _EXCEPTION_REGISTRATION_RECORD_RSXNT * __volatile__ pPrev;
    _EXCEPTION_HANDLER __volatile__ fHandler;
    int __volatile__ iContext;
    void * fFilter;
    void * fFilterEnd;
    unsigned long Ebp;
    unsigned long Ebx;
    unsigned long Esi;
    unsigned long Edi;
    unsigned long Esp;
    unsigned long __volatile__ ExceptionCode;
} EXCEPTION_REGISTRATION_RECORD_RSXNT;

/* where we are */
#define XCPT_CONTEXT_TRY        0
#define XCPT_CONTEXT_EXCEPTION  1
#define XCPT_CONTEXT_HANDLER    2
#define XCPT_CONTEXT_FINALLY    3

#define _exception_code()           (_err.ExceptionCode)
#define GetExceptionCode()          (_err.ExceptionCode)
#define exception_code()            (_err.ExceptionCode)

/* _exception_info can only be called inside the filter */
#define _exception_info()           (bad_context_exception_info)
#define GetExceptionInformation()   (bad_context_exception_info)
#define exception_info()            (bad_context_exception_info)

int _abnormal_termination(int);
#define AbnormalTermination()       _abnormal_termination(_err.iContext)
#define abnormal_termination()      _abnormal_termination(_err.iContext)

int  __xcpt_new_handler (EXCEPTION_REGISTRATION_RECORD_RSXNT *) __attribute__((stdcall));
int  __xcpt_set_handler (EXCEPTION_REGISTRATION_RECORD_RSXNT *) __attribute__((stdcall));
int  __xcpt_del_handler (void);
void __xcpt_filter (int) __attribute__((stdcall,noreturn));

#if !defined (RSXNT_SEH)

#define __try \
    ({  __label__ lab1, lab2;                       \
        EXCEPTION_REGISTRATION_RECORD_RSXNT _err;   \
        _err.fFilter = &&lab1;                      \
        _err.fFilterEnd = &&lab2;                   \
        __xcpt_new_handler(&_err);

#define __except(exp)               \
        goto lab2;                  \
       lab1:                        \
        {                           \
        struct _EXCEPTION_POINTERS * bad_context_exception_info; \
        bad_context_exception_info \
              = (struct _EXCEPTION_POINTERS *) _err.iContext; \
        __xcpt_filter ((exp));      \
        }                           \
       lab2:                        \
        __xcpt_set_handler(&_err);  \
    });                             \
    if (__xcpt_del_handler() == XCPT_CONTEXT_HANDLER)

#define __finally \
        lab1:                       \
        lab2:                       \
    });                             \
    __xcpt_del_handler();

#else /* defined (RSXNT_SEH) */

/* extended version to support __finally handlers */

int  __xcpt2_new_handler (EXCEPTION_REGISTRATION_RECORD_RSXNT *) __attribute__((stdcall));
int  __xcpt2_set_handler (EXCEPTION_REGISTRATION_RECORD_RSXNT *) __attribute__((stdcall));
int  __xcpt2_del_handler (void);
void __xcpt2_filter (int) __attribute__((stdcall,noreturn));
void __xcpt2_continue() __attribute__((noreturn));

#define __try \
    ({  __label__ lab1, lab2;                       \
        EXCEPTION_REGISTRATION_RECORD_RSXNT _err;   \
        _err.fFilter = &&lab1;                      \
        _err.fFilterEnd = &&lab2;                   \
        __xcpt2_new_handler (&_err);

#define __except(exp) \
        goto lab2;                  \
       lab1:                        \
        {                           \
        struct _EXCEPTION_POINTERS * bad_context_exception_info; \
        bad_context_exception_info \
              = (struct _EXCEPTION_POINTERS *) _err.iContext; \
        __xcpt2_filter ((exp));     \
        }                           \
       lab2:                        \
        __xcpt2_set_handler(&_err); \
        if (_err.iContext == XCPT_CONTEXT_HANDLER)

#define __finally \
       lab1:       \
       lab2:       \

#define __endtry \
        if (_err.iContext == XCPT_CONTEXT_FINALLY) \
            __xcpt2_continue();     \
        __xcpt2_del_handler();      \
    });

#endif /* !defined (RSXNT_SEH) */

#endif /* RC_INVOKED */

#ifdef __cplusplus
}
#endif

#endif /* !defined (_EXCPT_H) */
