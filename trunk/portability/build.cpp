////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Southampton University 1999-2004
//              (c) Andy Rushton           2004-2009
//   License:   BSD License, see ../docs/license.html

////////////////////////////////////////////////////////////////////////////////
#include "build.hpp"
#include "version.hpp"
#include "dprintf.hpp"
////////////////////////////////////////////////////////////////////////////////

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // report the platform-specific details of this build

  std::string build(void)
  {
    ////////////////////////////////////////////////////////////////////////////////
    // work out the platform

#ifdef _WIN32
    std::string platform("Windows");
#else
    // at present there are no variations between different Unix platforms so
    // they all map onto the generic Unix platform
    std::string platform("Generic Unix");
#endif

    ////////////////////////////////////////////////////////////////////////////////
    // work out the compiler

#if defined __GNUC__
    std::string compiler(dformat("gcc v%s",__VERSION__));
#elif defined _MSC_VER
    std::string compiler(dformat("MSVC v%0.2f",((float)_MSC_VER)/100.0));
#elif defined __BORLANDC__
    std::string compiler(dformat("Borland v%d.%d",__BORLANDC__/256,__BORLANDC__/16%16));
#else
    std::string compiler("unknown compiler");
#endif

    ////////////////////////////////////////////////////////////////////////////////
    // work out the kind of build
    // there are two variants - debug and release

#ifndef NDEBUG
    std::string variant("debug");
#else
    std::string variant("release");
#endif

    return std::string("STLplus v") + version() + ", " + platform + ", " + compiler + ", " + variant;
  }

////////////////////////////////////////////////////////////////////////////////
} // end namespace stlplus
