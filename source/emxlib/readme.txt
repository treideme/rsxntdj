To build emx libraries

1) unpack emxsrcd2.zip (builds \emx\src\lib source)
2) copy this files to \emx\src\lib  (xcopy /s *.* \emx\src\lib)
3) set c_include_path to \rsxntdj\include
4) set library_path to \rsxntdj\lib
5) use win32 gcc binaries (emx style of gcc.exe,cpp.exe,cc1.exe)
6) copy startup.mk to \etc
7) run dmake
8) run copydj.bat

