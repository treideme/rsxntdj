#ifndef _idedlg_h
#define _idedlg_h

BOOL CALLBACK DialogInput          (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogTarget         (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogTargetGCCFlags (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogTargetCPPFlags (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogTargetCCFlags  (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogTargetLDFlags  (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogIdeFlags       (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogAbout          (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogInfo           (HWND, UINT, WPARAM, LPARAM);

#endif

