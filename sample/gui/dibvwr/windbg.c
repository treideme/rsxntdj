/* windbg.c, assorted debugging / trace functions.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */
#include "compiler.h"
#include <windows.h>

#define TRACETXT    "%s in %s, line %d - \"%s\" "
VOID _trace_out(LPVOID assert_condition, LPSTR filename, int line_nr,
    LPSTR func, LPSTR text)
{
    if ( assert_condition ) {
        char    buf[500];

        if ( !filename ) filename = "<unknown>";
        if ( !func ) func = "<unknown>";
        if ( !text ) text = "<unknown>";
        wsprintf(buf, TRACETXT, filename, func, line_nr, text);
        OutputDebugString(buf);
    }
}

#ifndef MAX_LOG_ERROR_TEXT
#define MAX_LOG_ERROR_TEXT      512
#endif
/* Nifty code stolen from my INJDLL.. */
void WinLogError(LPCSTR Message, ...)
{
    char buf[MAX_LOG_ERROR_TEXT];
    va_list start;
    va_start(start, Message);
    wvsprintf(buf, Message, start);
    OutputDebugString(buf);
    va_end(start);
}
