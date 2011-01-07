#ifndef STLPLUS_PERSISTENCE_FIXES
#define STLPLUS_PERSISTENCE_FIXES
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004 onwards
//   License:   BSD License, see ../docs/license.html

//   Contains work arounds for OS or Compiler specific problems

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Unnecessary compiler warnings
////////////////////////////////////////////////////////////////////////////////

// Microsoft Visual Studio
#ifdef _MSC_VER
// shut up the following irritating warnings
//   4786 - VC6, identifier string exceeded maximum allowable length and was truncated (only affects debugger)
//   4305 - VC6, identifier type was converted to a smaller type
//   4503 - VC6, decorated name was longer than the maximum the compiler allows (only affects debugger)
//   4309 - VC6, type conversion operation caused a constant to exceeded the space allocated for it
//   4290 - VC6, C++ exception specification ignored
//   4800 - VC6, forcing value to bool 'true' or 'false' (performance warning)
//   4675 - VC7.1, "change" in function overload resolution _might_ have altered program
//   4996 - VC8, 'xxxx' was declared deprecated
#pragma warning(disable: 4786 4305 4503 4309 4290 4800 4675 4996)
#endif

// Borland
#ifdef __BORLANDC__
// Shut up the following irritating warnings
//   8026 - Functions with exception specifications are not expanded inline
//   8027 - Functions with xxx are not expanded inline
#pragma warn -8026
#pragma warn -8027
#endif

////////////////////////////////////////////////////////////////////////////////
// Rules for testing whether this compiler has TR1 extension data types
// Specifically I only support use of these extensions in their final, C++0x standard form
// i.e. 
//   1) the headers are in the global memory space (e.g. #include <memory>)
//   2) the components are in the std:: namespace
// Earlier versions put headers in a tr1/ subdirectory and compoinents in a std::tr1 sub-namespace
////////////////////////////////////////////////////////////////////////////////

// gcc has TR1 after version 4
// in normal mode, the TR1 extensions are in the tr1/ header space and std::tr1 namespace
// in C++0x mode they are in the global header space and std:: namespace
// C++0x mode is switched on from the command line using the -std=c++0x flag
#ifdef __GXX_EXPERIMENTAL_CXX0X__
#define STLPLUS_HAS_CXX0X 1
#endif

// Visual Studio
#ifdef _MSC_VER
// Microsoft only incorporated TR1 into std:: namespace in Visual Studio 2010 (v16.00)
#if _MSC_VER >= 1600
#define STLPLUS_HAS_CXX0X 1
#endif
#endif

// Borland
#ifdef __BORLANDC__
// Borland have supported TR1 since v5.82
#if __BORLANDC__ >= 0x582
#define STLPLUS_HAS_CXX0X 1
#endif
#endif

////////////////////////////////////////////////////////////////////////////////
#endif
