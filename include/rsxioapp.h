/* rsxioapp.c - building windowed text-mode applications

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

#ifndef _RSXIOAPP_H_
#define _RSXIOAPP_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int      rsxio_window_close;
extern char     rsxio_window_title[];
extern int      rsxio_main(int argc, char **argv, char **env);

#ifdef __cplusplus
};
#endif
#endif
