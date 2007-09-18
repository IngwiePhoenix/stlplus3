# Microsoft Developer Studio Project File - Name="smart_ptr_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=smart_ptr_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "smart_ptr_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "smart_ptr_test.mak" CFG="smart_ptr_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "smart_ptr_test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "smart_ptr_test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "smart_ptr_test - Win32 Release"

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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /out:"smart_ptr_test.exe"

!ELSEIF  "$(CFG)" == "smart_ptr_test - Win32 Debug"

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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /out:"smart_ptr_test.exe"
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "smart_ptr_test - Win32 Release"
# Name "smart_ptr_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp;cxx"
# Begin Source File

SOURCE=.\smart_ptr_test.cpp
DEP_CPP_SMART=\
	"..\..\containers\exceptions.hpp"\
	"..\..\containers\smart_ptr.hpp"\
	"..\..\containers\smart_ptr.tpp"\
	"..\..\containers\template_fixes.hpp"\
	"..\..\persistence\persistent.hpp"\
	"..\..\persistence\persistent_contexts.hpp"\
	"..\..\persistence\persistent_exceptions.hpp"\
	"..\..\persistence\persistent_int.hpp"\
	"..\..\persistence\persistent_interface.hpp"\
	"..\..\persistence\persistent_interface.tpp"\
	"..\..\persistence\persistent_pair.hpp"\
	"..\..\persistence\persistent_pair.tpp"\
	"..\..\persistence\persistent_pointer.hpp"\
	"..\..\persistence\persistent_pointer.tpp"\
	"..\..\persistence\persistent_polymorph.hpp"\
	"..\..\persistence\persistent_polymorph.tpp"\
	"..\..\persistence\persistent_shortcuts.hpp"\
	"..\..\persistence\persistent_shortcuts.tpp"\
	"..\..\persistence\persistent_smart_ptr.hpp"\
	"..\..\persistence\persistent_smart_ptr.tpp"\
	"..\..\persistence\persistent_string.hpp"\
	"..\..\persistence\persistent_string.tpp"\
	
# End Source File
# End Group
# End Target
# End Project