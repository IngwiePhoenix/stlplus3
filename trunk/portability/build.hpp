#ifndef STLPLUS_OS_FIXES_HPP
#define STLPLUS_OS_FIXES_HPP
/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  Provides a printable representation of the build characteristics in the form:

    platform, compiler, variant

  Where
    platform is the target operating system e.g. Windows or Generic Unix
    compiler is the compilation system and version that the function was compiled with e.g. gcc v4.1 or MSVC v12
    variant is the kind of build - debug or release

------------------------------------------------------------------------------*/
#include <string>

namespace stlplus
{

  std::string build(void);

}
////////////////////////////////////////////////////////////////////////////////
#endif
