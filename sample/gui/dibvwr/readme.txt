README.TXT
==========

The DIB Viewer demo application is a Win 4.0 program for viewing DIBs.


Introduction
============

This archive contains an implementation of a DIB Viewer control in C. I'ts up
to the user (presumably a programmer) of this control to create a viewing
application (although DIBVWR.C is an example of how such an application would
look like). Because Windows uses DIBs rather heavily, I have used the DIB format
to display bitmaps. If you want a AGF (any graphics format) viewer, just make
sure you create functions that translate an AG to the Windows DIB/BMP format,
and pass the DIB to the DIB window.


Used compiler tools
===================

A main portion of the source code has been written with Borland C++ 4.02
and Symantec C++ 7.2. 

The file dibvwr.mk is intended for users of the RSXNTDJ-DJGPP combo. This
is a make script which should work with DOS make programs. Tested it
with the Borland C++ and Symantec C++ MAKErs only though. If you have the
standard RSXNTDJ package, the make file automatically includes headers
in the ./include directory. If you're working with the platform SDK headers,
you don't need the headers in the include directory.


DIBWIN.C, the dib window
========================

DIBWIN.C implements a DIB viewer control. Most of the time you're interfacing
with this module. DIBWIN is straightforward; only the set_dib_ptr does some
things the complicated way.

Unless told otherwise, the dib window destroys the bitmap data upon destruction.
If you don't want this, take a look at the Get/SetWindowDiBits functions.

To create a dib window you use the CreateWindowXXX API, its class name is
defined as DIB_VWR_CLASSNAME defined in DIBWIN.H. The DIBWIN.H header also
defines some styles that can be used in the CreateWindowXX call:

DWS_NOPALETTE - The dib window won't use palette data when drawing the DIB.
    DIBs that don't have palettes need to be handled in a special way when
    displayed in a screen modes with less color capabilities. Currently
    the dib window can only "quantize" to the 16 and 256 color system
    palettes (use the SetBitmapAndPalette function). DIBWIN.C is not
    capable of quantizing to colors in the bit map. Perhaps I'll write
    special functions for these kind of things in the future.

DWS_FITTOCLIENT - Fits the DIB to the client area of the dib window. See the
    preview window in the dib open dialog for a useful example. Should be used
    in combination with DWS_NOSCROLLBARS.

DWS_NOSCROLLBARS - Doesn't display scrollbars if the client area of the
    dib window is smaller than the bitmap to be displayed.

DWS_NOFASTERASE - By default the dib window by passes the WM_ERASEBACKGROUND
    and handles both paint and erase logic within the WM_PAINT handler.
    DIBWIN.C is quite a good demo of how to optimize the paint logic.

Here's how DIBVWR.C creates the the dib window:

	/* We want a DIB_VWR with all default styles on, so we don't
		specify any of the DWS_xxx styles */
	HWND	hwndChild = CreateWindowEx(0, DIB_VWR_CLASSNAME, DIB_VWR_CLASSNAME,
				WS_CHILD | WS_VISIBLE,
				0, 0, 0, 0, hwndDib, (HMENU)ID_DIB_VIEWER, _hInst, NULL);

Note that DIBVWR.EXE doesn't need one of the above styles. Try the following
combination of styles DWS_NOSCROLLBARS | DWS_FITTOCLIENT.


Inter-process sharing of DIBs
-----------------------------

There are several ways for processes to share data, e.g. DDE, and clipboard.
Under Win32 it's also possible to share memory data between processes. Upon
receipt of special messages the dib window creates a DIB in shared memory.
The dib window supplies a copy, not the actual DIB it holds, so changing
the shared DIB won't change the displayed DIB. However, the
dib window returns a read only handle, but with some effort it's possible
to write to the shared DIB. (DIBFUNC.C has several "lower level" functions
for dealing with shared DIBs.)

The dib window creates one shared DIB, which is shared by all processes
that requested a shared DIB. A request for a shared DIB just increments
a reference count; if a process doesn't need a shared DIB it should clean up
the data passed to it. Here the DIBWIN APIs for shared DIBs:

ATOM WindowSharedDIBAlloc(HWND hWndDib)
    Accesses DIB data of a dib window. The returned atom should be used
    immediately by calling high-level functions in DIBFUNC.C, like
    copy_shared_dib_atom_ptr (which creates a copy of the shared DIB) or
    access_shared_dib_atom (which returns the actual pointer to a read
    only DIB). If you want more control over the shared DIB, there are
    a bunch of other functions for accessing the shared dib. If the
    function returns 0, an error occurred somewhere. The returned
    atom should be freed by a call to WindowSharedDIBFree. Don't free
    the atom yourself by calling GlobalDeleteAtom.

BOOL WindowSharedDIBFree(HWND hWndDib, ATOM hAtom)
    This function should be called immediately after using the ATOM
    returned by WindowSharedDibFree.

If you want your application to share DIBs without using the dib window
you should really take a look at the other shared DIB functions of DIBFUNC.C.
It's a kinda neat implementation.


Setting and getting bitmaps and palettes
----------------------------------------

Within the same application you can set the displayed DIB by using another set
of WINDIB APIs. The DIB window accepts DIBs in two forms:

- handles. Under Win 16 DIBs were allocated from the global heap through
    functions that return handles to allocated data. Under Win32 you
    can use plain pointers to memory allocated through the more powerful
    heap allocation functions. If you don't want the dib window to be
    the owner of a passed handle, you should free the handle by calling
    GlobalFree yourself. This includes **copies** of handles returned by
    GetWindowDIBits with the flags SWD_HANDLE | SWD_COPY!

    Here's an example:

      // Get a handle copy of the DIB stored by the DIB Window
      hglbDib = (HGLOBAL)GetWindowDIBits(hWndDib, SWD_HANDLE | SWD_COPY);

      // Get a pointer to DIB data
      lpbmi = (LPBITMAPINFO)GlobalLock(hglbDib);

      // ... Do something with the DIB

      // Unlock data
      GlobalUnlock(hglbDib);

      // Free the copy by calling GlobalFree
      GlobalFree(hglbDib);

- pointers. Internally the dib window stores the displayed dib as a pointer
    to actual DIB data. The actual DIB data has been allocated through a
    call to a heap allocation function, from the current process.

    If you need a clean new DIB, use the dib_ptr_alloc function (see
    DIBFUNC.C). A dib_ptr_alloc'ed DIB should be freed with dib_ptr_free,
    unless you passed it to a DIB window and the DIB window should be
    the owner.

    If you have a requested a copy of a DIB (GetWindowDIBits with flag SWD_COPY),
    you need to free it with dib_ptr_free.

    Here's an example of how to use a returned *copy* of a DIB:

        lpbmi = (LPBITMAPINFO)GetWindowDIBits(hWndDib, SWD_COPY);

        /* Do something with the DIB */

        /* It's a copy, so we need to free this with HeapFree */
        dib_ptr_free(lpbmi);


The dib window automatically deallocates any associated memory objects: DIBs,
palettes, shared DIBs. If you don't want this, use the Set/GetWindowDIBits to
create copies of DIBs.

BOOL SetWindowDIBits(HWND hWndDib, LPVOID lpdib, UINT uFlags)
LPVOID GetWindowDIBits(HWND hWndDib, UINT uFlags)
    These two functions accept/return pointers or handles to DIBs. The flags
    parameters tell how the dib window should accept/return data.

    Although WINDIB.H defines different constants for both functions, you
    can use the SWD_XXX constants for the GetWindowDIBits function. At least,
    to some extent: some SWD_XXX constants are meaningful to the
    SetWindowDIBits function only. You can combine the constants by OR'ing
    them. Use SWD_COPY | SWD_HANDLE if you want the dib window to create a
    copy of a passed handle to SetWindowDIBits. Here the constants:

    SWD_HANDLE, GWD_HANDLE - The LPVOID parameter of SetWindowDIBits should
        contain a global handle (allocated with GlobalAlloc) to a DIB. If you
        GlobalLock a dib handle, you get a pointer to the DIB. GetWindowDIBits
        returns the handle to a dib. Mainly for use in DDE or with old Windows
        applications. If you don't specify this flag, the dib window expects/
        returns a pointer to a DIB allocated on the heap (through dib_alloc_ptr).

    SWD_COPY - Tells both functions to create a copy of bitmap data. In the
        case of SetWindowDIBits, the dib window creates a copy of the parameter
        passed through the LPVOID parameter (by default a pointer to a DIB).
        If used in GetWindowDIBits, the dib window creates a copy of the
        DIB it contains.

    SWD_REDRAW - Forces an update of the Window. Only meaningful with
        SetWindowDIBits.

    SWD_DONTDELETEPREV - If you set a DIB with this style OR-ed, the dib window
        won't delete/destroy the previous DIB. Get the previous DIB by calling
        GetWindowDIBits without the SWD_COPY or GWD_COPY flag specified!

Note: if the dib window has one, SetWindowDIBits also destroys the palette,
UNLESS you specified the SWD_DONTDELETE flag. If this flag is used the
palette won't get destroyed, too. If you use SWD_DONTDELETE, use it wisely.

Both functions accept 0 (zero) as a flag. In that case SetWindowDIBits requires
a DIB allocated with HeapAlloc; GetWindowDIBits returns the actual DIB used
by the dib window.

There are also functions that deal with setting and getting palettes:

BOOL SetWindowDIBPalette (HWND, HPALETTE, UINT);
HPALETTE GetWindowDIBPalette (HWND);
    Note that GetWindowDIBPalette does not accept flags. If you need to
    copy a palette, check out the copy_palette function in DIBFUNC.C.

    The flags for SetWindowDIBPalette are:

        SWDP_REDRAW - Forces a redraw of the dib window.
        SWDP_DONTDELETE - Doesn't delete the previous palette. Before you
            call SetWindowDIBPalette with this flag, make sure you know
            the handle of the previous palette!

Then there's a function for automatically setting a palette and a bitmap. It's
actually a simple wrapper around the previous function.

VOID SetBitmapAndPalette (HWND, LPBITMAPINFO, BOOL);
    The second parameter is the DIB. The Window will be the owner of the DIB;
    the DIB must be allocated through a call with HeapAlloc.


Translating other graphics formats
==================================

For translating other graphics formats to images viewable inside a DIB window
you need to keep these things in mind:

1. You need to translate the graphics to the DIB format.
2. Use the dib_ptr_alloc to create empty bitmaps. Although dib_ptr_alloc also
accepts BITMAPINFO structs with only a valid BITMAPINFOHEADER structure.
3. The DIBWIN.C module only quantizes colors to the system palette(s) if you
have images with more than 256 colors


Demo application
================

The demo application shows how to use DIBWIN.C within an application.


Legal statements
================

The author (Alfons Hoogervorst) nor any of the in this file mentioned persons
and/or companies can be held responsible/liable for damages resulting of
incorrect use/working of the described software. This software is provided
AS IS: you the user (presumeably a programmer) take all responsibility in
using the software/source code.

You're free to use the files for whatever purpose.

Trademarks statements
---------------------

In case I inadvertently mentioned a trademark without explicitly referring to
its holder: all implictly mentioned trademark phrases are explicit to
be mentioned trademarks of their implicitly mentioned but explicitly to
be mentioned explicit implicit holders.


Other notes
===========

Author
------

Alfons Hoogervorst works as free-lancer and has been programming Windows
for quite a long time. He specializes in low-level, custom control and
WinHelp programming. He can be contacted at proteus@worldaccess.nl,
alternatively try a.hoogervorst@inter.nl.net.
