#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <process.h>
#include <string.h>

int main(int argc, char ** argv)
{
    int pid;

    if (argc > 1 && strcmp (argv[1], "!exec!") == 0)
    {
        puts ("exec child");
        exit (1);
    }

    pid = fork();

    if (pid == -1) {
        perror ("fork()");
        exit (2);
    }
    else if (pid == 0)
    {
        printf("child process\n");
        sleep(1);
        if (argc > 1 && strcmp (argv[1], "exec") == 0)
            execl (argv[0], argv[0], "!exec!", NULL);
        return getpid();
    }
    else
    {
        int status = 0;
        int ret = wait(&status);
        if (ret == -1)
            perror ("wait()");
        if ((status & 0xff) == 0)
            printf("father: pid = %d, exit status = %d\n", ret, status>>8);
    }
    return 0;
}
