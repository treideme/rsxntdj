/* conio.h (emx+gcc) */

#ifndef _CONIO_H
#define _CONIO_H

#define getch()   _read_kbd (0, 1, 0)
#define getche()  _read_kbd (1, 1, 0)

#endif /* not _CONIO_H */
