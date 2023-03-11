/*
    this program tests:
        - fork()
        - clock time for fork()
        - valid handles
*/

#include <crtrsxnt.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int pid;
    int i, j;
    clock_t t1, t2;

    t1 = clock();

    puts("sleep 1 second ..");
    sleep(1);

    pid = fork();

    if (pid == -1) {
        perror ("fork()");
        exit (1);
    }
    else if (pid != 0)
        printf("father process, child pid = %d\n", pid);
    else
        printf("child process\n");

    puts("sleep 1 second ..");
    sleep(1);

    t2 = clock();

    if (pid == 0) {
        printf("here is the child process pid = %d\n", getpid());
        printf ("alive = %ld sec\n", (t2 - t1) / CLK_TCK);
    }
    else {
        wait(&j);
        puts("here is the father process");
        printf ("alive = %ld sec\n", (t2 - t1) / CLK_TCK);
    }

    for (i = 0; i < 40; ++i)
      if (_ioctl (i, FGETHTYPE, &j) >= 0)
            printf("%d is a valid handle\n", i);

    return 0;
}
