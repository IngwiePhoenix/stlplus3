# Microsoft Developer Studio Project File - Name="digraph_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=digraph_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "digraph_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "digraph_test.mak" CFG="digraph_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "digraph_test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "digraph_test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "digraph_test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "..\..\strings" /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fr /c
# ADD CPP /nologo /MD /GR /GX /O2 /I "..\..\strings" /I "..\..\containers" /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /out:"digraph_test.exe"

!ELSEIF  "$(CFG)" == "digraph_test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Od /I "..\..\strings" /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fr /c
# ADD CPP /nologo /MDd /GR /GX /Od /I "..\..\strings" /I "..\..\containers" /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /out:"digraph_test.exe"
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "digraph_test - Win32 Release"
# Name "digraph_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp;cxx"
# Begin Source File

SOURCE=.\digraph_test.cpp
DEP_CPP_DIGRA=\
	"..\..\persistence\persistent.hpp"\
	"..\..\persistence\persistent_contexts.hpp"\
	"..\..\persistence\persistent_digraph.hpp"\
	"..\..\persistence\persistent_digraph.tpp"\
	"..\..\persistence\persistent_exceptions.hpp"\
	"..\..\persistence\persistent_int.hpp"\
	"..\..\persistence\persistent_shortcuts.hpp"\
	"..\..\persistence\persistent_shortcuts.tpp"\
	"..\..\persistence\persistent_string.hpp"\
	"..\..\persistence\persistent_string.tpp"\
	"..\..\persistence\persistent_vector.hpp"\
	"..\..\persistence\persistent_vector.tpp"\
	"..\..\persistence\persistent_xref.hpp"\
	"..\..\persistence\persistent_xref.tpp"\
	
NODEP_CPP_DIGRA=\
	"..\..\persistence\digraph.hpp"\
	".\digraph.hpp"\
	
# End Source File
# End Group
# End Target
# End Project