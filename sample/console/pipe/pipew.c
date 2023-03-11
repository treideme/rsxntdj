#include <stdio.h>
#include <stdlib.h>

int main ()
{
    FILE *fil = fopen ("pipew.c", "rt");
    int c;

    if (fil)
    {
        while ((c = getc(fil)) != EOF)
            putchar (c);

        fclose (fil);
    }

    return (1);
}
