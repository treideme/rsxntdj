/* cdlgtool.h - Common dialog tools by Alfons Hoogervorst
 *
 * Written by Alfons Hoogervorst, 1995-1997, proteus@worldaccess.nl.        */

#ifndef __CDLGTOOL_H
#define __CDLGTOOL_H

#ifndef WIN32
#ifndef MAX_PATH
#define MAX_PATH        255
#endif
typedef UINT (CALLBACK* LPOFNHOOKPROC) (HWND, UINT, WPARAM, LPARAM);
#endif

#ifdef __cplusplus
extern "C" {
#endif
void PreTranslateHookMessage (HWND, UINT, WPARAM, LPARAM);
int GetCurrentPath (HWND, LPSTR, int);
int GetSelectedFilePath (HWND, LPSTR, int);
HINSTANCE __CurrentInstance (void);
#ifdef __cplusplus
}
#endif

#ifndef CurrentInstance
#define CurrentInstance __CurrentInstance
#endif

#endif /* __CDLGTOOL_H */