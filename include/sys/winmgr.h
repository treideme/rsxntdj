/* sys/winmgr.h (emx+gcc) */

#ifndef _SYS_WINMGR_H
#define _SYS_WINMGR_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (__GNUC__)
#if !defined (__const__)
#define __const__ const
#endif
#endif

#if !defined (B_BLACK)

/* Background colors */

#define B_BLACK      0x00
#define B_BLUE       0x10
#define B_GREEN      0x20
#define B_CYAN       0x30
#define B_RED        0x40
#define B_MAGENTA    0x50
#define B_YELLOW     0x60
#define B_BROWN      0x60
#define B_WHITE      0x70

/* Foreground colors */

#define F_BLACK      0x00
#define F_BLUE       0x01
#define F_GREEN      0x02
#define F_CYAN       0x03
#define F_RED        0x04
#define F_MAGENTA    0x05
#define F_YELLOW     0x06
#define F_BROWN      0x06
#define F_WHITE      0x07

/* Other attributes */

#define INTENSITY    0x08
#define BLINK        0x80

/* black and white attributes */

#define BW_BLANK     0x00
#define BW_UNDERLINE 0x01
#define BW_NORMAL    0x07
#define BW_REVERSE   0x70

#endif

struct _FILE;

typedef struct _wm_window *wm_handle;

void wm_attrib (wm_handle wh, int a);
void wm_attrib_all (wm_handle wh, int a);
void wm_backsp (wm_handle wh, int count);
void wm_border (wm_handle wh, int bflag, int battr, __const__ char *title,
    int tflag, int tattr);
void wm_bottom (wm_handle wh);
void wm_chide (int flag);
void wm_clear (wm_handle wh);
void wm_close (wm_handle wh);
void wm_close_all (void);
void wm_clr_eol (wm_handle wh, int x, int y);
wm_handle wm_create (int x0, int y0, int x1, int y1, int border, int battr,
    int wattr);
void wm_ctype (wm_handle wh, int start, int end);
void wm_cursor (wm_handle wh);
void wm_cvis (wm_handle wh, int flag);
void wm_del_char (wm_handle wh, int x, int y, int count);
void wm_del_line (wm_handle wh, int y, int count);
void wm_delete (wm_handle wh);
void wm_dimen (wm_handle wh, int *width, int *height);
void wm_down (wm_handle wh);
void wm_exit (void);
wm_handle wm_find (int x, int y);
int wm_get_attrib (wm_handle wh);
wm_handle wm_get_cursor (void);
void wm_get_pos (wm_handle wh, int *x, int *y);
int wm_getx (wm_handle wh);
void wm_getxy (wm_handle wh, int *x, int *y);
int wm_gety (wm_handle wh);
void wm_gotoxy (wm_handle wh, int x, int y);
void wm_ins_char (wm_handle wh, int x, int y, int count);
void wm_ins_line (wm_handle wh, int y, int count);
int wm_init (int n);
void wm_move (wm_handle wh, int x, int y);
void wm_open (wm_handle wh);
void wm_puta_at (wm_handle wh, int x, int y, int a, int count);
void wm_putc (wm_handle wh, char c);
void wm_putc_at (wm_handle wh, int x, int y, char c);
void wm_putca (wm_handle wh, char c, int a);
void wm_putca_at (wm_handle wh, int x, int y, char c, int a);
void wm_puts (wm_handle wh, __const__ char *str);
void wm_puts_at (wm_handle wh, int x, int y, __const__ char *str);
void wm_putsa (wm_handle wh, __const__ char *str, int len);
void wm_putsa_at (wm_handle wh, int x, int y, __const__ char *str, int len);
void wm_scroll (wm_handle wh, int count);
void wm_top (wm_handle wh);
void wm_up (wm_handle wh);
void wm_update (wm_handle wh, int flag);
void wm_wrap (wm_handle wh, int wrap_flag);


#if defined (__EMX__)

#if !defined (_VA_LIST)
#define _VA_LIST
typedef char *va_list;
#endif

int wm_fclose (struct _FILE *stream);
struct _FILE *wm_fopen (wm_handle wh);

#if defined (__GNUC__)
int wm_printf (wm_handle wh, __const__ char *fmt, ...)
        __attribute__ ((__format__ (__printf__, 2, 3)));
int wm_vprintf (wm_handle wh, __const__ char *fmt, va_list arg_ptr)
        __attribute__ ((__format__ (__printf__, 2, 0)));
#else
int wm_printf (wm_handle wh, __const__ char *fmt, ...);
int wm_vprintf (wm_handle wh, __const__ char *fmt, va_list arg_ptr);
#endif
#endif

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_WINMGR_H */
