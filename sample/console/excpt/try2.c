#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <excpt.h>

#ifndef EXCEPTION_ACCESS_VIOLATION
#define EXCEPTION_ACCESS_VIOLATION (0xC0000005L)
#endif

int main (void)
{
    __try {
        puts ("enter try block1 - generate fault (y/n):");
        if (getch() == 'y')
            printf("%d", *(int *) -1);

        __try {
            puts ("enter try block2 - generate fault (y/n):");
            if (getch() == 'y')
                printf("%d", *(int *) -1);
        }
        __except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION)
                    ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
            puts ("access violation");
            puts ("except 2 block");
        }
        puts ("end of try/except block 2");

        puts ("back in try block1 - generate fault (y/n):");
        if (getch() == 'y')
            printf("%d", *(int *) -1);

    }
    __except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION)
                ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
        puts ("access violation");
        puts ("except 1 block");
    }
    puts ("end of try/except block 1\n");

    puts ("enter normal code - generate fault (y/n):");
    if (getch() == 'y')
        printf("%d", *(int *) -1);

    return 0;
}
