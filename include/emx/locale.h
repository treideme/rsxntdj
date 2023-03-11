/* emx/locale.h (emx+gcc) */

#ifndef _EMX_LOCALE_H
#define _EMX_LOCALE_H

#if defined (__cplusplus)
extern "C" {
#endif

struct lconv;

/* Multibyte characters (locale-specific) */

#define _MB_8BITS     0         /* No multibyte characters */
#define _MB_DBCS      1         /* OS/2 double-byte character set */
#define _MB_SHIFT     2         /* Some sort of encoding with shift states */
#define _MB_UTF_2     3         /* UTF-2 */

struct _mbyte
{
  unsigned char mode;           /* _MB_8BITS etc. */
};

extern struct _mbyte _cur_mbyte;

int _mbtowc (wchar_t *, __const__ char *, size_t, int *);
int _wctomb (char *, wchar_t, size_t, int *);

/* locales and strftime() */

struct _lcf_time
{
  char *months1[12];
  char *months2[12];
  char *wdays1[12];
  char *wdays2[12];
  char *date_time_fmt;
  char *date_fmt;
  char *time_fmt;
  char *am, *pm;
};

/* These structures contain character arrays instead of character
   pointers to be able to read them from a file (future extension). */

struct lc_collate
{
  char dummy;
};

struct lc_ctype
{
  char dummy;
};

struct lc_monetary
{
  char int_curr_symbol[6];
  char currency_symbol[7];
  char mon_decimal_point[2];
  char mon_thousands_sep[2];
  char mon_grouping[2];
  char positive_sign[2];
  char negative_sign[2];
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
};

struct lc_numeric
{
  char decimal_point[2];
  char thousands_sep[2];
  char grouping[2];
};

struct lc_time
{
  char months1[48];             /* 12 abb. month names, null-terminated */
  char months2[128];            /* 12 month names, null-terminated */
  char wdays1[32];              /* 7 abb. week day names, null-terminated */
  char wdays2[80];              /* 7 week days, null-terminated */
  char date_time_fmt[24];       /* strftime() format for %c */
  char date_fmt[12];            /* strftime() format for %x */
  char time_fmt[12];            /* strftime() format for %X */
  char am[3];                   /* AM indicator for %p */
  char pm[3];                   /* PM indicator for %p */
};

struct lc_data
{
  char               *name;
  struct lc_collate  *collate;
  struct lc_ctype    *ctype;
  struct lc_monetary *monetary;
  struct lc_numeric  *numeric;
  struct lc_time     *time;
};


extern struct _lcf_time _cur_lcf_time;
extern struct lconv _cur_lconv;
extern const struct lc_data _lc_table[];


#if defined (__cplusplus)
}
#endif

#endif /* not _EMX_LOCALE_H */
