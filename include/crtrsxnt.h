#ifdef __CRTRSXNT__ /** define this symbols only if -Zcrtdll=crtrsxnt is used **/

/** ----- ctype.h  ---------------------------------------------------------- **/
#define _ctype (**_ctype)

/** ----- getopt.h / unistd.h ----------------------------------------------- **/
#define optarg (**optarg)
#define optind (**optind)
#define opterr (**opterr)
#define optopt (**optopt)
#define optswchar (**optswchar)
#define optmode (**optmode)

#if !defined (_POSIX_SOURCE) || defined (_WITH_UNDERSCORE)
#define _optarg (**_optarg)
#define _optind (**_optind)
#define _opterr (**_opterr)
#define _optopt (**_optopt)
#endif

/** ----- stdlib.h ---------------------------------------------------------- **/
#ifndef __MT__
#define __ST_MT_ERRNO__
#endif
#if !defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)
#define _mb_cur_max (**_mb_cur_max)
#define environ (**environ)
#define sys_errlist (**sys_errlist)
#define sys_nerr (**sys_nerr)
#define _emx_env (**_emx_env)
#define _emx_rev (**_emx_rev)
#define _emx_vcmp (**_emx_vcmp)
#define _osminor (**_osminir)
#define _osmajor (**_osmajor)
#define _osmode (**_osmode)
#define _emx_vprt (**_emx_vptr)
#endif
#if (!defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)) \
    || defined (_WITH_UNDERSCORE)
#define _environ (**_environ)
#define _sys_errlist (**_sys_errlist)
#define _sys_nerr (**_sys_nerr)
#endif

/** stdio.h **/
#define _streamv (**_streamv)

/** ----- time.h ------------------------------------------------------------ **/
#if !defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)
#define daylight (**daylight)
#define timezone (**timezone)
#define tzname (**tzname)
#endif
#if (!defined (__STRICT_ANSI__) && !defined (_POSIX_SOURCE)) \
    || defined (_WITH_UNDERSCORE)
#define _daylight (**_daylight)
#define _timezone (**_timezone)
#define _tzname (**_tzname)
#endif

/** ----- sys/nls.h --------------------------------------------------------- **/
#define _nls_tolower_tab (**_nls_tolower_tab)
#define _nls_toupper_tab (**_nls_toupper_tab)
#define _nls_ctype_tab (**_nls_ctype_tab)

/** ----- emx\startup.h ----------------------------------------------------- **/
#define _org_environ (**_org_environ)
#define _cdll_flag (**_cdll_flag)

/** ----- emx\time.h -------------------------------------------------------- **/
#define _tzset_flag (**_tzset_flag)

/** ----- no headers (but exported) ----------------------------------------- **/

#define _files (**_files)
#define _fmode_bin (**_fmode_bin)
#define _lookahead (**_lookahead)
#define _pipe_size (**_pipe_size)
#define __new_handler (**__new_handler)

#endif

