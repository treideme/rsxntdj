RSXNTDJ 1.5.1
=============

Contents
--------

Section 1 - Important Information
	1.1 - What is RSXNTDJ?
	1.2 - Who wrote RSXNTDJ?
	1.3 - How did this version come about?

Section 2 - Installation
	2.1 - Quick Install

Section 3 - Contact Details
	3.1 - Johan Venter
	3.2 - Rainer Schnitker
	3.3 - DJGPP Information
	3.4 - Anders Norlander

Section 1 - Important Information
---------------------------------

1.1 - What is RSXNTDJ?
	RSXNTDJ is an add on to DJGPP allowing it to compile
both console and GUI Win32 programs. DJGPP is a free
32-bit development system for DOS made up mostly of DOS
ports of the famous GNU software. Included is ports for
GCC, the binutils, fileutils etc. If you've never heard 
of DJGPP before I strongly suggest you go to the homepage
(http://www.delorie.com/djgpp/) to find out more.

1.2 - Who wrote RSXNTDJ?
	Originally, a man called Rainer Schnitker wrote RSXNTDJ.
The last version he worked on was 1.5, which came out with 
a mass of problems for which I wrote a HOWTO 
(http://surf.to/rsxntdj). This version is meant as a patched
1.5 release, as it fixes many (if not all) of the problems
related to 1.5.

1.3 - How did this version come about?
	I wrote my RSXNTDJ 1.5 HOWTO during August and September of 99.
It ended up having quite a number of things that required doing
before you could get RSXNTDJ 1.5 to work correctly. It also
detailed the use of the Microsoft Platform SDK September 98 
WINAPI headers. Shortly after that, I decided that people shouldn't
have to download the whole MSSDK (about 10mb) just for the headers,
and they shouldn't have to follow so many instructions on getting
a single package to work. Thus this version, 1.5.1, is basically an
already patched version of 1.5 using Anders Norlander's WinAPI headers,
which are quickly becoming famous as the most up to date and clean set
of free WinAPI headers available.

Section 2 - Installation
------------------------

2.1 - Quick Install

NOTE: Make sure you have a working installation of DJGPP 2.02 or later
before attempting to install RSXNTDJ 1.5.1.

Installation of this version of RSXNTDJ is extremely easy, as it only
requires you to perform two steps.

What you need to do is add the following three lines to your autoexec.bat
file (usually in C:\):

	SET RSXNTDJ=C:\RSXNTDJ
	SET PATH=%RSXNTDJ%\bin;%PATH%
	SET C_INCLUDE_PATH=%RSXNTDJ%\include\win32\anders

NOTE: You may need to change the RSXNTDJ variable to suit your installation.

	I know some of you will probably be saying "Ha, this guy's a fool, why
should we have to add the last line". Well, grc (the resource compiler), often
needs to find WinAPI include files and that is the easiest way to do it.

	If you use Windows 98 your computer might use a different autoexec.bat
to the one found in C:\. To make sure you get the right one, click on 
Start-Programs-Accessories-System Tools-System Information. Once it's loaded,
click on Tools-System Configuration Utility and then click the autoexec.bat
tab. Add the lines there.

	The last thing you need to do is COPY your cpp.exe from your DJGPP
installation into your DJGPP/bin directory. It is located in your
DJGPP/lib/gcc-lib/djgpp/2.95 directory (or similar, depending on your
gcc version).

Section 3 - Contact Details
---------------------------

3.1 -
	I, (Johan Venter), can be reached at jventer@writeme.com

3.2 - 
	Rainer Schnitker can be reached at rainer@mathematik.uni-bielefeld.de

3.3 -
	The DJGPP homepage is at http://www.delorie.com/djgpp/

3.4 - 
	Anders Norlander's WinAPI headers can be found at 
	http://www.acc.umu.se/~anorland/gnu-win32/ 


Johan Venter
jventer@writeme.com

Original Date: September 22nd 1999
Latest Update: October 19th 1999
