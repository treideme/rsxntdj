/* sys/nls.h (emx+gcc) */

#ifndef _SYS_NLS_H
#define _SYS_NLS_H

#if defined (__cplusplus)
extern "C" {
#endif

#define _NLS_DBCS_LEAD  0x01

extern unsigned char _nls_toupper_tab[256];
extern unsigned char _nls_tolower_tab[256];
extern unsigned char _nls_ctype_tab[256];

#define _nls_tolower(c) _nls_tolower_tab[c]
#define _nls_toupper(c) _nls_toupper_tab[c]

#define _nls_is_dbcs_lead(c) _nls_ctype_tab[c]

void _nls_init (void);
unsigned char *_nls_strlwr (unsigned char *string);
unsigned char *_nls_strupr (unsigned char *string);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_NLS_H */
