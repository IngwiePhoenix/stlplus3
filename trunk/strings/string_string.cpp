/*------------------------------------------------------------------------------

  Author:    Andy Rushton
  Copyright: (c) Andy Rushton, 2007
  License:   BSD License, see ../docs/license.html

  ------------------------------------------------------------------------------*/
#include "string_string.hpp"

namespace stlplus
{

  ////////////////////////////////////////////////////////////////////////////////
  // strings

  std::string string_to_string(const std::string& value)
  {
    return value;
  }

  std::string cstring_to_string(const char* value)
  {
    return std::string(value);
  }

} // end namespace stlplus
