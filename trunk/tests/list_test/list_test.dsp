# Microsoft Developer Studio Project File - Name="list_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=list_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "list_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "list_test.mak" CFG="list_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "list_test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "list_test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "list_test - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fr /c
# ADD CPP /nologo /MD /GR /GX /O2 /I "..\..\containers" /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /out:"list_test.exe"

!ELSEIF  "$(CFG)" == "list_test - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /GR /GX /Od /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fr /c
# ADD CPP /nologo /MDd /GR /GX /Od /I "..\..\containers" /I "..\..\persistence" /I "..\..\portability" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /pdb:none /machine:I386 /out:"list_test.exe"
# SUBTRACT LINK32 /debug

!ENDIF 

# Begin Target

# Name "list_test - Win32 Release"
# Name "list_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c;cpp;cxx"
# Begin Source File

SOURCE=.\list_test.cpp
DEP_CPP_LIST_=\
	"..\..\containers\digraph.hpp"\
	"..\..\containers\digraph.tpp"\
	"..\..\containers\exceptions.hpp"\
	"..\..\containers\foursome.hpp"\
	"..\..\containers\foursome.tpp"\
	"..\..\containers\hash.hpp"\
	"..\..\containers\hash.tpp"\
	"..\..\containers\matrix.hpp"\
	"..\..\containers\matrix.tpp"\
	"..\..\containers\ntree.hpp"\
	"..\..\containers\ntree.tpp"\
	"..\..\containers\smart_ptr.hpp"\
	"..\..\containers\smart_ptr.tpp"\
	"..\..\containers\template_fixes.hpp"\
	"..\..\containers\triple.hpp"\
	"..\..\containers\triple.tpp"\
	"..\..\persistence\persistence.hpp"\
	"..\..\persistence\persistent.hpp"\
	"..\..\persistence\persistent_basic.hpp"\
	"..\..\persistence\persistent_bitset.hpp"\
	"..\..\persistence\persistent_bitset.tpp"\
	"..\..\persistence\persistent_bool.hpp"\
	"..\..\persistence\persistent_complex.hpp"\
	"..\..\persistence\persistent_complex.tpp"\
	"..\..\persistence\persistent_contexts.hpp"\
	"..\..\persistence\persistent_cstring.hpp"\
	"..\..\persistence\persistent_deque.hpp"\
	"..\..\persistence\persistent_deque.tpp"\
	"..\..\persistence\persistent_digraph.hpp"\
	"..\..\persistence\persistent_digraph.tpp"\
	"..\..\persistence\persistent_enum.hpp"\
	"..\..\persistence\persistent_enum.tpp"\
	"..\..\persistence\persistent_exceptions.hpp"\
	"..\..\persistence\persistent_float.hpp"\
	"..\..\persistence\persistent_foursome.hpp"\
	"..\..\persistence\persistent_foursome.tpp"\
	"..\..\persistence\persistent_hash.hpp"\
	"..\..\persistence\persistent_hash.tpp"\
	"..\..\persistence\persistent_int.hpp"\
	"..\..\persistence\persistent_interface.hpp"\
	"..\..\persistence\persistent_interface.tpp"\
	"..\..\persistence\persistent_list.hpp"\
	"..\..\persistence\persistent_list.tpp"\
	"..\..\persistence\persistent_map.hpp"\
	"..\..\persistence\persistent_map.tpp"\
	"..\..\persistence\persistent_matrix.hpp"\
	"..\..\persistence\persistent_matrix.tpp"\
	"..\..\persistence\persistent_multimap.hpp"\
	"..\..\persistence\persistent_multimap.tpp"\
	"..\..\persistence\persistent_multiset.hpp"\
	"..\..\persistence\persistent_multiset.tpp"\
	"..\..\persistence\persistent_ntree.hpp"\
	"..\..\persistence\persistent_ntree.tpp"\
	"..\..\persistence\persistent_pair.hpp"\
	"..\..\persistence\persistent_pair.tpp"\
	"..\..\persistence\persistent_pointer.hpp"\
	"..\..\persistence\persistent_pointer.tpp"\
	"..\..\persistence\persistent_pointers.hpp"\
	"..\..\persistence\persistent_polymorph.hpp"\
	"..\..\persistence\persistent_polymorph.tpp"\
	"..\..\persistence\persistent_set.hpp"\
	"..\..\persistence\persistent_set.tpp"\
	"..\..\persistence\persistent_shortcuts.hpp"\
	"..\..\persistence\persistent_shortcuts.tpp"\
	"..\..\persistence\persistent_smart_ptr.hpp"\
	"..\..\persistence\persistent_smart_ptr.tpp"\
	"..\..\persistence\persistent_stl.hpp"\
	"..\..\persistence\persistent_stlplus.hpp"\
	"..\..\persistence\persistent_string.hpp"\
	"..\..\persistence\persistent_string.tpp"\
	"..\..\persistence\persistent_triple.hpp"\
	"..\..\persistence\persistent_triple.tpp"\
	"..\..\persistence\persistent_vector.hpp"\
	"..\..\persistence\persistent_vector.tpp"\
	"..\..\persistence\persistent_xref.hpp"\
	"..\..\persistence\persistent_xref.tpp"\
	"..\..\portability\file_system.hpp"\
	"..\..\portability\os_fixes.hpp"\
	
# End Source File
# End Group
# End Target
# End Project
