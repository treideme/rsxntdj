/*
    multithread example

    uses C-lib _beginthread()
*/

#ifdef __GNUC__
#include <crtrsxnt.h>       /* if compiled with -Zcrtdll=rsxntcm */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <process.h>

#ifndef __MT__
#error You forgot to define -Zmt
#endif

#ifdef USE_PUTCHAR
#define OUT(c) {putchar(c); fflush(stdout); sleep(0);}
#else
#define OUT(c) {write (1, &(c), 1); sleep(0);}
#endif

void mythread (void *param)
{
    int i;
    char c = (char) (int) param;

    for (i = 0; i < 1024; ++i)
        OUT(c);
}

int main()
{
    if (_beginthread(mythread, NULL, 8192, (void *) '+') == -1) {
        puts("error: cannot create thread");
        return(1);
    }
    if (_beginthread(mythread, NULL, 8192, (void *) '-') == -1) {
        puts("error: cannot create thread");
        return(1);
    }
    getchar ();
    return 0;
}
