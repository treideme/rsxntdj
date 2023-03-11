/*----------------------------------------------------------------------*
 * Bounds Checking for GCC.						*
 * Copyright (C) 1995 Richard W.M. Jones <rwmj@doc.ic.ac.uk>.		*
 *----------------------------------------------------------------------*
 * This program is free software; you can redistribute it and/or modify	*
 * it under the terms of the GNU General Public License as published by	*
 * the Free Software Foundation; either version 2 of the License, or	*
 * (at your option) any later version.					*
 *									*
 * This program is distributed in the hope that it will be useful,	*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	*
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	*
 * GNU General Public License for more details.				*
 *									*
 * You should have received a copy of the GNU General Public License	*
 * along with this program; if not, write to the Free Software		*
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.		*
 *----------------------------------------------------------------------*
 * Modified for emx by Eberhard Mattes, Jun 1998			*
 *----------------------------------------------------------------------*/

#ifndef _FIX_ARGS_H_
#define _FIX_ARGS_H_

#ifdef __BOUNDS_CHECKING_ON

extern int __bounds_debug_no_checking;

#define va_arg(AP,TYPE) \
  ({int __t = __bounds_debug_no_checking; \
  TYPE __r; \
  __bounds_debug_no_checking = 1; \
  __r = __std_va_arg(AP,TYPE); \
  __bounds_debug_no_checking = __t; \
  __r;})

#endif /* __BOUNDS_CHECKING_ON */
#endif /* _FIX_ARGS_H_ */
