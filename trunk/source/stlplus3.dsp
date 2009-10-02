# Microsoft Developer Studio Project File - Name="stlplus3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=stlplus3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "stlplus3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "stlplus3.mak" CFG="stlplus3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "stlplus3 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "stlplus3 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "stlplus3 - Win32 Release"

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

!ELSEIF  "$(CFG)" == "stlplus3 - Win32 Debug"

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

# Name "stlplus3 - Win32 Release"
# Name "stlplus3 - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx"
# Begin Source File

SOURCE=.\build.hpp
# End Source File
# Begin Source File

SOURCE=.\cli_parser.hpp
# End Source File
# Begin Source File

SOURCE=.\containers.hpp
# End Source File
# Begin Source File

SOURCE=.\containers_fixes.hpp
# End Source File
# Begin Source File

SOURCE=.\copy_functors.hpp
# End Source File
# Begin Source File

SOURCE=.\debug.hpp
# End Source File
# Begin Source File

SOURCE=.\digraph.hpp
# End Source File
# Begin Source File

SOURCE=.\dprintf.hpp
# End Source File
# Begin Source File

SOURCE=.\dynaload.hpp
# End Source File
# Begin Source File

SOURCE=.\exceptions.hpp
# End Source File
# Begin Source File

SOURCE=.\file_system.hpp
# End Source File
# Begin Source File

SOURCE=.\format_types.hpp
# End Source File
# Begin Source File

SOURCE=.\foursome.hpp
# End Source File
# Begin Source File

SOURCE=.\hash.hpp
# End Source File
# Begin Source File

SOURCE=.\inf.hpp
# End Source File
# Begin Source File

SOURCE=.\ini_manager.hpp
# End Source File
# Begin Source File

SOURCE=.\ip_sockets.hpp
# End Source File
# Begin Source File

SOURCE=.\library_manager.hpp
# End Source File
# Begin Source File

SOURCE=.\matrix.hpp
# End Source File
# Begin Source File

SOURCE=.\message_handler.hpp
# End Source File
# Begin Source File

SOURCE=.\ntree.hpp
# End Source File
# Begin Source File

SOURCE=.\persistence.hpp
# End Source File
# Begin Source File

SOURCE=.\persistence_fixes.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_basic.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_bitset.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_bool.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_callback.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_complex.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_contexts.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_cstring.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_deque.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_digraph.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_enum.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_exceptions.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_float.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_foursome.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_hash.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_inf.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_int.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_interface.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_list.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_map.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_matrix.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_multimap.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_multiset.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_ntree.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_pair.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_pointer.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_pointers.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_set.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_shortcuts.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_simple_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_smart_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_stl.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_stlplus.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_string.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_triple.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_vector.hpp
# End Source File
# Begin Source File

SOURCE=.\persistent_xref.hpp
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

SOURCE=.\print_address.hpp
# End Source File
# Begin Source File

SOURCE=.\print_basic.hpp
# End Source File
# Begin Source File

SOURCE=.\print_bitset.hpp
# End Source File
# Begin Source File

SOURCE=.\print_bool.hpp
# End Source File
# Begin Source File

SOURCE=.\print_cstring.hpp
# End Source File
# Begin Source File

SOURCE=.\print_digraph.hpp
# End Source File
# Begin Source File

SOURCE=.\print_float.hpp
# End Source File
# Begin Source File

SOURCE=.\print_foursome.hpp
# End Source File
# Begin Source File

SOURCE=.\print_hash.hpp
# End Source File
# Begin Source File

SOURCE=.\print_inf.hpp
# End Source File
# Begin Source File

SOURCE=.\print_int.hpp
# End Source File
# Begin Source File

SOURCE=.\print_list.hpp
# End Source File
# Begin Source File

SOURCE=.\print_map.hpp
# End Source File
# Begin Source File

SOURCE=.\print_matrix.hpp
# End Source File
# Begin Source File

SOURCE=.\print_ntree.hpp
# End Source File
# Begin Source File

SOURCE=.\print_pair.hpp
# End Source File
# Begin Source File

SOURCE=.\print_pointer.hpp
# End Source File
# Begin Source File

SOURCE=.\print_sequence.hpp
# End Source File
# Begin Source File

SOURCE=.\print_set.hpp
# End Source File
# Begin Source File

SOURCE=.\print_simple_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\print_smart_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\print_stl.hpp
# End Source File
# Begin Source File

SOURCE=.\print_stlplus.hpp
# End Source File
# Begin Source File

SOURCE=.\print_string.hpp
# End Source File
# Begin Source File

SOURCE=.\print_triple.hpp
# End Source File
# Begin Source File

SOURCE=.\print_vector.hpp
# End Source File
# Begin Source File

SOURCE=.\safe_iterator.hpp
# End Source File
# Begin Source File

SOURCE=.\simple_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\smart_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\stlplus3.hpp
# End Source File
# Begin Source File

SOURCE=.\string_address.hpp
# End Source File
# Begin Source File

SOURCE=.\string_basic.hpp
# End Source File
# Begin Source File

SOURCE=.\string_bitset.hpp
# End Source File
# Begin Source File

SOURCE=.\string_bool.hpp
# End Source File
# Begin Source File

SOURCE=.\string_cstring.hpp
# End Source File
# Begin Source File

SOURCE=.\string_digraph.hpp
# End Source File
# Begin Source File

SOURCE=.\string_float.hpp
# End Source File
# Begin Source File

SOURCE=.\string_foursome.hpp
# End Source File
# Begin Source File

SOURCE=.\string_hash.hpp
# End Source File
# Begin Source File

SOURCE=.\string_inf.hpp
# End Source File
# Begin Source File

SOURCE=.\string_int.hpp
# End Source File
# Begin Source File

SOURCE=.\string_list.hpp
# End Source File
# Begin Source File

SOURCE=.\string_map.hpp
# End Source File
# Begin Source File

SOURCE=.\string_matrix.hpp
# End Source File
# Begin Source File

SOURCE=.\string_ntree.hpp
# End Source File
# Begin Source File

SOURCE=.\string_pair.hpp
# End Source File
# Begin Source File

SOURCE=.\string_pointer.hpp
# End Source File
# Begin Source File

SOURCE=.\string_sequence.hpp
# End Source File
# Begin Source File

SOURCE=.\string_set.hpp
# End Source File
# Begin Source File

SOURCE=.\string_simple_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\string_smart_ptr.hpp
# End Source File
# Begin Source File

SOURCE=.\string_stl.hpp
# End Source File
# Begin Source File

SOURCE=.\string_stlplus.hpp
# End Source File
# Begin Source File

SOURCE=.\string_string.hpp
# End Source File
# Begin Source File

SOURCE=.\string_triple.hpp
# End Source File
# Begin Source File

SOURCE=.\string_utilities.hpp
# End Source File
# Begin Source File

SOURCE=.\string_vector.hpp
# End Source File
# Begin Source File

SOURCE=.\strings.hpp
# End Source File
# Begin Source File

SOURCE=.\strings_fixes.hpp
# End Source File
# Begin Source File

SOURCE=.\subprocesses.hpp
# End Source File
# Begin Source File

SOURCE=.\subsystems.hpp
# End Source File
# Begin Source File

SOURCE=.\subsystems_fixes.hpp
# End Source File
# Begin Source File

SOURCE=.\tcp.hpp
# End Source File
# Begin Source File

SOURCE=.\tcp_sockets.hpp
# End Source File
# Begin Source File

SOURCE=.\time.hpp
# End Source File
# Begin Source File

SOURCE=.\timer.hpp
# End Source File
# Begin Source File

SOURCE=.\triple.hpp
# End Source File
# Begin Source File

SOURCE=.\udp_sockets.hpp
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

SOURCE=.\cli_parser.cpp
DEP_CPP_CLI_P=\
	".\cli_parser.hpp"\
	".\containers_fixes.hpp"\
	".\copy_functors.hpp"\
	".\dprintf.hpp"\
	".\exceptions.hpp"\
	".\file_system.hpp"\
	".\ini_manager.hpp"\
	".\message_handler.hpp"\
	".\portability_fixes.hpp"\
	".\smart_ptr.hpp"\
	".\smart_ptr.tpp"\
	".\subsystems_fixes.hpp"\
	
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

SOURCE=.\ini_manager.cpp
DEP_CPP_INI_M=\
	".\file_system.hpp"\
	".\ini_manager.hpp"\
	".\portability_fixes.hpp"\
	".\subsystems_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\ip_sockets.cpp
DEP_CPP_IP_SO=\
	".\dprintf.hpp"\
	".\ip_sockets.hpp"\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\library_manager.cpp
DEP_CPP_LIBRA=\
	".\containers_fixes.hpp"\
	".\copy_functors.hpp"\
	".\exceptions.hpp"\
	".\file_system.hpp"\
	".\ini_manager.hpp"\
	".\library_manager.hpp"\
	".\portability_fixes.hpp"\
	".\smart_ptr.hpp"\
	".\smart_ptr.tpp"\
	".\subsystems_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\message_handler.cpp
DEP_CPP_MESSA=\
	".\containers_fixes.hpp"\
	".\copy_functors.hpp"\
	".\dprintf.hpp"\
	".\exceptions.hpp"\
	".\message_handler.hpp"\
	".\portability_fixes.hpp"\
	".\smart_ptr.hpp"\
	".\smart_ptr.tpp"\
	".\subsystems_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_bool.cpp
DEP_CPP_PERSI=\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_bool.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_exceptions.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_contexts.cpp
DEP_CPP_PERSIS=\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_exceptions.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_cstring.cpp
DEP_CPP_PERSIST=\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_cstring.hpp"\
	".\persistent_exceptions.hpp"\
	".\persistent_int.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_exceptions.cpp
DEP_CPP_PERSISTE=\
	".\persistence_fixes.hpp"\
	".\persistent_exceptions.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_float.cpp
DEP_CPP_PERSISTEN=\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_exceptions.hpp"\
	".\persistent_float.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_inf.cpp
DEP_CPP_PERSISTENT=\
	".\inf.hpp"\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_exceptions.hpp"\
	".\persistent_inf.hpp"\
	".\persistent_int.hpp"\
	".\persistent_string.hpp"\
	".\persistent_string.tpp"\
	".\portability_exceptions.hpp"\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_int.cpp
DEP_CPP_PERSISTENT_=\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_exceptions.hpp"\
	".\persistent_int.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_string.cpp
DEP_CPP_PERSISTENT_S=\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_exceptions.hpp"\
	".\persistent_int.hpp"\
	".\persistent_string.hpp"\
	".\persistent_string.tpp"\
	
# End Source File
# Begin Source File

SOURCE=.\persistent_vector.cpp
DEP_CPP_PERSISTENT_V=\
	".\persistence_fixes.hpp"\
	".\persistent.hpp"\
	".\persistent_contexts.hpp"\
	".\persistent_exceptions.hpp"\
	".\persistent_int.hpp"\
	".\persistent_vector.hpp"\
	".\persistent_vector.tpp"\
	
# End Source File
# Begin Source File

SOURCE=.\portability_fixes.cpp
DEP_CPP_PORTA=\
	".\portability_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_address.cpp
DEP_CPP_PRINT=\
	".\format_types.hpp"\
	".\print_address.hpp"\
	".\print_int.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_bool.cpp
DEP_CPP_PRINT_=\
	".\format_types.hpp"\
	".\print_bool.hpp"\
	".\print_int.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_cstring.cpp
DEP_CPP_PRINT_C=\
	".\print_cstring.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_float.cpp
DEP_CPP_PRINT_F=\
	".\format_types.hpp"\
	".\print_float.hpp"\
	".\string_float.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_inf.cpp
DEP_CPP_PRINT_I=\
	".\format_types.hpp"\
	".\inf.hpp"\
	".\portability_exceptions.hpp"\
	".\portability_fixes.hpp"\
	".\print_inf.hpp"\
	".\string_inf.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_int.cpp
DEP_CPP_PRINT_IN=\
	".\format_types.hpp"\
	".\print_int.hpp"\
	".\string_int.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_string.cpp
DEP_CPP_PRINT_S=\
	".\print_string.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\print_vector.cpp
DEP_CPP_PRINT_V=\
	".\print_pair.hpp"\
	".\print_pair.tpp"\
	".\print_sequence.hpp"\
	".\print_sequence.tpp"\
	".\print_vector.hpp"\
	".\print_vector.tpp"\
	".\string_pair.hpp"\
	".\string_pair.tpp"\
	".\string_sequence.hpp"\
	".\string_sequence.tpp"\
	".\string_vector.hpp"\
	".\string_vector.tpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_address.cpp
DEP_CPP_STRIN=\
	".\format_types.hpp"\
	".\string_address.hpp"\
	".\string_int.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_bool.cpp
DEP_CPP_STRING=\
	".\format_types.hpp"\
	".\string_bool.hpp"\
	".\string_int.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_cstring.cpp
DEP_CPP_STRING_=\
	".\string_cstring.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_float.cpp
DEP_CPP_STRING_F=\
	".\format_types.hpp"\
	".\string_float.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_inf.cpp
DEP_CPP_STRING_I=\
	".\format_types.hpp"\
	".\inf.hpp"\
	".\portability_exceptions.hpp"\
	".\portability_fixes.hpp"\
	".\string_address.hpp"\
	".\string_basic.hpp"\
	".\string_bool.hpp"\
	".\string_cstring.hpp"\
	".\string_float.hpp"\
	".\string_inf.hpp"\
	".\string_int.hpp"\
	".\string_pointer.hpp"\
	".\string_pointer.tpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_int.cpp
DEP_CPP_STRING_IN=\
	".\format_types.hpp"\
	".\string_int.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_string.cpp
DEP_CPP_STRING_S=\
	".\string_string.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_utilities.cpp
DEP_CPP_STRING_U=\
	".\format_types.hpp"\
	".\string_address.hpp"\
	".\string_basic.hpp"\
	".\string_bool.hpp"\
	".\string_cstring.hpp"\
	".\string_float.hpp"\
	".\string_int.hpp"\
	".\string_pointer.hpp"\
	".\string_pointer.tpp"\
	".\string_utilities.hpp"\
	".\strings_fixes.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\string_vector.cpp
DEP_CPP_STRING_V=\
	".\string_pair.hpp"\
	".\string_pair.tpp"\
	".\string_sequence.hpp"\
	".\string_sequence.tpp"\
	".\string_vector.hpp"\
	".\string_vector.tpp"\
	".\strings_fixes.hpp"\
	
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

SOURCE=.\tcp_sockets.cpp
DEP_CPP_TCP_S=\
	".\ip_sockets.hpp"\
	".\portability_fixes.hpp"\
	".\tcp_sockets.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\time.cpp
DEP_CPP_TIME_=\
	".\dprintf.hpp"\
	".\portability_fixes.hpp"\
	".\time.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\timer.cpp
DEP_CPP_TIMER=\
	".\dprintf.hpp"\
	".\portability_fixes.hpp"\
	".\subsystems_fixes.hpp"\
	".\time.hpp"\
	".\timer.hpp"\
	
# End Source File
# Begin Source File

SOURCE=.\udp_sockets.cpp
DEP_CPP_UDP_S=\
	".\ip_sockets.hpp"\
	".\portability_fixes.hpp"\
	".\udp_sockets.hpp"\
	
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
# Begin Group "Template Implementations"

# PROP Default_Filter "tpp;txx"
# Begin Source File

SOURCE=.\digraph.tpp
# End Source File
# Begin Source File

SOURCE=.\foursome.tpp
# End Source File
# Begin Source File

SOURCE=.\hash.tpp
# End Source File
# Begin Source File

SOURCE=.\matrix.tpp
# End Source File
# Begin Source File

SOURCE=.\ntree.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_bitset.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_callback.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_complex.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_deque.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_digraph.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_enum.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_foursome.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_hash.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_interface.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_list.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_map.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_matrix.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_multimap.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_multiset.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_ntree.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_pair.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_pointer.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_set.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_shortcuts.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_simple_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_smart_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_string.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_triple.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_vector.tpp
# End Source File
# Begin Source File

SOURCE=.\persistent_xref.tpp
# End Source File
# Begin Source File

SOURCE=.\print_bitset.tpp
# End Source File
# Begin Source File

SOURCE=.\print_digraph.tpp
# End Source File
# Begin Source File

SOURCE=.\print_foursome.tpp
# End Source File
# Begin Source File

SOURCE=.\print_hash.tpp
# End Source File
# Begin Source File

SOURCE=.\print_list.tpp
# End Source File
# Begin Source File

SOURCE=.\print_map.tpp
# End Source File
# Begin Source File

SOURCE=.\print_matrix.tpp
# End Source File
# Begin Source File

SOURCE=.\print_ntree.tpp
# End Source File
# Begin Source File

SOURCE=.\print_pair.tpp
# End Source File
# Begin Source File

SOURCE=.\print_pointer.tpp
# End Source File
# Begin Source File

SOURCE=.\print_sequence.tpp
# End Source File
# Begin Source File

SOURCE=.\print_set.tpp
# End Source File
# Begin Source File

SOURCE=.\print_simple_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\print_smart_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\print_triple.tpp
# End Source File
# Begin Source File

SOURCE=.\print_vector.tpp
# End Source File
# Begin Source File

SOURCE=.\safe_iterator.tpp
# End Source File
# Begin Source File

SOURCE=.\simple_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\smart_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\string_bitset.tpp
# End Source File
# Begin Source File

SOURCE=.\string_digraph.tpp
# End Source File
# Begin Source File

SOURCE=.\string_foursome.tpp
# End Source File
# Begin Source File

SOURCE=.\string_hash.tpp
# End Source File
# Begin Source File

SOURCE=.\string_list.tpp
# End Source File
# Begin Source File

SOURCE=.\string_map.tpp
# End Source File
# Begin Source File

SOURCE=.\string_matrix.tpp
# End Source File
# Begin Source File

SOURCE=.\string_ntree.tpp
# End Source File
# Begin Source File

SOURCE=.\string_pair.tpp
# End Source File
# Begin Source File

SOURCE=.\string_pointer.tpp
# End Source File
# Begin Source File

SOURCE=.\string_sequence.tpp
# End Source File
# Begin Source File

SOURCE=.\string_set.tpp
# End Source File
# Begin Source File

SOURCE=.\string_simple_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\string_smart_ptr.tpp
# End Source File
# Begin Source File

SOURCE=.\string_triple.tpp
# End Source File
# Begin Source File

SOURCE=.\string_vector.tpp
# End Source File
# Begin Source File

SOURCE=.\triple.tpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\README.txt
# End Source File
# End Target
# End Project
