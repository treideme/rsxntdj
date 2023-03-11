#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char * const *argv)
{
    int c;
    int i = 0;
    char buf[81];

    while ((c = getchar()) != EOF)
    {
        buf[i++] = c;

        if (c == '\n' || i == 80)
        {
            buf[i] = 0;
            i = 0;
            printf("->%s", buf);
        }
    }
    return (2);
}
