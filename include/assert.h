/* assert.h (emx+gcc) */

#if defined (__cplusplus)
extern "C" {
#endif

#undef assert

#if defined (NDEBUG)
#define assert(exp) ((void)0)
#else
void _assert (__const__ char *, __const__ char *, unsigned);
#define assert(exp) ((exp) ? (void)0 : _assert (#exp, __FILE__, __LINE__))
#endif

#if defined (__cplusplus)
}
#endif
