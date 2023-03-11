/* sys/video.h (emx+gcc) */

#ifndef _SYS_VIDEO_H
#define _SYS_VIDEO_H

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

/* v_hardware() return values */

#define V_COLOR_8    1
#define V_COLOR_12   2
#define V_MONOCHROME 3

/* v_scroll() */

#define V_SCROLL_UP    0
#define V_SCROLL_DOWN  1
#define V_SCROLL_LEFT  2
#define V_SCROLL_RIGHT 3
#define V_SCROLL_CLEAR 4

struct _FILE;

void v_attrib (int a);
void v_backsp (int count);
void v_clear (void);
void v_clreol (void);
void v_ctype (int start, int end);
void v_delline (int count);
void v_dimen (int *width, int *height);
int v_fclose (struct _FILE *stream);
struct _FILE *v_fopen (void);
int v_getattr (void);
void v_getctype (int *start, int *end);
void v_getline (char *dst, int x, int y, int count);
void v_getxy (int *x, int *y);
void v_gotoxy (int x, int y);
int v_hardware (void);
void v_hidecursor (void);
int v_init (void);
void v_insline (int count);
void v_putc (char c);
void v_putline (__const__ char *src, int x, int y, int count);
void v_putm (__const__ char *str, int len);
void v_putmask (__const__ char *src, __const__ char *mask, int x, int y,
    int count);
void v_putn (char c, int count);
void v_puts (__const__ char *str);
void v_scroll (int tl_x, int tl_y, int br_x, int br_y, int count, int flag);
void v_scrollup (void);

#if defined (__EMX__)

#if !defined (_VA_LIST)
#define _VA_LIST
typedef char *va_list;
#endif

#if defined (__GNUC__)
int v_printf (__const__ char *fmt, ...)
        __attribute__ ((__format__ (__printf__, 1, 2)));
int v_vprintf (__const__ char *fmt, va_list arg_ptr)
        __attribute__ ((__format__ (__printf__, 1, 0)));
#else
int v_printf (__const__ char *fmt, ...);
int v_vprintf (__const__ char *fmt, va_list arg_ptr);
#endif
#endif

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_VIDEO_H */
