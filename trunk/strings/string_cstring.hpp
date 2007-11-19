#ifndef STLPLUS_STRING_CSTRING
#define STLPLUS_STRING_CSTRING
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

//   Functions for converting C strings to string

//   This is necessary for completeness

////////////////////////////////////////////////////////////////////////////////
#include "strings_fixes.hpp"
#include <string>
#include <stdexcept>

namespace stlplus
{

  std::string cstring_to_string(const char* value);

}

#endif
