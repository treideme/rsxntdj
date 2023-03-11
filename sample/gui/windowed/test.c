/*
   This application is a demo to use the rsxioapp library
*/

#include <stdio.h>
#include <stdlib.h>
#include <rsxioapp.h>

/*
    styles of rsxio window (optional)

    title: text in window caption
    close: close window on exit
*/

char rsxio_window_title[] = "This is a test of rsxioapp";
int rsxio_window_close = 1;

int rsxio_main(int argc, char **argv, char **env)
{
    int d;

    for (;;) {
        printf("\033[1;36m colour (0-7) (-1=exit) :");

        scanf("%d", &d);
        if (d < 0 || d > 7)
            break;
        else
            printf("\033[1;%dm ++++++++ this is a test string ++++++++\n", 30+d);
    }
    printf("\033[0m");
    getchar();
    puts("type <enter> for exit");
    getchar();

    return 0;
}
