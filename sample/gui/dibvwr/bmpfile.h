/* bmpfile.h, plain and simple dib file functions
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

#ifndef __bmpfile_h
#define __bmpfile_h

#ifdef __cplusplus
extern "C" {
#endif
LPBITMAPINFO read_bmp_file_win32_ptr (LPCSTR);
DWORD write_bmp_file_win32_ptr (LPCSTR, LPBITMAPINFO);
#ifdef __cplusplus
}
#endif

#endif