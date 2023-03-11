/* dllso/dllinit.c (emx+gcc) -- Copyright (c) 1994-1996 by Eberhard Mattes */

int _CRT_init (void);
void _CRT_term (void);
void __ctordtorInit (void);
void __ctordtorTerm (void);

unsigned long _DLL_InitTerm (unsigned long mod_handle, unsigned long flag)
{
  switch (flag)
    {
    case 0:
      if (_CRT_init () != 0)
        return 0;
      __ctordtorInit ();
      return 1;
    case 1:
      __ctordtorTerm ();
      _CRT_term ();
      return 1;
    default:
      return 0;
    }
}
