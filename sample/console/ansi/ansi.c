/*
    This example shows the ansi functions inside rsxnt.dll.

    To enable ansi emulation, you must use rsxntopt.
*/
      
#ifdef __GNUC__
#include <crtrsxnt.h>       /* if compiled with -Zcrtdll=crtrsxnt */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
    some ansi functions
*/
#define BLACK   0
#define RED     1
#define GREEN   2
#define YELLOW  3
#define BLUE    4
#define MAGNETA 5
#define CYAN    6
#define WHITE   7
#define ANSI_GOTOXY(z,s)    printf("\033[%d;%dH", (z), (s))
#define ANSI_CLEAR_SCREEN() printf("\033[2J")
#define ANSI_DEFAULT()      printf("\033[0m")
#define ANSI_COLOR(f,b)     printf("\033[%d;%dm", (f) + 30, (b) + 40)
#define ANSI_FG_LCOLOR(f)   printf("\033[0;%dm", (f) + 30)
#define ANSI_FG_HCOLOR(f)   printf("\033[1;%dm", (f) + 30)


static int screenwidth, screenheight;

/*
    get the sizes of the screen
*/
static void emx_init()
{
    int size[2];

    _scrsize (size);
    screenwidth  = size[0];
    screenheight = size[1];
}

/*
    get a keyboard hit in the last line
*/
static int getkey()
{
    ANSI_DEFAULT();
    ANSI_FG_HCOLOR(WHITE);
    ANSI_GOTOXY(screenheight, 1);
    printf("Enter Key>");
    return getch();
}

int main(void)
{
    int z;

    emx_init();
    ANSI_CLEAR_SCREEN();

    for (z = 1; z <= screenheight - 1; ++z) {
       ANSI_GOTOXY(z, 1 + (z % 10));
       ANSI_FG_HCOLOR(z % 8);
       printf("<<<--- this is line %d", z);
    }

    getkey();
    ANSI_DEFAULT();
    ANSI_CLEAR_SCREEN();

    for (z = 0; z <= 7; ++z) {
       ANSI_GOTOXY(z + 10, z + 10);
       ANSI_COLOR(z, 7 - z);
       printf("++++++++ this is a test string ++++++++");
    }

    getkey();

    ANSI_COLOR(1, 3);
    ANSI_CLEAR_SCREEN();
    ANSI_GOTOXY(10, 10);
    printf("++++++++ this is a test string ++++++++");

    getkey();

    ANSI_DEFAULT();
    return 0;
}

