/* dibfunc.c - Functions for handling DIB data in 10 and odd ways.
 * Some functions we're based on the dibutil module of Microsoft,
 * but were rewritten for the dibwin control.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

/*
 * @DOC
 * @module dibfunc.c |
 * DibFunc has a load of functions that deal with manipulating DIBs. For
 * example: creating new copies of DIBs in handle, pointer or shared forms.
 * This module needs the resources in the dibfunc.rc resource script.
 * @index dibfunc.c | func
 */

#include "compiler.h"
#include <windows.h>
#include "dibfunc.h"
#include "winfuncs.h"
#include "windbg.h"

/*-PUB----------------------------------------------------------------------*
    @func Calculates the offset to the bits (pixel data) in a DIB handle.
    @rdesc Returns an integer value:
    @flag  -1   | Error
    @flag  else | offset to pixel data
 *--------------------------------------------------------------------------*/
int find_dib_bits_offset(
    HGLOBAL hdib        /* @parm Global handle of DIB.                      */
)
{
	LPBYTE	lpDib;
	int		nResult = -1;

	lpDib = (LPBYTE)GlobalLock(hdib);
	if ( lpDib != NULL ) {
		nResult = find_dib_bits((LPBITMAPINFO)lpDib) - lpDib;
		GlobalUnlock(hdib);
	}
	return nResult;
}

/*-PUB----------------------------------------------------------------------*
    @func Returns a pointer to a DIB's pixel data.
    @rdesc This value returns anything, mostly a pointer to a DIB's
    pixel data, but it the DIB's info header contains invalid values
    the return value is not valid. There's no way to verify a DIB's
    information header.
    @flag value | Pointer to the DIB's pixel data.
 *--------------------------------------------------------------------------*/
LPBYTE find_dib_bits(
    LPBITMAPINFO lpbi       /* @parm Pointer to a DIB.                      */
)
{
	return ((LPBYTE)lpbi + lpbi->bmiHeader.biSize + palette_size(lpbi));
}

/*-PUB----------------------------------------------------------------------*
    @func This function calculates a DIB's palette size. Use this function
    to calculate how much memory you should allocate for a DIB's palette.
    @rdesc This function returns the size of the palette in bytes.
 *--------------------------------------------------------------------------*/
int palette_size(
    LPBITMAPINFO lpbi   /* @parm A pointer to a DIB                         */
)
{
	/* calculate the size required by the palette */
	int	colors = dib_num_colors(lpbi);
	return  colors > 256 ? 0 : colors * ( IS_WIN30_DIB(lpbi) ?
		sizeof(RGBQUAD) : sizeof(RGBTRIPLE) );
}

/*-PUB----------------------------------------------------------------------*
    @func This function calculates the entire size of a DIB, including its
    informational headers, palette and bitmap data.
    @rdesc The return value is the size (in bytes) of the DIB's data.
 *--------------------------------------------------------------------------*/
DWORD dib_size(
    LPBITMAPINFO lpDib      /* @parm A pointer to a DIB.                    */
)
{
	return ( lpDib->bmiHeader.biSizeImage ? lpDib->bmiHeader.biSizeImage :
				WIDTHBYTES((DWORD)(lpDib->bmiHeader.biWidth) *
				lpDib->bmiHeader.biBitCount) * lpDib->bmiHeader.biHeight ) +
				palette_size(lpDib) + sizeof(BITMAPINFOHEADER);
}

/*-PUB----------------------------------------------------------------------*
    @func This function calculates the number of colors in a DIB. Useful if
    you want to know if the DIB uses a palette. See <f palette_size>.
    @rdesc Returns the number of colors in a DIB.
 *--------------------------------------------------------------------------*/
int dib_num_colors(
    LPBITMAPINFO lpbi   /* @parm Pointer to a DIB.                          */
)
{
	int nBitCount;

	if ( IS_WIN30_DIB(lpbi) )
		if ( lpbi->bmiHeader.biClrUsed ) return (int)lpbi->bmiHeader.biClrUsed;

	if ( IS_WIN30_DIB(lpbi) )
		nBitCount = lpbi->bmiHeader.biBitCount;
	else
		nBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;

	/* return number of colors based on bits per pixel */
	return 1 << nBitCount;
}

/*-PUB----------------------------------------------------------------------*
    @func This function calculates the size (in bytes) of a DIB scan line.
    A scan line is one pixel row. The return value is DWORD aligned, which
    is required for the Win32 API.
    @rdesc An integer value with the size of a DIB scan line.
 *--------------------------------------------------------------------------*/
int get_scanline_size(
    LPBITMAPINFO lpbmi      /* @parm Pointer to a DIB.                      */
)
{
	return WIDTHBYTES(lpbmi->bmiHeader.biWidth *	lpbmi->bmiHeader.biBitCount);
}

/*-PUB----------------------------------------------------------------------*
    @func copy_dib_ptr creates a new copy of a DIB from a DIB pointer. The
    returned pointer should not be used to exchange data between different
    processes. If no longer necessary, the returned pointer should be
    freed with <f dib_ptr_free>.
    @rdesc Any of the following values:
    @flag  NULL | Error
    @flag  else | Pointer to a newly allocated DIB. When no longer necessary
                  free with <f dib_ptr_free>
 *--------------------------------------------------------------------------*/
LPBITMAPINFO copy_dib_ptr(
    LPBITMAPINFO lpDib  /* @parm A pointer to a DIB.                        */
)
{
	LPBITMAPINFO	lpDibCopy = 0;
	DWORD           dwSize;

	if ( lpDib == NULL ) return lpDibCopy;

    /* Allocate pointer */
	lpDibCopy = dib_ptr_alloc(lpDib);
	if ( lpDibCopy == NULL ) return lpDibCopy;

    /* Copy data */
	MemCpy(lpDibCopy, lpDib, dib_size(lpDib));

	return lpDibCopy;
}

/*-PUB----------------------------------------------------------------------*
    @func copy_dib_handle creates a new copy of a DIB from a handle. This
    handle can be used in the clipboard communication functions or DDE.
    @rdesc Returns a global handle. If you use this handle in the same
    process, you're responsible for freeing the handle with GlobalFree. If
    you pass it to other process through DDE, or via the clipboard, see
    the SDK documentation.
    @flag   NULL  | Error.
    @flag   !NULL | A valid handle which should be freed with GlobalFree.
 *--------------------------------------------------------------------------*/
HGLOBAL copy_dib_handle(
    LPBITMAPINFO lpDib  /* @parm A pointer to a DIB.                        */
)
{
	HGLOBAL	hglbDibCopy = 0;
	LPBYTE	lpDibCopy;
	DWORD 	dwSize;

	if ( lpDib == NULL ) return NULL;

	/*** Calculate size of dib ***/
	if ( 0 == (dwSize = dib_size(lpDib)) ) {
	    WINASSERTTEXT(TRUE, "Invalid DIB size");
	    return NULL;
    }

	hglbDibCopy = GlobalAlloc(GHND, dwSize);
	if ( hglbDibCopy == NULL ) return NULL;

	lpDibCopy = (LPBYTE)GlobalLock(hglbDibCopy);
	if ( lpDibCopy == NULL ) {
		GlobalFree(hglbDibCopy);
		return NULL;
	}

	MemCpy(lpDibCopy, lpDib, dwSize);
	GlobalUnlock(hglbDibCopy);

	return hglbDibCopy;
}

/*-PUB----------------------------------------------------------------------*
    @func This function creates a new copy of a DIB from a DIB handle.
    Use the <p bDeleteHandle> argument when the function should destroy
    the DIB passed in <p hGlbDib>.
    @rdesc Returns any of the following values:
    @flag   NULL    | Error occurred.
    @flag   else    | Pointer to new copy of the DIB passed in <p hGlbDib>
 *--------------------------------------------------------------------------*/
LPBITMAPINFO copy_handle_dib(
    HGLOBAL hGlbDib,        /* @parm DIB handle.                            */
    BOOL bDeleteHandle)     /* @parm TRUE if the function should deallocate
                               the DIB in <p hGlbDib>                       */
{
	LPBITMAPINFO	lpBmi = GlobalLock(hGlbDib), lpRes;

	if ( lpBmi == NULL ) return lpBmi;
	lpRes = copy_dib_ptr(lpBmi);
	GlobalUnlock(hGlbDib);

	if ( lpRes != NULL ) if ( bDeleteHandle ) GlobalFree(hGlbDib);
	return lpRes;
}

/*-PUB----------------------------------------------------------------------*
    @func This function creates a palette for a DIB.
    @rdesc Returns the GDI handle of the new palette or NULL.
 *--------------------------------------------------------------------------*/
HPALETTE create_dib_palette(
    LPBITMAPINFO lpbmi  /* @parm Pointer to a DIB.                          */
)
{
	int nColors = dib_num_colors(lpbmi);

	if ( nColors <= 256 && nColors > 0 ) {
		LPLOGPALETTE lpLogPalette = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(LOGPALETTE) + nColors * sizeof(PALETTEENTRY));
		if ( lpLogPalette != NULL ) {
			HPALETTE		hPal;
			lpLogPalette->palVersion = 0x300;
			lpLogPalette->palNumEntries = (WORD)nColors;
			for ( ; nColors; nColors-- ) {
				lpLogPalette->palPalEntry[nColors - 1].peRed =
					lpbmi->bmiColors[nColors - 1].rgbRed;
				lpLogPalette->palPalEntry[nColors - 1].peBlue =
					lpbmi->bmiColors[nColors - 1].rgbBlue;
				lpLogPalette->palPalEntry[nColors - 1].peGreen =
					lpbmi->bmiColors[nColors - 1].rgbGreen;
				lpLogPalette->palPalEntry[nColors - 1].peFlags = 0;
			}
			hPal = CreatePalette(lpLogPalette);
			HeapFree(GetProcessHeap(), 0, lpLogPalette);
			return hPal;
		}
	}
	return NULL;
}

/*-PUB----------------------------------------------------------------------*
    @func Creates a  new copy of a palette.
    @rdesc Returns a GDI handle or NULL if it failed. Delete the handle if
    you don't need to use it anymore.
 *--------------------------------------------------------------------------*/
HPALETTE copy_palette(
    HPALETTE hPalette   /* @parm Palette you want to copy                   */
)
{
	LPLOGPALETTE	lpLogPal = (LPLOGPALETTE)HeapAlloc(GetProcessHeap(),
							0, sizeof(LOGPALETTE));
	HPALETTE			hPalResult = NULL;

	if ( !lpLogPal ) return NULL;
	if ( GetObject(hPalette, sizeof(LOGPALETTE), lpLogPal) ) {
		int				nSize;
		LPLOGPALETTE	lpT = HeapReAlloc(GetProcessHeap(), 0, lpLogPal,
								nSize = sizeof(LOGPALETTE) +
								lpLogPal->palNumEntries * sizeof(PALETTEENTRY));
		if ( lpT ) {
			lpLogPal = lpT;
			GetObject(hPalette, nSize, lpLogPal);
			hPalResult = CreatePalette(lpLogPal);
		}
	}

	HeapFree(GetProcessHeap(), 0, lpLogPal);
	return hPalResult;
}

/*-PUB----------------------------------------------------------------------*
    @func create_resource_palette creates a new palette from a bitmap
    located in the resources of the current program.
    @rdesc This function returns a GDI palette handle or NULL if it
    failed.
 *--------------------------------------------------------------------------*/
HPALETTE create_resource_palette(
    LPCSTR lpszResourceName /* @parm The name of the bitmap resource.       */
)
{
	LPBITMAPINFO	lpbmi = NULL;
	HPALETTE		hPalette = NULL;
	HGLOBAL			hRes;

	if ( lpszResourceName == NULL || *lpszResourceName == 0 )
		return hPalette;

	/* Load bitmap into memory */
	lpbmi = (LPBITMAPINFO)LockResource(hRes = LoadResource(GetModuleHandle(NULL),
		FindResource(GetModuleHandle(NULL), lpszResourceName, RT_BITMAP)
	));

	WINASSERTTEXT(!lpbmi, "Bitmap resource not found");

	if ( lpbmi && dib_num_colors(lpbmi) > 256 )
		hPalette = create_dib_palette(lpbmi);

	if ( lpbmi ) GlobalUnlock(hRes);
	if ( hRes ) FreeResource(hRes);

	return create_dib_palette(lpbmi);
}

/*-PUB----------------------------------------------------------------------*
    @func Function hbitmap_to_ptr creates a DIB from a GDI bitmap (a
    device dependent bitmap). Based on a function I found in the MSL, so I
    don't deserve the full credit.
    @rdesc This function returns a pointer to a new DIB. When no longer
    necessary destroy with <f dib_ptr_free>.
 *--------------------------------------------------------------------------*/
LPBITMAPINFO hbitmap_to_ptr(
    HBITMAP hbmpBitmap,     /* @parm GDI handle of bitmap to create a DIB of */
    HPALETTE hPalette       /* @parm GDI handle of palette to use. May be NULL
                                to use the default system palette.          */
)
{
	BITMAP 				bm;
	BITMAPINFOHEADER 	bi;
	LPBITMAPINFO		lpbmi;
	DWORD 				dwLen;
	HDC 				hDC;
	UINT 				biBits;

	/* Check if bitmap handle is valid */
	if ( !hbmpBitmap ) return NULL;

	/* Get default palette if no palette is specified */
	if ( hPalette == NULL ) hPalette = GetStockObject(DEFAULT_PALETTE);

	/* Fill in BITMAP structure */
	GetObject(hbmpBitmap, sizeof bm, &bm);

	/* Calculate bits per pixel */
	biBits = bm.bmPlanes * bm.bmBitsPixel;

	/* Initialize BITMAPINFOHEADER */
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth; bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1; bi.biBitCount = (WORD)biBits;
	bi.biCompression = DIB_RGB_COLORS;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	/* Calculate size of memory block required to store BITMAPINFO */
	dwLen = bi.biSize + palette_size((LPBITMAPINFO)&bi);

	hDC = GetDC(NULL);

	/* Select and realize our palette */
	hPalette = SelectPalette(hDC, hPalette, FALSE);
	RealizePalette(hDC);

	lpbmi = dib_ptr_alloc((LPBITMAPINFO)&bi);

	/* If we couldn't get memory block */
	if ( !lpbmi ) {
		/* Clean up and return NULL */
		SelectPalette(hDC, hPalette, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
		return NULL;
	}

	/* Use our bitmap info. to fill BITMAPINFOHEADER */
	lpbmi->bmiHeader = bi;

	/* Call GetDIBits with a NULL lpBits param, so it will calculate the
		biSizeImage field for us */
	GetDIBits(hDC, hbmpBitmap, 0, bi.biHeight, NULL, lpbmi, DIB_RGB_COLORS);

	/* Get the info. */
	bi = lpbmi->bmiHeader;

	/* If the driver did not fill in the biSizeImage field, make one up */
	if ( bi.biSizeImage == 0 )
		bi.biSizeImage = WIDTHBYTES((DWORD)bm.bmWidth * biBits) * bm.bmHeight;

	/* Call GetDIBits with a NON-NULL lpBits param, and actualy get the
		bits this time */
	if ( GetDIBits(hDC, hbmpBitmap, 0, (WORD)bi.biHeight, (LPBYTE)lpbmi +
		  lpbmi->bmiHeader.biSize + palette_size(lpbmi),
		  lpbmi, DIB_RGB_COLORS) == 0 ) {
		dib_ptr_free(lpbmi);
		SelectPalette(hDC, hPalette, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
		return NULL;
	}

	/* Clean up */
	SelectPalette(hDC, hPalette, TRUE);
	RealizePalette(hDC);
	ReleaseDC(NULL, hDC);

	/* Return handle to the DIB */
	return lpbmi;
}

/*-PUB----------------------------------------------------------------------*
    @func This function creates a GDI bitmap from a DIB.
    @rdesc Returns a GDI bitmap handle.
 *--------------------------------------------------------------------------*/
HBITMAP ptr_to_hbitmap(
    LPBITMAPINFO lpbmi,     /* @parm Pointer to a DIB.                      */
    HPALETTE hPalette       /* @parm GDI palette handle, may be NULL to use
                                the default system palette.                 */
)
{
	HDC		hDC = GetDC(NULL);
	HBITMAP	hbmp;

	if ( hPalette ) {
		/* Select this palette */
		hPalette = SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC);
	}

	hbmp = CreateDIBitmap(hDC, &(lpbmi->bmiHeader), CBM_INIT,
		find_dib_bits(lpbmi), lpbmi, DIB_RGB_COLORS);

	if ( hPalette ) {
		SelectPalette(hDC, hPalette, TRUE);
		RealizePalette(hDC);
	}

	ReleaseDC(NULL, hDC);
	return hbmp;
}

/*****************/

/*-PUB----------------------------------------------------------------------*
    @func create_shared_dib_atom creates a bitmap which can be shared
    between multiple processes. The shared bitmap is accessible through the
    returned atom. Normally you will use the DibWindow control functions
    to share bitmap, but you can also use the shared bitmap functions.
    @rdesc This function returns a new ATOM, and the address of the mapped
    DIB. Both the ATOM and the address should be used to destroy the
    shared bitmap. The ATOM can be used in interprocess communication.
    Returns NULL if the shared bitmap couldn't be created.
 *--------------------------------------------------------------------------*/
ATOM create_shared_dib_atom(
    LPBITMAPINFO lpbmi,     /* @parm Pointer to the DIB you want to share.  */
    LPSTR lpszName,         /* @parm Name to use for the DIB. You can use
                                this name to access the shared DIB through
                                the Win32 file mapping API or the returned
                                ATOM and related ATOM functions in this
                                module.*/
	LPVOID* lpMappedView    /* @parm Pointer to a pointer receiving the address
	                            where the DIB has been mapped.              */
)
{
	LPSTR                   lpszStr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
							    lstrlen(lpszName) + 1);
	ATOM					hShDib = 0;
	HANDLE					hMapping;
	LPBITMAPINFO			lpnew;
	DWORD					dwSize;

	if ( !lpszStr || !lstrlen(lpszName) ) return hShDib;
	lstrcpy(lpszStr, lpszName);
	lpszName = lpszStr;

	/* Replace back slashes. Backslashes are invalid characters. */
	while ( *lpszStr++ )	if ( *lpszStr == '\\' ) *lpszStr = '_';

	/* Create file mapping object with a name */
	hMapping = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE,
		0, dwSize = dib_size(lpbmi), lpszName);

	if ( !hMapping || GetLastError() ) {
        WINTRACE("Error creating file mapping.");
		HeapFree(GetProcessHeap(), 0, lpszName);
		return 0;
	}

	lpnew = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);

	if ( lpnew ) {
		MemCpy(lpnew, lpbmi, dwSize);

		/* Create a global atom */
		if ( 0 == (hShDib = GlobalAddAtom(lpszName)) )
			UnmapViewOfFile(lpbmi);

#ifdef __debug
		/* This increments the reference count of the atom, so we
			can test whether shared memory area is still available
			(which ofcourse shouldn't be available) */
		GlobalAddAtom(lpszName);
#endif
	}

    /* Return a pointer */
	if ( lpMappedView ) *lpMappedView = lpnew;

	/* We do not unmap the view of file, so it remains open. */
    CloseHandle(hMapping);
	HeapFree(GetProcessHeap(), 0, lpszName);
	return hShDib;
}

/*-PUB----------------------------------------------------------------------*
    @func open_shared_dib_atom returns a file mapping object handle to the
    DIB created with create_shared_dib_atom. Use this function to change the
    attributes of the file mapping object. (Or use access_shared_dib_atom)
    @rdesc Returns the following values:
    @flag INVALID_HANDLE_VALUE | Error
    @flag else                 | Handle of file mapping object associated
    with the shared DIB. If you don't need access through the handle,
    you should close it with CloseHandle().
 *--------------------------------------------------------------------------*/
HANDLE open_shared_dib_atom(
    ATOM hAtom      /* @parm Atom of a shared DIB. This atom may perhaps
                        been received from another planet or a process.     */
)
{
	char		szBuffer[80];
	HANDLE	hMapping;

	if ( !GlobalGetAtomName(hAtom, szBuffer, sizeof szBuffer) ) return NULL;
	hMapping = OpenFileMapping(FILE_MAP_READ, FALSE, szBuffer);
	return  hMapping;
}

/*-PUB----------------------------------------------------------------------*
    @func access_shared_dib_atom access a shared DIB through its ATOM and
    returns a read only pointer.
    @rdesc This function returns NULL if an error occurred or a valid
    address to the DIB.
 *--------------------------------------------------------------------------*/
BITMAPINFO FAR* access_shared_dib_atom(
    ATOM hAtom  /* @parm Atom of a shared DIB. Perhaps received through an
                    IPC mechanism.                                          */
)
{
	HANDLE			hMapping = open_shared_dib_atom(hAtom);
	LPBITMAPINFO   lpbmi = NULL;
	if ( hMapping != NULL && hMapping != INVALID_HANDLE_VALUE ) {
		lpbmi = (LPBITMAPINFO)MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);
		/* Give up access through handle */
		CloseHandle(hMapping);
	}
	return lpbmi;
}

/*-PUB----------------------------------------------------------------------*
    @func unaccess_shared_dib_atom closes access to a DIB previously opened
    access_shared_dib_atom.
    @rdesc This function does not return a value.
 *--------------------------------------------------------------------------*/
VOID unaccess_shared_dib_atom(
    CONST BITMAPINFO FAR* lpbmi /* @parm Pointer to a DIB returned by a call
                                    to access_shared_dib_atom.              */
)
{
	UnmapViewOfFile(lpbmi);
}

/*-PUB----------------------------------------------------------------------*
    @func This function accepts an atom of a shared DIB and creates a new
    copy in the context of the current process. The new copy is not shared
    and should be freed with <f dib_ptr_free>.
    @rdesc Returns NULL if any error occurred, else it returns a pointer
    to a new copy of the shared DIB. The new copy should be deleted with
    <f dib_ptr_free> when no longer necessary.
 *--------------------------------------------------------------------------*/
LPBITMAPINFO copy_shared_dib_atom_ptr(
    ATOM hAtom  /* @parm Atom of a shared DIB.                              */
)
{
	BITMAPINFO FAR* 	lpbmi = access_shared_dib_atom(hAtom);
	LPBITMAPINFO        lpNew = NULL;
	DWORD	            dwSize;

	if ( lpbmi ) lpNew = copy_dib_ptr(lpbmi);

    unaccess_shared_dib_atom(lpbmi);
	return lpNew;
}

/*-PUB----------------------------------------------------------------------*
    @func destroy_shared_dib_atom undoes a previous call to
    <f create_shared_dib_atom>. After the call to this function the bitmap
    is no longer accessible from other processes.
    @rdesc Returns TRUE if successful or FALSE when some error occurred.
 *--------------------------------------------------------------------------*/
BOOL destroy_shared_dib_atom(
    ATOM hAtom,             /* @parm ATOM returned by a previous call to
                                <f create_shared_dib_atom>.                 */
    LPVOID lpMappedView     /* @parm Address returned by <f create_shared_dib_atom>. */
)
{
	if ( !lpMappedView ) return FALSE;

	/* Shake it loose */
	UnmapViewOfFile(lpMappedView);

	GlobalDeleteAtom(hAtom);
	return TRUE;
}

/*****************/

/*** The DIB allocation functions were added later to fill in a major gap
     in the DIB viewer code: some robustness and clarity.

     12-06-95 11:36am
***/

/* Special identification: DIBFUNC */
#define DIB_ID      MAKELONG(MAKEWORD('D', 'F'), MAKEWORD('N', 'C'))
typedef struct {
    DWORD   dwId;
    WORD    wFlags;
} DIBALLOC;

typedef DIBALLOC FAR* LPDIBALLOC;

#define DIBALLOC_METHOD         0x0007
#define DIBALLOC_UNKNOWN        0x0000
#define DIBALLOC_HEAPALLOC      0x0001

/*** all other values between 0 and 7 are reserved! ***/
#define DIBALLOC_GLOBALALLOC    (0x0002)

static BOOL verify_dib_ptr(LPBITMAPINFO lpbmi)
{
    DWORD       dwSize, dwDIBSize;
    LPDIBALLOC  lpAlloc;

    WINTRACE("Enter");
    if ( !lpbmi ) {
        WINASSERTTEXT(!lpbmi, "Invalid parameter");
        return FALSE;
    }

    /* Is this DIB allocated from the heap? */
    if ( 0 == (dwSize = HeapSize(GetProcessHeap(), 0, lpbmi)) ) {
        WINASSERTTEXT(TRUE, "Block not allocated from heap?");
        return FALSE;
    }

    dwDIBSize = dib_size(lpbmi);

    /* Check if this DIB has a tag */
    if ( dwSize < dwDIBSize + sizeof(DIBALLOC) ) {
        WINASSERTTEXT(TRUE, "Block not allocated by dib_ptr_alloc");
        return FALSE;
    }

    lpAlloc = (LPDIBALLOC)((LPBYTE)lpbmi + dwDIBSize);
    if ( lpAlloc->dwId != DIB_ID ) {
        WINASSERTTEXT(TRUE, "Invalid DIBALLOC ID");
        return FALSE;
    }

    WINTRACE("Leave");
    return TRUE;
}

/*-PUB----------------------------------------------------------------------*
    @func dib_ptr_alloc allocates memory for a DIB. It does not copy DIB
    data.
    @rdesc Returns a pointer to the newly allocated block. This block can
    be used to copy DIB data to. You should deallocate this block with
    dib_free_ptr.
 *--------------------------------------------------------------------------*/
LPBITMAPINFO dib_ptr_alloc(
    LPBITMAPINFO lpbmi  /* @parm Pointer to DIB information.                */
)
{
    DWORD           dwDIBSize;
    LPBITMAPINFO    lpNewDib;
    LPDIBALLOC      lpAlloc;

    WINTRACE("Enter");
    if ( !lpbmi ) {
        WINASSERTTEXT(lpbmi == NULL, "Invalid parameter");
        return NULL;
    }

    dwDIBSize = dib_size(lpbmi);

    if ( dwDIBSize == 0 ) {
        WINASSERTTEXT(TRUE, "Invalid bitmapinfo ptr");
        return NULL;
    }

    lpNewDib = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
        dwDIBSize + sizeof(DIBALLOC));
    if ( !lpNewDib ) {
        WINASSERTTEXT(!lpNewDib, "Bitmap allocation failed");
        return NULL;
    }

    lpAlloc = (LPDIBALLOC)((LPBYTE)lpNewDib + dwDIBSize);
    lpAlloc->dwId = DIB_ID;
    lpAlloc->wFlags |= DIBALLOC_HEAPALLOC;

    WINTRACE("Leave");
    return lpNewDib;
}

/*-PUB----------------------------------------------------------------------*
    @func This function frees memory associated with a DIB. The pointer
    should be one returned by dib_ptr_alloc.
    @rdesc Returns TRUE if successful, else FALSE.
 *--------------------------------------------------------------------------*/
BOOL dib_ptr_free(
    LPBITMAPINFO lpbmi  /* @parm DIB previously allocated with dib_ptr_alloc
                            or another function in this module.             */
)
{
    LPDIBALLOC  lpAlloc;
    WINTRACE("Enter");
    if ( !verify_dib_ptr(lpbmi) ) {
        WINASSERTTEXT(TRUE, "Invalid DIB pointer, not ours");
        return FALSE;
    }

    lpAlloc = (LPDIBALLOC)((LPBYTE)lpbmi + dib_size(lpbmi));
    if ( (lpAlloc->wFlags & DIBALLOC_METHOD) != DIBALLOC_HEAPALLOC ) {
        WINASSERTTEXT(TRUE, "Not a HeapAlloc'ed block");
        return FALSE;
    }

    if ( !HeapFree(GetProcessHeap(), 0, lpbmi) ) {
        WINASSERTTEXT(TRUE, "HeapFree failed on DIB");
        return FALSE;
    }

    WINTRACE("Leave");
    return TRUE;
}

/*** End of File ***/