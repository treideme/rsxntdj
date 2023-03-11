REM *** single thread ***
xcopy \emx\lib\st\c.a       \rsxntdj\lib\st\libc.a
xcopy \emx\lib\st\c_app.a   \rsxntdj\lib\st\libc_app.a
xcopy \emx\lib\st\c_dllrt.a \rsxntdj\lib\st\libdllrt.a
xcopy \emx\lib\st\emx.a     \rsxntdj\lib\st\libemx.a
xcopy \emx\lib\st\malloc1.a \rsxntdj\lib\st\libmal1.a

REM *** multi thread ***
xcopy \emx\lib\mt\c.a       \rsxntdj\lib\mt\libc.a
xcopy \emx\lib\mt\c_app.a   \rsxntdj\lib\mt\libc_app.a
xcopy \emx\lib\mt\c_dllrt.a \rsxntdj\lib\mt\libdllrt.a
xcopy \emx\lib\mt\emx.a     \rsxntdj\lib\mt\libemx.a
xcopy \emx\lib\mt\malloc1.a \rsxntdj\lib\mt\libmal1.a

REM *** others ***
xcopy \emx\lib\c_alias.a    \rsxntdj\lib\libalias.a
xcopy \emx\lib\c_static.a   \rsxntdj\lib\libstati.a
xcopy \emx\lib\emxio.a      \rsxntdj\lib\libemxio.a
xcopy \emx\lib\g.a          \rsxntdj\lib\libg.a
xcopy \emx\lib\gcc.a        \rsxntdj\lib\libgcc.a
xcopy \emx\lib\m.a          \rsxntdj\lib\libm.a
xcopy \emx\lib\moddef.a     \rsxntdj\lib\libmodde.a
xcopy \emx\lib\omflib.a     \rsxntdj\lib\libomf.a
xcopy \emx\lib\*.o          \rsxntdj\lib

