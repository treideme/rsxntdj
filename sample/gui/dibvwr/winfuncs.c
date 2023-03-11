/* winfuncs.c - Several functions. Some functions can be replaced by the
 * RTL or the Win32 API.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */
#include "compiler.h"
#include <windows.h>
#include "winfuncs.h"

/*** SetDlgItemLong ***
    SetDlgItemInt counter part for LONGs. Minimalistic approach.
***********************/
VOID SetDlgItemLong(HWND hWnd, int nId, LONG lNumber, BOOL bSigned)
{
    char    buffer[20];

    buffer[0] = 0;
    wsprintf(buffer, bSigned ? "%ld" : "%lu", lNumber);
    SetDlgItemText(hWnd, nId, buffer);
}

/*** GetDlgItemLong ***
    GetDlgItemInt counter part for LONGs. Minimalistic approach. Type cast *lpResult
    to a word if you want it to be negative. This function is not used within
    this module. It might be used in an other version of DIBVWR.
***********************/
BOOL GetDlgItemLong(HWND hWnd, int nId, LPLONG lpResult)
{
    char    buffer[20];
    BOOL    bResult = FALSE;
    char*   lpWalk = buffer;
    DWORD   dec = 1;
    if ( GetDlgItemText(hWnd, nId, buffer, sizeof buffer) == 0 ) return bResult;
    *lpResult = 0;
    while ( *lpWalk++ ) {}
    while ( --lpWalk >= buffer )
        if ( *lpWalk >= 0 && *lpWalk <= 9 ) {
            if ( *lpWalk != 0 ) *lpResult += dec * (*lpWalk - '0');
            dec *= 10;
        } else if ( *lpWalk == '-' || *lpWalk == '+' ) { /* Return true if we hit a sign char */
            *lpWalk == '-' ? *lpResult *= -1 : 0;
            break;
        } else return FALSE;
   return TRUE;
}

/*****************/

VOID MemSet(LPVOID lpvdMem, int nValue, DWORD dwSize)
{
    while ( dwSize-- ) *((LPSTR)lpvdMem)++ = (char)nValue;
}

VOID MemCpy(LPVOID lpvdDest, LPVOID lpvdSource, DWORD dwSize)
{
    while ( dwSize-- ) *((LPSTR)lpvdDest)++ = *((LPSTR)lpvdSource)++;
}

/*****************/

/***** Random function courtesy of Snippets *****/

#define a 16807         /* multiplier */
#define m 2147483647L   /* 2**31 - 1 */
#define q 127773L       /* m div a */
#define r 2836          /* m mod a */

static LONG NextLongRand(LONG seed)
{
	DWORD lo, hi;

	lo = a * (LONG)(seed & 0xFFFF);
	hi = a * (LONG)((DWORD)seed >> 16);
	lo += (hi & 0x7FFF) << 16;
	if (lo > m) {
		lo &= m;
		++lo;
	}
	lo += hi >> 15;
	if (lo > m) {
		lo &= m;
		++lo;
	}
	return (LONG)lo;
}

static LONG lRandomNum = 1;

LONG LongRand(VOID)
{
	return lRandomNum = NextLongRand(lRandomNum);
}

VOID SLongRand(DWORD dwSeed)      /* to seed it */
{
	lRandomNum = dwSeed ? (dwSeed & m) : 1;  /* nonzero seed */
}

/*****************/

/*** CreateUniqueName ***
    Creates a unique name.
*************************/
LPSTR CreateUniqueName(LPSTR lpszName, int nSize)
{
	LPSTR		lpszWalk = lpszName;
	nSize--;
	while ( nSize-- > 1 ) *lpszWalk++ = (char)(LongRand() % 26) + 'A';
	*lpszWalk = 0;
	return lpszName;
}

/*****************/

/*** GetWindowsVersionNumber ***
    Returns the operating version number, but in a programmer friendly
    way: 0x0003500 means version 3.5. 0x0003B000 means version 3.11
********************************/
DWORD GetWindowsVersionNumber(VOID)
{
    OSVERSIONINFO   osvi;
    GetVersionEx(&osvi);
    return (DWORD)MAKELONG((WORD)osvi.dwMinorVersion, (WORD)osvi.dwMajorVersion << 12);
}