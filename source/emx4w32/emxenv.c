/* emxenv.c - define emx vars for -Znorte

   Copyright (c) 1995-1999 Rainer Schnitker

   This file is part of RSXNT.

   RSXNT is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   RSXNT is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with RSXNT; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA. */

#define RUN_387         0x0020L
#define RUN_486         0x0040L
#define RUN_RSX         0x1000L

#define RSXNT_VERSION   (0x00020000 | 0x0131)

unsigned int _emx_vcmp = 0x302e3963;  /* 0.9C */
unsigned int _emx_rev = RSXNT_VERSION;
unsigned int _emx_env = RUN_RSX | RUN_387;

