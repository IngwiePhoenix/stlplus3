# Microsoft Developer Studio Project File - Name="strings" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=strings - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "strings.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "strings.mak" CFG="strings - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "strings - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "strings - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "strings - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "..\portability" /I "..\containers" /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /Fr /c
# ADD CPP /nologo /MD /GR /GX /O2  /I "..\portability" /I "..\containers" /D "WIN32" /D "NDEBUG" /D "_LIB" /D "_MBCS" /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "strings - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Od  /I "..\portability" /I "..\containers" /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /Fr /c
# ADD CPP /nologo /MDd /GR /GX /Od  /I "..\portability" /I "..\containers" /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_MBCS" /c
# SUBTRACT CPP /Fr
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

# Name "strings - Win32 Release"
# Name "strings - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx"
# Begin Source File

SOURCE=.\format_types.hpp
# End Source File
# Begin Source File

SOURCE=.\strings.hpp
# End Source File
# Begin Source File

SOURCE=.\string_basic.hpp
# End Source File
# Begin Source File

SOURCE=.\string_stl.hpp
# End Source File
# Begin Source File

SOURCE=.\string_utilities.hpp
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp;cxx"
# Begin Source File

SOURCE=.\string_basic.cpp
DEP_CPP_STRIN=\
	".\format_types.hpp"\
	".\string_basic.hpp"\
	
NODEP_CPP_STRIN=\
	".\dprintf.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_stl.cpp
DEP_CPP_STRING=\
	".\format_types.hpp"\
	".\string_stl.hpp"\
	".\string_stl.tpp"\
	
NODEP_CPP_STRING=\
	".\template_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_utilities.cpp
DEP_CPP_STRINGS=\
	".\format_types.hpp"\
	".\string_basic.hpp"\
	".\string_utilities.hpp"\
	
NODEP_CPP_STRINGS=\
	".\dprintf.hpp"\
	
# End Source File
# End Group
# Begin Group "Template Implementations"

# PROP Default_Filter ".tpp"
# Begin Source File

SOURCE=.\string_stl.tpp
# End Source File
# End Group
# End Target
# End Project
