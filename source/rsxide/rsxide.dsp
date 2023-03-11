# Microsoft Developer Studio Project File - Name="rsxide" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=rsxide - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "Rsxide.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "Rsxide.mak" CFG="rsxide - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "rsxide - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386
# Begin Target

# Name "rsxide - Win32 Release"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=\Rsxide\Editdde.c
# End Source File
# Begin Source File

SOURCE=\Rsxide\Idedlg.c
# End Source File
# Begin Source File

SOURCE=\Rsxide\Rsxide.c
# End Source File
# Begin Source File

SOURCE=\Rsxide\Rsxide.rc
# End Source File
# Begin Source File

SOURCE=\Rsxide\Runw32.c
# End Source File
# Begin Source File

SOURCE=\Rsxide\Runw32s.c
# End Source File
# Begin Source File

SOURCE=\RSXIDE\tgtflags.c
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\editdde.h
# End Source File
# Begin Source File

SOURCE=..\IDDLG.H
# End Source File
# Begin Source File

SOURCE=..\idedlg.h
# End Source File
# Begin Source File

SOURCE=..\IDMENU.H
# End Source File
# Begin Source File

SOURCE=..\MASTER.H
# End Source File
# Begin Source File

SOURCE=..\rsxide.h
# End Source File
# Begin Source File

SOURCE=..\treeview.h
# End Source File
# Begin Source File

SOURCE=..\WINXX.H
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\BAR.BMP
# End Source File
# Begin Source File

SOURCE=..\RSXIDE.BMP
# End Source File
# Begin Source File

SOURCE=..\RSXIDE.DLG
# End Source File
# Begin Source File

SOURCE=..\rsxide.ico
# End Source File
# Begin Source File

SOURCE=..\rsxide1.ico
# End Source File
# Begin Source File

SOURCE=..\rsxidec.ico
# End Source File
# Begin Source File

SOURCE=..\rsxidet.ico
# End Source File
# Begin Source File

SOURCE=..\tvclose.bmp
# End Source File
# Begin Source File

SOURCE=..\tvitem.bmp
# End Source File
# Begin Source File

SOURCE=..\tvopen.bmp
# End Source File
# End Group
# End Target
# End Project
