/* bmpfile.c, plain and simple dib file functions
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

 /*
  * @DOC
  * @module bmpfile.c |
  * Simple functions that use the Win32 API to read Device Independent Bitmaps.
  * @index bmpfile.c | func
  */

#include "compiler.h"
#include <windows.h>
#include "bmpfile.h"
#include "dibfunc.h"
#include "windbg.h"

#ifdef __cplusplus
extern "C" {
#endif
static BOOL valid_bitmap_header (HANDLE);
#ifdef __cplusplus
}
#endif

/*-PUB---------------------------------------------------------------------*
    @func Reads a bitmap file and returns a pointer to the bitmap data. The
    returned pointer should be freed by calling dib_free_ptr().
    @rdesc Returns one of the following values
    @flag NULL | Error occurred
    @flag <> NULL | Succesful, the returned pointer should be freed by
    calling <f dib_free_ptr>
*--------------------------------------------------------------------------*/
LPBITMAPINFO read_bmp_file_win32_ptr
(
    LPCSTR lpszFileName /* @parm Name of bitmap file to read                */
)
{
	HANDLE			    hFile = CreateFile(lpszFileName,
					        GENERIC_READ, FILE_SHARE_READ, NULL,
							OPEN_EXISTING,	FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD			    dwSize, dwRead = 0;
	BITMAPINFOHEADER    bmih;
	LPBITMAPINFO	    lpbmi = NULL;

	if ( hFile == INVALID_HANDLE_VALUE ) return lpbmi;
	if ( !valid_bitmap_header(hFile) ) goto rbfcpExit;

	/* Read bitmap info header */
	if ( !ReadFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwRead, NULL) ||
		  dwRead != sizeof(BITMAPINFOHEADER) ) {
		CloseHandle(hFile);
		return lpbmi;
	}

	/* Size of bitmap data + color table */
	dwSize = dib_size((LPBITMAPINFO)&bmih);
    WINASSERTTEXT(dwSize == 0, "Zero sized DIB");

	lpbmi = dib_ptr_alloc((LPBITMAPINFO)&bmih);
    if ( !lpbmi ) {
		CloseHandle(hFile);
		return lpbmi;
	}

    lpbmi->bmiHeader = bmih;
    dwSize -= sizeof(BITMAPINFOHEADER);
	if ( !ReadFile(hFile, lpbmi->bmiColors, dwSize, &dwRead, NULL) ||
		  dwRead != dwSize ) {
		dib_ptr_free(lpbmi);
		lpbmi = NULL;
	}

rbfcpExit:
	CloseHandle(hFile);
	return lpbmi;
}

static BOOL valid_bitmap_header(HANDLE hFile)
{
	BITMAPFILEHEADER	bfh;
	DWORD					dwSize;

	if ( !ReadFile(hFile, &bfh, sizeof bfh, &dwSize, NULL ) ||
		dwSize != sizeof bfh )
		return FALSE;
	if ( bfh.bfType != *(LPWORD)"BM" ) return 0;
	return TRUE;
}

/*-PUB----------------------------------------------------------------------*
    @func Writes a bitmap to a BMP file
    @rdesc Returns zero if successful
    @flag ERROR_SUCCESS (0) | Success
    @flag != 0 | The value returned by GetLastError()
 *--------------------------------------------------------------------------*/
DWORD write_bmp_file_win32_ptr(
    LPCSTR lpszFileName,    /* @parm Name of bitmap file                    */
    LPBITMAPINFO lpbmi)     /* @parm Pointer to DIB                         */
{
	BITMAPFILEHEADER	bfh;
	DWORD				dwResult = ERROR_BAD_ARGUMENTS;
	HANDLE				hFile;

	if ( lpszFileName == NULL || lpbmi == NULL ) return dwResult;

	hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile == INVALID_HANDLE_VALUE ) return GetLastError();

	bfh.bfType = MAKEWORD('B', 'M');

	/*** Calculate size of dib ***/
	bfh.bfSize = ( lpbmi->bmiHeader.biSizeImage ?
		lpbmi->bmiHeader.biSizeImage :
		WIDTHBYTES((DWORD)(lpbmi->bmiHeader.biWidth) *
		lpbmi->bmiHeader.biBitCount) * lpbmi->bmiHeader.biHeight );
	bfh.bfSize += palette_size(lpbmi) + sizeof(BITMAPINFOHEADER);
	bfh.bfSize += sizeof bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfOffBits = sizeof bfh + (find_dib_bits(lpbmi) - (LPBYTE)lpbmi);

	/*** Write header ***/
	if ( !WriteFile(hFile, &bfh, sizeof bfh, &dwResult, NULL) ||
		  dwResult != sizeof bfh ) {
		dwResult = GetLastError();
		CloseHandle(hFile);
		return dwResult;
	}

	/*** Write bitmap bits ***/
	dwResult = WriteFile(hFile, lpbmi, bfh.bfSize - sizeof bfh,
		&dwResult, NULL) ? ERROR_SUCCESS : GetLastError();
	CloseHandle(hFile);
	return dwResult;
}

/* End of File */
