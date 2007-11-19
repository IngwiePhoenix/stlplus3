#ifndef STLPLUS_STRING_STRING
#define STLPLUS_STRING_STRING
////////////////////////////////////////////////////////////////////////////////

//   Author:    Andy Rushton
//   Copyright: (c) Andy Rushton, 2007
//   License:   BSD License, see ../docs/license.html

//   Functions for converting C/STL strings to string

//   This is necessary for completeness, e.g. for use in vector_to_string for vector<string>

////////////////////////////////////////////////////////////////////////////////
#include "strings_fixes.hpp"
#include <string>
#include <stdexcept>

namespace stlplus
{

  std::string string_to_string(const std::string& value);

}

#endif
