#ifndef STLPLUS_BUILD
#define STLPLUS_BUILD
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

//   Provides a printable representation of the build characteristics in the form:

//     version, platform, compiler, variant

//   Where
//     version is the version of STLplus
//     platform is the target operating system
//     compiler is the compilation system and version that the function was compiled with
//     variant is the kind of build - debug or release

//   Example:
//     STLplus version 3.0, Generic Unix, gcc v3.4, debug

////////////////////////////////////////////////////////////////////////////////
#include "portability_fixes.hpp"
#include <string>

namespace stlplus
{

  std::string build(void);

}
////////////////////////////////////////////////////////////////////////////////
#endif
