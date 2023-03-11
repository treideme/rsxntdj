/* dibopen.h - A common dialog for opening and previewing DIB files.
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */
#ifndef __dibopen_h
#define __dibopen_h

#ifdef __cplusplus
extern "C" {
#endif
BOOL _get_open_dib_file (HWND, LPCSTR, int*, LPSTR, int, LPBITMAPINFO*, BOOL);
BOOL get_open_dib_file (HWND, LPCSTR, LPSTR, int, LPBITMAPINFO*, BOOL);
#ifdef __cplusplus
}
#endif

#endif /* !__dibopen_h */

