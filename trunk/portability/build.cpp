////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "build.hpp"
#include "version.hpp"
#include "dprintf.hpp"
////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

////////////////////////////////////////////////////////////////////////////////
// work out the platform
// at present there are no variations between different Unix platforms so they all map onto the generic Unix platform

#undef PLATFORM
#ifdef MSWINDOWS
#define PLATFORM std::string("Windows")
#endif

#ifndef PLATFORM
#define PLATFORM std::string("Generic Unix")
#endif

////////////////////////////////////////////////////////////////////////////////
// work out the compiler

#undef COMPILER
#ifdef __GNUC__
#define COMPILER (std::string("gcc v")+std::string(__VERSION__))
#endif
#ifdef _MSC_VER
#define COMPILER (std::string("MSVC v")+dformat("%0.2f",((float)_MSC_VER)/100.0))
#endif
#ifdef __BORLANDC__
#define COMPILER (std::string("Borland v")+dformat("%d",__BORLANDC__/256)+std::string(".")+dformat("%d",__BORLANDC__/16%16))
#endif

#ifndef COMPILER
#define COMPILER std::string("unknown compiler")
#endif

////////////////////////////////////////////////////////////////////////////////
// work out the kind of build
// there are two variants - debug and release

#undef VARIANT
#ifndef NDEBUG
#define VARIANT std::string("debug")
#else
#define VARIANT std::string("release")
#endif

////////////////////////////////////////////////////////////////////////////////
// report the platform-specific details of this build

std::string build(void)
{
  return std::string("STLplus v") + version() + ", " + PLATFORM + ", " + COMPILER + ", " + VARIANT;
}

////////////////////////////////////////////////////////////////////////////////
} // end namespace stlplus
