@ECHO OFF
IF off == %1 GOTO DJGPPOFF

SET PATH=%PATH%;C:\EMX\BIN;F:\EMXWIN32\BIN;F:\RSXNTDJ\BIN
SET TMPDIR=C:/TEMP
SET COMPILER_PATH=C:/EMX/BIN
SET C_INCLUDE_PATH=C:/EMX/INCLUDE;C:/EMX/INCLUDE/WIN32
SET LIBRARY_PATH=C:/EMX/LIB
GOTO END
:DJGPPOFF
SET TMPDIR=
SET COMPILER_PATH=
SET C_INCLUDE_PATH=
SET LIBRARY_PATH=
:END
