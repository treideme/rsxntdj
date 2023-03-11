/* wm_demo.c (emx+gcc) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/winmgr.h>

#define FALSE 0
#define TRUE  1

static wm_handle w1;
static wm_handle w2;
static wm_handle w3;
static int bw;


static void demo_1 (void)
{
  int i, x, y;

  x = 0; y = 0;
  w1 = wm_create (x, y, x+22, y+2, 2,
                  bw ? BW_NORMAL : F_RED|B_BLACK,
                  bw ? BW_NORMAL : F_GREEN|B_BLACK);
  if (w1 != NULL)
    {
      wm_puts_at (w1, 2, 1, "Window manager demo");
      wm_open (w1);
      for (i = 0; i < 10; ++i)
        {
          _sleep2 (60);
          x += 2; y += 1;
          wm_move (w1, x, y);
        }
      sleep (2);
    }
}


static void demo_2 (void)
{
  int i, j, x, y, sd[2];
  int a1, a2, a3, a4;
  char *title = " A Window Title! ";
  char tmp[100];
  char *backgnd = "B a c k g r o u n d - ";

  x = 8; y = 1;
  if (bw)
    {
      a1 = BW_NORMAL;
      a2 = BW_REVERSE;
      a3 = BW_NORMAL|INTENSITY;
      a4 = BW_REVERSE;
    }
  else 
    {
      a1 = F_WHITE|INTENSITY|B_BLUE;
      a2 = F_YELLOW|INTENSITY|B_RED;
      a3 = F_RED|INTENSITY|B_BLUE;
      a4 = F_WHITE|INTENSITY|B_GREEN;
    }
  w2 = wm_create (x, y, x+25, y+9, 1, a1, a1);
  if (w2 != NULL)
    {
      wm_down (w2);
      wm_open (w2);
      for (i = 0; i < 22; ++i)
        {
          _sleep2 (100);
          if (i < 11)
            x += 2;
          else
            y += 1;
          wm_move (w2, x, y);
          wm_gotoxy (w1, 9, 0);
          wm_printf (w1, "(%d,%d)", x, y);
          wm_gotoxy (w2, 0, 0);
          wm_printf (w2, "(%d,%d)", x, y);
        }
      wm_clr_eol (w1, 9, 0);
      for (i = 1; i <= 200; ++i)
        wm_printf (w2, "Window manager demo %-4d ", i);
      for (i = 0; i < 8; ++i)
        {
          wm_attrib_all (w2, a2);
          _sleep2 (150);
          wm_attrib_all (w2, a1);
          _sleep2 (150);
          if (i == 4)
            wm_top (w2);
        }
      j = strlen (title);
      for (i = 0; i <= j; ++i)
        {
          memcpy (tmp, title, i);
          tmp[i] = 0;
          wm_border (w2, 1, a1, tmp, 1, a3);
          _sleep2 (80);
        }
      wm_clear (w2);
      wm_gotoxy (w2, 4, 1); wm_puts (w2, "Title with");
      wm_getxy (w2, &x, &y);
      wm_gotoxy (w2, 4, 2); wm_puts (w2, "vertical bars\n");
      sleep (2);
      wm_border (w2, 1, a1, title, 0, a3);
      wm_attrib (w2, a2);
      wm_puts_at (w2, x, y, "out");
      wm_attrib (w2, a1);
      sleep (2);
      _scrsize (sd);
      x = sd[0]; y = sd[1];
      w3 = wm_create (0, 0, x-1, y-1, 0, 0, a4);
      if (w3 != NULL)
        {
          wm_bottom (w3);
          for (i = 0; i < (x*y)/strlen (backgnd); ++i)
            wm_puts (w3, backgnd);
          wm_putc (w3, ' ');
          wm_open (w3);
          sleep (1);
          wm_attrib (w3, BW_NORMAL);
          wm_clear (w3);
          sleep (1);
          wm_close (w3);
          sleep (1);
        }
    }
}


int main (int argc, char *argv[])
{
  int i;

  bw = FALSE;
  for (i = 1; i < argc; ++i)
    if (strcmp (argv[i], "-b") == 0)
      bw = TRUE;
    else
      {
        fprintf (stderr, "Usage: wm_demo [-b]\n");
        return 1;
      }
  if (!wm_init (20))
    {
      fprintf (stderr, "wm_demo: wm_init() failed\n");
      return 1;
    }
  demo_1 ();
  demo_2 ();
  wm_close_all ();
  wm_exit ();
  return 0;
}
