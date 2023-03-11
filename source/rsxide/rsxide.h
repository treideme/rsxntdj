#ifndef _rsxide_h
#define _rsxide_h

/* IDs for MDI windows */
#define IDC_LIST        500
#define IDC_COMPILE     501

enum { rt_static = 0, rt_crtdll, rt_norte, rt_sys };
enum { opt_l2 = 0, opt_none, opt_l1, opt_l3 };
enum { warn_all = 0, warn_none, warn_extra };
enum { style_gnu = 0, style_ansi, style_traditional };

union target_flags {
    char _old[6][260]; /* version 1.0 */

    struct {
        // general
        int  gcc_runtime;
        int  gcc_multithread:1;
        int  gcc_debug:1;
        int  gcc_print:1;
        int  gcc_pipe:1;
        int  gcc_reserved[6];
                
        // preprocessor
        int  cpp_nostdinc:1;
        int  cpp_reserved[7];

        // compiler
        int cc1_opt;
        int cc1_warnings;
        int cc1_style;
        int cc1_486:1;
        int cc1_ebp:1;
        int cc1_pedantic:1;
        int cc1_error:1;
        int cc1_sigchar:1;
        int cc1_unsigbit:1;
        int cc1_writestr:1;
        int cc1_reserved[4];
        
        // linker
        int  ld_nostdo:1;
        int  ld_nostdlib:1;
        int  ld_reserved[7];

        int  string_options;

        // strings
        char * gcc_other;
        char * cpp_include;
        char * cpp_macros;
        char * cpp_umacros;
        char * cpp_incfile;
        char * cpp_incmac;
        char * cpp_other;
        char * cc1_other;
        char * ld_libs;
        char * ld_ldir;
        char * ld_other;        
        char * second_link_cmd;
    } s;
};
#define STRING_OPTIONS 12

enum { type_win32 = 0, type_dll, type_lib, type_rsx, type_emx };

struct target {
    int                     type;
    HWND                    hWndTarget;
    HWND                    hWndTargetTreeView;
    char                    szTargetName[260];
    union  target_flags     flags;
    int                     nfiles;
    char                    **sourcefiles;
    char                    **objectfiles;
};

struct target_desc {
    char    *title;
    char    *ext;
};

extern HINSTANCE hInstance;
extern struct target_desc target_desc[];

BOOL run_cmd_win32(LPSTR lpszCmdLine, HWND hListWnd, HWND hWndIde, LPSTR);
BOOL run_cmd_win32s(LPSTR lpszCmdLine, HWND hListWnd, HWND hWndIde, LPSTR);

#endif

