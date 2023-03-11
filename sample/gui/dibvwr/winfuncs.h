/*** winfuncs.h ***
	Dib Window / Viewer.

	Copyright (C) 1995 by Alfons Hoogervorst

	Free distribution is allowed, on this condition: don't remove this
	comment section.
*******************/

#ifndef __winfuncs_h
#define __winfuncs_h

#ifdef __cplusplus
extern "C" {
#endif
VOID SetDlgItemLong (HWND, int, LONG, BOOL);
BOOL GetDlgItemLong (HWND, int, LPLONG);

VOID MemSet(LPVOID, int, DWORD);
VOID MemCpy(LPVOID, LPVOID, DWORD);

LONG LongRand (VOID);
VOID SLongRand (DWORD);

LPSTR CreateUniqueName (LPSTR, int);
DWORD GetWindowsVersionNumber (VOID);
#ifdef __cplusplus
}
#endif

#endif
