#include <stdio.h>
#include <unistd.h>
#include <process.h>

int main(int argc, char **argv)
{
    int ret;
    if (argc < 2) {
        puts("This program is for use with rsxide");
        puts("usage: runcon <program> <args>");
        return (1);
    }
    if ((ret = spawnvp (P_WAIT, argv[1], argv + 1)) != -1)
    {
      const char msg[] = "press <return> to close this window ...";
      char buf [4];
      
      write (1, msg, sizeof(msg) - 1);
      read (0, buf, sizeof(buf));
    }
    return ret;
}

