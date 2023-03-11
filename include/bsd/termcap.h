/* bsd/termcap.h (emx+gcc) */

#ifndef _TERMCAP_H
#define _TERMCAP_H

#if defined (__cplusplus)
extern "C" {
#endif

extern char *UP;
extern char *BC;
extern char PC;

int tgetent (char *, const char *);
int tgetnum (const char *);
int tgetflag (const char *);
char *tgetstr (const char *, char **);
char *tgoto (const char *, int, int);
int tputs (const char *, int, int (*)());

#if defined (__cplusplus)
}
#endif

#endif /* not _TERMCAP_H */
