/*
    This example uses the new keyword __endtry.

    With this keyword all finally handlers are called.
*/

#define RSXNT_SEH /* use other finally handler */

#include <stdio.h>
#include <excpt.h>

#if !defined (__GNUC__)  /* make other compilers happy */
#define __endtry
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void block3 ()
{
    __try {
	puts("try block 3");
	printf("%d\n", *(int *)-1); /* FAULT! */
    }
    __finally {
	puts("finally block 3");
        printf("abnormal term = %d\n", AbnormalTermination());
    }
    __endtry;
    puts ("end of block 3");
}

void block2 ()
{
    __try {
	puts("try block 2");
	block3();
    }
    __finally {
	puts("finally block 2");
        printf("abnormal term = %d\n", AbnormalTermination());
    }
    __endtry;
    puts ("end of block 2");
}

unsigned long filter (EXCEPTION_POINTERS * ep)
{
    printf("filter 1 exception=%X\n", ep->ExceptionRecord->ExceptionCode);

    return EXCEPTION_EXECUTE_HANDLER;
}

int main ()
{
    __try {
        __try {
            puts("try block 1");
            block2();
        }
        __except ((filter((EXCEPTION_POINTERS *) GetExceptionInformation()))) {
            puts ("except 1");
        }
        __endtry;
    }
    __finally {
        printf("abnormal term = %d\n", AbnormalTermination());
    }
    __endtry;

    puts ("end");
    return 0;
}
