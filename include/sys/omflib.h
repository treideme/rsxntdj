/* sys/omflib.h (emx+gcc) */

/* Public header file for the emx OMFLIB library. */

#ifndef _SYS_OMFLIB_H
#define _SYS_OMFLIB_H

#if defined (__cplusplus)
extern "C" {
#endif


#if !defined (THEADR)

#define THEADR 0x80
#define LHEADR 0x82
#define COMENT 0x88
#define MODEND 0x8a
#define PUBDEF 0x90
#define ALIAS  0xc6
#define LIBHDR 0xf0
#define LIBEND 0xf1

#define REC32  0x01

#endif

/* Comment classes */

#if !defined (IMPDEF_CLASS)

#define IMPDEF_CLASS    0xa0
#define LIBMOD_CLASS    0xa3

#define IMPDEF_SUBTYPE  0x01

#endif

struct omflib;

struct omflib *omflib_open (const char *fname, char *error);
struct omflib *omflib_create (const char *fname, int page_size, char *error);
int omflib_close (struct omflib *p, char *error);
int omflib_module_name (char *dst, const char *src);
int omflib_find_module (struct omflib *p, const char *name, char *error);
int omflib_mark_deleted (struct omflib *p, const char *name, char *error);
int omflib_pubdef_walk (struct omflib *p, word page,
    int (*walker)(const char *name, char *error), char *error);
int omflib_extract (struct omflib *p, const char *name, char *error);
int omflib_add_module (struct omflib *p, const char *fname, char *error);
int omflib_module_count (struct omflib *p, char *error);
int omflib_module_info (struct omflib *p, int n, char *name, int *page,
    char *error);
int omflib_copy_lib (struct omflib *dst, struct omflib *src, char *error);
int omflib_finish (struct omflib *p, char *error);
int omflib_write_record (struct omflib *p, byte rec_type, word rec_len,
    const byte *buffer, int chksum, char *error);
int omflib_write_module (struct omflib *p, const char *name, word *pagep,
    char *error);
int omflib_add_pub (struct omflib *p, const char *name, word page,
    char *error);
int omflib_header (struct omflib *p, char *error);
int omflib_find_symbol (struct omflib *p, const char *name, char *error);
long omflib_page_pos (struct omflib *p, int page);

#if defined (__cplusplus)
}
#endif

#endif /* not _SYS_OMFLIB_H */
