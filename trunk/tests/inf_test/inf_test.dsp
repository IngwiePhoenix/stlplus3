# Microsoft Developer Studio Project File - Name="inf_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=inf_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "inf_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "inf_test.mak" CFG="inf_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "inf_test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "inf_test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF "$(CFG)" == "inf_test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GR /GX /MD /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /c
# ADD CPP /nologo /W3 /GR /GX /MD /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /c /I "..\..\containers" /I "..\..\portability" /I "..\..\subsystems" /I "..\..\persistence" /I "..\..\strings"
# ADD BASE RSC /l 0x809 /d "NDEBUG" 
# ADD RSC /l 0x809 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /incremental:no /subsystem:console /machine:I386
# ADD LINK32  "..\..\containers\Release\containers.lib" "..\..\portability\Release\portability.lib" "..\..\subsystems\Release\subsystems.lib" "..\..\persistence\Release\persistence.lib" "..\..\strings\Release\strings.lib" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /incremental:no /subsystem:console /machine:I386 /out:"inf_test.exe"

!ELSEIF "$(CFG)" == "inf_test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GR /GX /MDd /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /c
# ADD CPP /nologo /W3 /GR /GX /MDd /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /c /I "..\..\containers" /I "..\..\portability" /I "..\..\subsystems" /I "..\..\persistence" /I "..\..\strings"
# ADD BASE RSC /l 0x809 /d "_DEBUG" 
# ADD RSC /l 0x809 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /incremental:no /subsystem:console /machine:I386 /debug
# ADD LINK32  "..\..\containers\Debug\containers.lib" "..\..\portability\Debug\portability.lib" "..\..\subsystems\Debug\subsystems.lib" "..\..\persistence\Debug\persistence.lib" "..\..\strings\Debug\strings.lib" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /incremental:no /subsystem:console /machine:I386 /debug /out:"inf_test.exe"

!ENDIF 

# Begin Target

# Name "inf_test - Win32 Release"
# Name "inf_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp;cxx"
# Begin Source File

SOURCE=.\inf_test.cpp
# End Source File
# End Group
# End Target
# End Project
