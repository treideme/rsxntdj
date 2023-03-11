/*
    Demo for the new findfirst structure for RSX** runtime environment
*/

#ifdef __GNUC__
#include <crtrsxnt.h>       /* if compiled with -Zcrtdll=crtrsxnt */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <emx/syscalls.h>

#pragma pack (1)
struct _lfn_find {
  unsigned long lfn_handle;         /* find handle      */
  unsigned char lfn_attr;           /* attr for handle  */
  unsigned char magic[3];           /* = "LFN"          */
  char shortname[13];               /* DOS name         */

  unsigned char  attr;
  unsigned short time;
  unsigned short date;
  unsigned short size_lo;
  unsigned short size_hi;
  char name[257];
};
#pragma pack ()

/* --------------------------------------------------------------- */

void handle_entry(struct _find *ff)
{
    struct _lfn_find *lfn = (struct _lfn_find *) ff;

    if (memcmp (lfn->magic, "LFN", 3) == 0)
        printf("%12s %s\n", lfn->shortname, lfn->name);
    else
        printf("%s\n", lfn->name);
}

void handle_dir(char *dir)
{
    printf("Directory : %s\n", dir);
}

void enter_dir (char * startdir)
{
    struct _find  ff;
    char          dir[260];

    handle_dir (startdir);

    strcpy(dir, startdir);
    strcat(dir, "*.*");

    if (__findfirst(dir, _A_SUBDIR /*| _A_NORMAL*/, &ff) == 0)
    {
        do
        {
            if (ff.attr & _A_SUBDIR)
            {
                if (!strcmp(ff.name, ".") || !strcmp(ff.name, ".."))
                    continue;
                strcpy(dir, startdir);
                strcat(dir, ff.name);
                strcat(dir, "\\");
                enter_dir(dir);
            }
            else
                handle_entry (&ff);
        }
        while (!__findnext(&ff));
    }
}

int main (int argc, char ** argv)
{
    char path [260];
    if (argc > 1)
    {
        int l = strlen (argv[1]);
        memcpy (path, argv[1], l + 1);
        if (l == 0 || path[l-1] != '\\')
            strcpy (path + l , "\\");
    }
    else
    {
        char * p = path;
        getcwd (path, 260);
        strcat (path, "\\");
        do
        {
            if (*p == '/')
                *p = '\\';
        }
        while (*++p);
    }
    enter_dir(path);
    return 0;
}
