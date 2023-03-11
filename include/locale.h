/* locale.h (emx+gcc) */

#ifndef _LOCALE_H
#define _LOCALE_H

#if defined (__cplusplus)
extern "C" {
#endif

#if !defined (NULL)
#if defined (__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MONETARY     3
#define LC_NUMERIC      4
#define LC_TIME         5

#define LC_C             "C"
#define LC_C_FRANCE      "FRAN"
#define LC_C_GERMANY     "GERM"
#define LC_C_ITALY       "ITAL"
#define LC_C_SPAIN       "SPAI"
#define LC_C_UK          "UK"
#define LC_C_USA         "USA"

struct lconv
{
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
};


char *setlocale (int, __const__ char *);

struct lconv *_localeconv (int);
struct lconv *localeconv (void);

#if defined (__CHAR_UNSIGNED__)
#define localeconv() _localeconv (255)
#else
#define localeconv() _localeconv (127)
#endif

#if defined (__cplusplus)
}
#endif

#endif /* not _LOCALE_H */
