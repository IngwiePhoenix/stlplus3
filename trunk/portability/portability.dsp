# Microsoft Developer Studio Project File - Name="portability" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=portability - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "portability.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "portability.mak" CFG="portability - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "portability - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "portability - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "portability - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "portability - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Od /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "portability - Win32 Release"
# Name "portability - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx"
# Begin Source File

SOURCE=.\build.hpp
# End Source File
# Begin Source File

SOURCE=.\debug.hpp
# End Source File
# Begin Source File

SOURCE=.\dprintf.hpp
# End Source File
# Begin Source File

SOURCE=.\dynaload.hpp
# End Source File
# Begin Source File

SOURCE=.\file_system.hpp
# End Source File
# Begin Source File

SOURCE=.\inf.hpp
# End Source File
# Begin Source File

SOURCE=.\portability.hpp
# End Source File
# Begin Source File

SOURCE=.\portability_exceptions.hpp
# End Source File
# Begin Source File

SOURCE=.\portability_fixes.hpp
# End Source File
# Begin Source File

SOURCE=.\subprocesses.hpp
# End Source File
# Begin Source File

SOURCE=.\tcp.hpp
# End Source File
# Begin Source File

SOURCE=.\time.hpp
# End Source File
# Begin Source File

SOURCE=.\version.hpp
# End Source File
# Begin Source File

SOURCE=.\wildcard.hpp
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp;cxx"
# Begin Source File

SOURCE=.\build.cpp
DEP_CPP_BUILD=\
	".\build.hpp"\
	".\dprintf.hpp"\
	".\portability_fixes.hpp"\
	".\version.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\debug.cpp
DEP_CPP_DEBUG=\
	".\debug.hpp"\
	".\dprintf.hpp"\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\dprintf.cpp
DEP_CPP_DPRIN=\
	".\dprintf.hpp"\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\dynaload.cpp
DEP_CPP_DYNAL=\
	".\dynaload.hpp"\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\file_system.cpp
DEP_CPP_FILE_=\
	".\file_system.hpp"\
	".\portability_fixes.hpp"\
	".\wildcard.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\inf.cpp
DEP_CPP_INF_C=\
	".\inf.hpp"\
	".\portability_exceptions.hpp"\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\portability_fixes.cpp
DEP_CPP_PORTA=\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\subprocesses.cpp
DEP_CPP_SUBPR=\
	".\dprintf.hpp"\
	".\file_system.hpp"\
	".\portability_fixes.hpp"\
	".\subprocesses.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\tcp.cpp
DEP_CPP_TCP_C=\
	".\dprintf.hpp"\
	".\portability_fixes.hpp"\
	".\tcp.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\time.cpp
DEP_CPP_TIME_=\
	".\dprintf.hpp"\
	".\portability_fixes.hpp"\
	".\time.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\version.cpp
DEP_CPP_VERSI=\
	".\portability_fixes.hpp"\
	".\version.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\wildcard.cpp
DEP_CPP_WILDC=\
	".\portability_fixes.hpp"\
	".\wildcard.hpp"\
	
# End Source File
# End Group
# End Target
# End Project
