#ifdef __MT__

#include <emx/syscalls.h>
#include <emx/thread.h>
#include <sys/builtin.h>
#include <sys/fmutex.h>
#include <sys/smutex.h>
#define WIN32_LEAN_AND_MEAN
#include <wingnuc.h>
#include <windows.h>
#include <winerror.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void __smutex_request_internal (volatile _smutex *sem)
{
  do
    {
      Sleep (1000);
    } while (__cxchg (sem, 1) != 0);
}

#else

void __smutex_request_internal (void *sem)
{
}

#endif
