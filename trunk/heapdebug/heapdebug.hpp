#ifndef STLPLUS_HEAPDEBUG_HPP
#define STLPLUS_HEAPDEBUG_HPP
////////////////////////////////////////////////////////////////////////////////

// Author:    Andy Rushton
// Copyright: (c) Southampton University 1999-2004
//            (c) Andy Rushton           2004-2009
// License:   BSD License, see ../docs/license.html

// A subsystem for tracing and reporting heap memory usage using new/delete

////////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable: 4290)
#endif

#ifdef __BORLANDC__
#define HEAPDEBUG_NO_PLACEMENT_DELETE
#define HEAPDEBUG_BROKEN_NOTHROW
#endif

#include <new>

////////////////////////////////////////////////////////////////////////////////
// reproduce the standard definitions of new/delete in case of header inconsistencies

// standard new and delete - new can throw a bad_alloc if there is no memory left
void* operator new (size_t) throw(std::bad_alloc);
void* operator new[] (size_t) throw(std::bad_alloc);
void operator delete (void*) throw();
void operator delete[] (void*) throw();

// nothrow variants will never throw an exception - so new(nothrow) will return null if out of memory
#ifndef HEAPDEBUG_BROKEN_NOTHROW
void* operator new (size_t, const std::nothrow_t&) throw();
void* operator new[] (size_t, const std::nothrow_t&) throw();
void operator delete (void* memory, const std::nothrow_t&) throw();
void operator delete[] (void* memory, const std::nothrow_t&) throw();
#endif

////////////////////////////////////////////////////////////////////////////////
// exported diagnostic functions

namespace stlplus
{
  // report the state of memory - this is automatically called at exit
  void heapdebug_report(void);

  // get the error count
  unsigned heapdebug_errors(void);

  // get the number of blocks outstanding, i.e. allocated but not deallocated
  unsigned heapdebug_outstanding(void);
}

// memory debugging is switched on by the standard NDEBUG macro also used for assertions
#ifndef NDEBUG

////////////////////////////////////////////////////////////////////////////////
// placement new operators which record filename and lineno information for each allocation
// the macros are provided to make these operators easier to use

void* operator new (size_t, const char*, int) throw(std::bad_alloc);
void* operator new[] (size_t, const char*, int) throw(std::bad_alloc);

#ifndef HEAPDEBUG_NO_PLACEMENT_DELETE
void operator delete (void*, const char*, int) throw();
void operator delete[] (void*, const char*, int) throw();
#endif

// Two ways of using this:
//
// 1) #define STLPLUS_HEAPDEBUG_USE_MACRO_NEW before including this header and
// use the NEW macro in your code - this avoids problems with placement
// versions of new but requires changes to your code
//
// 2) (default) use the new operator in your code and let the macros replace
// them with the debugging versions - note that this requires less changes to
// your code but will not work if your code uses placement new

#ifdef STLPLUS_HEAPDEBUG_USE_MACRO_NEW
#  define NEW new(__FILE__,__LINE__)
#else
#  define new new(__FILE__,__LINE__)
#endif

#else

// non-debug version
// if the user has used macros, map them directly onto the keywords

#define NEW new

#endif

#endif
