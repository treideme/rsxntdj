/*
    argvenv:

	- dual mode program
	- use Win32 Api if the program runs under rsxnt
*/

#ifdef __GNUC__
#include <crtrsxnt.h>	    /* if compiled with -Zcrtdll=crtrsxnt */
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

/*
    check runtime system:

    the _emx_env variable defines runtime flags

    if the rsx bit is set, the application runs under rsx, rsxwin or rsxnt
     then the _emx_rev variable contains rsx runtime flags
     the high word defines the runtime system under rsx**
*/

#define BIT_RSX 0x1000L

#define RSX_IS_RUNNING	    0
#define RSXWIN_IS_RUNNING   1
#define RSXNT_IS_RUNNING    2

static int print_runtime()
{
    char *runtime;
    int version;

    if (_emx_env & BIT_RSX) {
        int rsx_runtime = _emx_rev >> 16;
        version = _emx_rev & 0xFFFF;

        if (rsx_runtime == RSX_IS_RUNNING)
            runtime = "RSX";

        else if (rsx_runtime == RSXWIN_IS_RUNNING)
            runtime = "RSXWIN";

        else if (rsx_runtime == RSXNT_IS_RUNNING)
            runtime = "RSXNT";

        else
            runtime = "unkown rsx system";
    }
    else
    {
        runtime = "EMX";
        version = _emx_rev;
    }
    printf("EMX version number %s\n", _emx_vprt);
    printf("Runtime environment: %s\n"
           "Version %X.%X\n",
                runtime, version >> 8, version & 0xff);
    return 0;
}

static int check_rsxnt_runtime()
{
    if ((_emx_env & BIT_RSX) && (_emx_rev >> 16 == RSXNT_IS_RUNNING))
        return 1;
    else
        return 0;
}

/*
    print win32 GetVersion flags
*/

static void print_win32_version(void)
{
    DWORD ver = GetVersion();
    char *s;

    printf("\nWindows version %ld.%ld\n", ver & 0xff, (ver>>8) & 0xff);
    printf("build %ld\n", (ver >> 16) & 0x3fff);

    if (!(ver & 0x80000000))
	s = "NT";
    else if (ver & 0x40000000)
	s = "95";
    else
	s = "3.x + Win32s";

    printf("System: Windows %s\n", s);
}

int main(int argc, char **argv, char **env)
{
    int i;

    _envargs (&argc, &argv, "ARGS");
    _response (&argc, &argv);
    _wildcard (&argc, &argv);

    printf("Environment:\n");
    for (i=0;env[i]!=NULL;++i)
	printf("%02d: %s\n",i,env[i]);
    putchar ('\n');
    fflush (stdout);

    printf("Arguments:\n");
    for (i=0;argv[i]!=NULL;++i)
	printf("%02d: %s\n",i,argv[i]);
    putchar ('\n');
    fflush (stdout);

    print_runtime();
    if (check_rsxnt_runtime())
	print_win32_version();

    return 0;
}
