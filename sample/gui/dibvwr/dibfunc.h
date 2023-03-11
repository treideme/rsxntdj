/* dibfunc.h - Functions for handling DIB data in 10 and odd ways.
 * Some functions we're based on the dibutil module of Microsoft,
 * but were rewritten for the dibwin control.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

#ifndef __dibfunc_h
#define __dibfunc_h


/*** DIB macro's ***/
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define WIDTHBYTES(bits)	(((bits) + 31) / 32 * 4)

/*** Resource identifiers ***/
#define BITMAP_256COLORS		"BMP256"
#define BITMAP_16COLORS			"BMP16"
#define BITMAP_GRAY				"BMPGRAY"


#ifdef __cplusplus
extern "C" {
#endif
int find_dib_bits_offset (HGLOBAL);
LPBYTE find_dib_bits (LPBITMAPINFO);
int palette_size (LPBITMAPINFO);
DWORD dib_size (LPBITMAPINFO);
int dib_num_colors (LPBITMAPINFO);
int get_scanline_size (LPBITMAPINFO);

LPBITMAPINFO copy_dib_ptr (LPBITMAPINFO);
HGLOBAL copy_dib_handle (LPBITMAPINFO);
LPBITMAPINFO copy_handle_dib (HGLOBAL, BOOL);
HPALETTE create_dib_palette (LPBITMAPINFO);
HPALETTE copy_palette (HPALETTE);
HPALETTE create_resource_palette (LPCSTR);

LPBITMAPINFO hbitmap_to_ptr (HBITMAP, HPALETTE);
HBITMAP ptr_to_hbitmap(LPBITMAPINFO, HPALETTE);

ATOM create_shared_dib_atom (LPBITMAPINFO, LPSTR, LPVOID*);
HANDLE open_shared_dib_atom (ATOM);
BITMAPINFO FAR* access_shared_dib_atom (ATOM);
VOID unaccess_shared_dib_atom (CONST BITMAPINFO FAR*);
LPBITMAPINFO copy_shared_dib_atom_ptr (ATOM);
BOOL destroy_shared_dib_atom (ATOM, LPVOID);

LPBITMAPINFO dib_ptr_alloc (LPBITMAPINFO);
BOOL dib_ptr_free (LPBITMAPINFO);
#ifdef __cplusplus
}
#endif

#endif /* !__dibfunc_h */