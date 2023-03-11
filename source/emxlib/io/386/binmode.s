/ binmode.s (emx+gcc) -- Copyright (c) 1992-1994 by Eberhard Mattes

        .text

L_setbinmode:
        movl    $1, __fmode_bin
        ret

        .section .ctor
        .long   _L_setbinmode
        .section .text
