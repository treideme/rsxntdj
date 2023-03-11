#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <excpt.h>

struct exception_text
{
    unsigned long code;
    char * text;
};

static char * get_exception_text (unsigned long code)
{
    static struct exception_text exception_text[] =
    {
        {0xC0000005, "ACCESS_VIOLATION"},
        {0xC0000006, "IN_PAGE_ERROR"},
        {0xC0000008, "INVALID_HANDLE"},
        {0xC0000017, "NO_MEMORY"},
        {0xC000001D, "ILLEGAL_INSTRUCTION"},
        {0xC0000025, "NONCONTINUABLE_EXCEPTION"},
        {0xC0000026, "INVALID_DISPOSITION"},
        {0xC000008C, "ARRAY_BOUNDS_EXCEEDED"},
        {0xC000008D, "FLOAT_DENORMAL_OPERAND"},
        {0xC000008E, "FLOAT_DIVIDE_BY_ZERO"},
        {0xC000008F, "FLOAT_INEXACT_RESULT"},
        {0xC0000090, "FLOAT_INVALID_OPERATION"},
        {0xC0000091, "FLOAT_OVERFLOW"},
        {0xC0000092, "FLOAT_STACK_CHECK"},
        {0xC0000093, "FLOAT_UNDERFLOW"},
        {0xC0000094, "INTEGER_DIVIDE_BY_ZERO"},
        {0xC0000095, "INTEGER_OVERFLOW"},
        {0xC0000096, "PRIVILEGED_INSTRUCTION"},
        {0xC00000FD, "STACK_OVERFLOW"},
        {0xC000013A, "CONTROL_C_EXIT"}
    };
    int i;

    for (i = 0; i <= (sizeof(struct exception_text)); ++i)
        if (exception_text[i].code == code)
            return exception_text[i].text;

    return "unknown";
};

static int filter_func (int errcode)
{
    char * err = get_exception_text(errcode);
    int c;

    printf("\n!!got exception '%s' !!\n\n", err);
    printf("continue (y,n):");

    c = getch();
    putchar ('\n');

    if (c == 'n')
        return EXCEPTION_CONTINUE_SEARCH;
    else
        return EXCEPTION_EXECUTE_HANDLER;
}

int main (void)
{
    printf ("Win32 exceptions demo\n\n");

    __try {
        puts ("enter try/excpt block - generate fault (y/n):");
        if (getch() == 'y')
            printf("%d", *(int *) -1);
    }
    __except ((filter_func(GetExceptionCode()))) {
        puts ("excpt handler handles exception");
    }
    puts ("end of try/excpt block 1\n");

    __try {
        puts ("enter try/finally block - generate fault (y/n):");
        if (getch() == 'y')
            printf("%d", *(int *) -1);
    }
    __finally  {
        puts ("this code is only called if there is no exception");
    }
    puts ("end of try/finally block 1");

    return 0;
}
