/*** windbg.h ***
    Debug functions.

    No copyrights claimed. By Alfons Hoogervorst.
*******************/

#ifndef __windbg_h
#define __windbg_h

#if defined(DEBUG) || defined(NDEBUG) || defined(_DEBUG)
#define WINASSERT(condition) \
    _trace_out((void*)(condition), (LPSTR)__FILE__ ? (LPSTR)__FILE__ : NULL, \
        __LINE__ ? __LINE__ : 0, (LPSTR)__FUNC__ ? (LPSTR)__FUNC__ : NULL, \
        NULL)
#define WINASSERTTEXT(condition, text) \
    _trace_out((void*)(condition), (LPSTR)__FILE__ ? (LPSTR)__FILE__ : NULL,  \
        __LINE__ ? __LINE__ : 0, (LPSTR)__FUNC__ ? (LPSTR)__FUNC__ : NULL, \
        (LPSTR)text ? (LPSTR)text : NULL)
#define WINVTRACE       WinLogError
#define WINTRACE(text) \
    _trace_out((void*)1, (LPSTR)__FILE__ ? (LPSTR)__FILE__ : NULL,  \
        __LINE__ ? __LINE__ : 0, (LPSTR)__FUNC__ ? (LPSTR)__FUNC__ : NULL, \
        (LPSTR)text ? (LPSTR)text : NULL)
#ifdef __cplusplus
extern "C" {
#endif
VOID _trace_out (void*, char*, int, char*, char*);
void WinLogError (LPCSTR, ...);
#ifdef __cplusplus
}
#endif
#else
#define WINASSERT(condition) \
   if ( condition ) (void)0
#define WINASSERTTEXT(condition, text) \
   if ( condition ) (void)0
#define WINTRACE(text) \
    (void)0
#define WINVTRACE   \
    1 == 1 ? (void)0 :
#endif


#endif /* !__windbg_h */