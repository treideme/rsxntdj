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
 * File:
 *	run-includes/unchecked.h
 * Summary:
 *	Macros to allow per-pointer and per-use unchecked pointers.
 * Other notes:
 *	
 * Author      	Date		Notes
 * RWMJ		23/1/95		Initial implementation.
 * RWMJ         17/6/95         Added miscellaneous features.
 *----------------------------------------------------------------------*/

#ifndef _bounds_unchecked_h
#define _bounds_unchecked_h

#if defined(__GNUC__) && defined(__BOUNDS_CHECKING_ON)

/* Make pointer operations unchecked on each use.
*/
#define UNCHECKED_PTR_DIFF(p,q) ((ptrdiff_t)(((unsigned)(p))-((unsigned)(q))/sizeof (*p)))
#define UNCHECKED_PTR_PLUS_INT(p,i) ((typeof(p))((unsigned)(p))+(i)*(sizeof *p))
#define UNCHECKED_PTR_MINUS_INT(p,i) ((typeof(p))((unsigned)(p))-(i)*(sizeof *p))

/* How to switch checking off over a region of the program. You will need
 * 'DEBUG_FEATURES' set in the library. You do:
 *     ..
 *    BOUNDS_CHECKING_OFF;
 *     .. strange pointer operations here ..
 *    BOUNDS_CHECKING_ON;
 */
#define BOUNDS_CHECKING_OFF do {extern int __bounds_debug_no_checking; \
                                __bounds_debug_no_checking = 1;} while(0)
#define BOUNDS_CHECKING_ON  do {extern int __bounds_debug_no_checking; \
                                __bounds_debug_no_checking = 0;} while(0)

/* Switch bounds checking off in a single statement. You do:
 *    BOUNDS_CHECKING_OFF_DURING (stmt);
 * This works for most 'ordinary' statements, ie. not returns, or gotos, etc.
 * For expressions, use:
 *    BOUNDS_CHECKING_OFF_IN_EXPR (expr)
 */
#define BOUNDS_CHECKING_OFF_DURING(stmt) \
  do { extern int __bounds_debug_no_checking; \
       __bounds_debug_no_checking = 1; \
       stmt; \
       __bounds_debug_no_checking = 0; \
  } while (0)
#define BOUNDS_CHECKING_OFF_IN_EXPR(expr) \
  ({ extern int __bounds_debug_no_checking; \
     typeof(expr) __value; \
     __bounds_debug_no_checking = 1; \
     __value = (expr); \
     __bounds_debug_no_checking = 0; \
     __value; })

#else /* not __GNUC__ or not __BOUNDS_CHECKING_ON */

#define UNCHECKED_PTR_DIFF(p,q) ((p)-(q))
#define UNCHECKED_PTR_PLUS_INT(p,i) ((p)+(i))
#define UNCHECKED_PTR_MINUS_INT(p,i) ((p)-(i))

#define BOUNDS_CHECKING_OFF
#define BOUNDS_CHECKING_ON

#define BOUNDS_CHECKING_OFF_DURING(stmt) stmt
#define BOUNDS_CHECKING_OFF_IN_EXPR(expr) expr

#endif /* __GNUC__, __BOUNDS_CHECKING_ON */
#endif /* _bounds_unchecked_h */
