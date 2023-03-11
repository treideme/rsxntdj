/* dllnrt/dllinit.c (emx+gcc) -- Copyright (c) 1994-1996 by Eberhard Mattes */

void __ctordtorInit (void);
void __ctordtorTerm (void);

unsigned long _DLL_InitTerm (unsigned long mod_handle, unsigned long flag)
{
  switch (flag)
    {
    case 0:
      __ctordtorInit ();
      return 1;
    case 1:
      __ctordtorTerm ();
      return 1;
    default:
      return 0;
    }
}
